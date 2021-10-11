#pragma once

#include <glad/gl.h>
#include <include/cef_render_handler.h>

class WebViewRenderer : public CefRenderHandler {
    IMPLEMENT_REFCOUNTING(WebViewRenderer);

public:
    WebViewRenderer(int width, int height);

    ~WebViewRenderer() override;

    WebViewRenderer(const WebViewRenderer &) = delete;
    const WebViewRenderer &operator=(const WebViewRenderer &) = delete;

    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects,
                 const void *buffer, int width, int height) override;

    void SetSize(int width, int height);

    void Render() const;

private:
    int width;
    int height;

    GLuint shaderProgram;

    GLuint object = 0;
    GLuint buffers[3]{};

    GLuint texture = 0;
};
