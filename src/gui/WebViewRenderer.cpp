#include "WebViewRenderer.hpp"

WebViewRenderer::WebViewRenderer(int width, int height)
    : width(width), height(height) {
    const char *vertexShaderText =
            "#version 330 core\n"
            "layout (location = 0) in vec2 Position;\n"
            "layout (location = 1) in vec2 TexturePosition;\n"
            "out vec2 Coordinates;\n"
            "void main() {\n"
            "    gl_Position = vec4(Position.xy, 0.0, 1.0);\n"
            "    Coordinates = TexturePosition;\n"
            "}\n";

    const char *fragmentShaderText =
            "#version 330 core\n"
            "in vec2 Coordinates;\n"
            "out vec4 OutputColor;\n"
            "uniform sampler2D Texture;\n"
            "void main() {\n"
            "    OutputColor = texture(Texture, Coordinates);\n"
            "}\n";

    GLuint indices[6] = {0, 1, 3, 0, 3, 2};
    GLfloat vertices[8] = {-1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f};
    GLfloat textures[8] = {0.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f};

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader);
    glDeleteShader(vertexShader);

    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(fragmentShader);

    glGenBuffers(3, &buffers[0]);

    glGenVertexArrays(1, &object);
    glBindVertexArray(object);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(NULL);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);

    glBindTexture(GL_TEXTURE_2D, NULL);
}

WebViewRenderer::~WebViewRenderer() {
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(3, &buffers[0]);
    glDeleteBuffers(1, &object);
    glDeleteTextures(1, &texture);
}

void WebViewRenderer::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect.width = this->width;
    rect.height = this->height;
}

void WebViewRenderer::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type,
                              const RectList &dirtyRects, const void *buffer, int _width, int _height) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, _width);

    for (const CefRect &rect : dirtyRects) {
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect.x);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, rect.y);

        glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width, rect.height, GL_BGRA, GL_UNSIGNED_BYTE, buffer);
    }

    glBindTexture(GL_TEXTURE_2D, NULL);
}

void WebViewRenderer::SetSize(int _width, int _height) {
    this->width = _width;
    this->height = _height;

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void WebViewRenderer::Render() const {
    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(object);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
}
