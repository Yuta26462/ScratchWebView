#include "WebViewScene.h"
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <wrl/event.h>

#include "resource.h"

#include "DxLib.h"

using namespace Microsoft::WRL;

// メインウィンドウのクラス名
static TCHAR szWindowClass[] = _T("WebViewSceneWindow");

// アプリケーションのタイトルバーに表示される文字列
static TCHAR szTitle[] = _T("Scratch");

// 関数宣言
LRESULT CALLBACK WebViewWndProc(HWND, UINT, WPARAM, LPARAM);

// コンストラクタ
WebViewScene::WebViewScene() {
    // WNDCLASSEX の設定
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WebViewWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    //wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hIcon = (HICON)LoadImage(
        wcex.hInstance,
        _T("ICON01"),  /* アイコンリソースの名前 */
        IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        // エラー処理
        return;
    }

    // ディスプレイサイズを取得
    RECT rtScreen;
    GetWindowRect(GetDesktopWindow(), &rtScreen);

    // ウィンドウの作成
    /*HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rtScreen.left + rtScreen.right, rtScreen.bottom + rtScreen.top,
        NULL,
        NULL,
        wcex.hInstance,
        NULL
    );*/

    // DXライブラリのメインウィンドウハンドルを取得
    HWND hWnd = (HWND)GetMainWindowHandle();

    // 疑似フルスクリーン
    SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("CreateWindow の呼び出しに失敗しました"),
            _T("Windowsデスクトップ ガイドツアー"),
            NULL);

        return;
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    // WebView2 の初期化
    // この部分は HelloWebView.cpp の WebView2 の初期化部分を参考にしてください

    // WebViewScene コンストラクタ内、ウィンドウ作成後の部分

// WebView2 環境の初期化
    CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [hWnd, this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                if (result != S_OK)
                    return result;

                env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                    [hWnd, this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                        if (result != S_OK)
                            return result;

                        webviewController = controller;
                        webviewController->get_CoreWebView2(&webview);

                        // その他の WebView2 の設定
                        // 例: webview->AddWebResourceRequestedFilter() などのメソッド呼び出し

                                                // ウェブビューの設定を追加する
                        // 値はデフォルト設定なので、デモのステップは冗長である。
                        wil::com_ptr<ICoreWebView2Settings> settings;
                        webview->get_Settings(&settings);
                        // スクリプトを有効化
                        settings->put_IsScriptEnabled(TRUE);
                        // デフォルトのダイアログを有効化
                        settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                        // ファイルのドラッグアンドドロップを有効化
                        settings->put_IsWebMessageEnabled(TRUE);
                        //開発者ツールを無効化
                        settings->put_AreDevToolsEnabled(FALSE);
                        //ズームコントロールを無効化
                        settings->put_IsZoomControlEnabled(FALSE);
                        // ステータスバーを無効化
                        settings->put_IsStatusBarEnabled(FALSE);
                        // メイン・ウィンドウを最前面に表示する(強制前面表示)
                        SetForegroundWindow(hWnd);

                        // 親ウィンドウの境界に合わせてWebViewのサイズを変更する
                        RECT bounds;
                        GetClientRect(hWnd, &bounds);
                        webviewController->put_Bounds(bounds);

                        // Scratchにナビゲートする非同期タスクをスケジュールする
                        //webview->Navigate(L"https://scratch.mit.edu/projects/editor/?tutorial=getStarted");
                        webview->Navigate(L"https://scratch.mit.edu/projects/882371064/editor/");

                        //! F12でデベロッパーモードに入ろうとするとバグる

                        // <NavigationEvents>
                        // Step 4 - ナビゲーションイベント
                        // https以外のナビゲーションをキャンセルするためにICoreWebView2NavigationStartingEventHandlerを登録する。
                        EventRegistrationToken token;
                        webview->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
                            [](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
                                wil::unique_cotaskmem_string uri;
                                args->get_Uri(&uri);
                                std::wstring source(uri.get());
                                if (source.substr(0, 5) != L"https") {
                                    args->put_Cancel(true);
                                }
                                return S_OK;
                            }).Get(), &token);

                        return S_OK;
                    }).Get());

                return S_OK;
            }).Get());


    // WebView2 のイベントハンドラの設定
    // 例: NavigationCompleted, WebMessageReceived などのイベント
}

// デストラクタ
WebViewScene::~WebViewScene() {
    // WebView2 のリソースの解放
    webview = nullptr;
    webviewController = nullptr;

    // ウィンドウの破棄
    DestroyWindow(hWnd);
}

AbstractScene* WebViewScene::Update() {
    // WebView2 の更新処理やシーン遷移のロジックをここに実装

    return this;
}

void WebViewScene::Draw() const {
    // WebView2 は自動的に描画されるため、このメソッド内で特別な描画処理は基本的に必要ありません
}

// ウィンドウプロシージャ
LRESULT CALLBACK WebViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // HelloWebView.cpp で定義されている WndProc 関数の内容をこの関数に移植
    // 必要に応じてコードを調整してください

	TCHAR greeting[] = _T("Hello, Windows desktop!");
    WebViewScene* scene = reinterpret_cast<WebViewScene*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (scene) {
        // scene->webviewController や他のメンバ変数にアクセスすることができます
    }
	switch (message)
	{
	case WM_SIZE:
		if (scene->webviewController != nullptr) {
			RECT bounds;
			GetClientRect(hWnd, &bounds);
			scene->webviewController->put_Bounds(bounds);
		};
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
