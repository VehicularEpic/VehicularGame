#include "WebViewSchemeHandler.hpp"

#include <include/cef_parser.h>
#include <include/wrapper/cef_stream_resource_handler.h>

CefRefPtr<CefResourceHandler> WebViewSchemeHandler::Create(
        CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
        const CefString &scheme_name, CefRefPtr<CefRequest> request) {
    CefURLParts url_parts;
    CefParseURL(request->GetURL(), url_parts);

    std::string file = CefString(&url_parts.path).ToString().substr(1);

    Asset asset = this->repository.Read(file);
    size_t size = sizeof(asset.data[0]) * asset.data.size();

    CefRefPtr<CefStreamReader> stream =
            CefStreamReader::CreateForData(&asset.data[0], size);
    return new CefStreamResourceHandler(asset.mimeType, stream);
}
