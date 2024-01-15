#pragma once
#include "AbstractScene.h"
//#include <windows.h>
//#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"

class WebViewScene : public AbstractScene {
public:

    wil::com_ptr<ICoreWebView2Controller> webviewController;

private:
    
    wil::com_ptr<ICoreWebView2> webview;
    HWND hWnd;

    //wil::com_ptr<ICoreWebView2Controller> webviewController = nullptr;
    //wil::com_ptr<ICoreWebView2> webview = nullptr;
    EventRegistrationToken webMessageReceivedToken = {};

public:
    WebViewScene();
    ~WebViewScene();
    virtual AbstractScene* Update() override;
    virtual void Draw() const override;

    //wil::com_ptr<ICoreWebView2Controller> getWebviewController() { return webviewController; }
};
