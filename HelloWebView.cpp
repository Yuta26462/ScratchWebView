//// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c
//
//#include <windows.h>
//#include <stdlib.h>
//#include <string>
//#include <tchar.h>
//#include <wrl.h>
//#include <wil/com.h>
//// <IncludeHeader>
//// include WebView2 header
//#include "WebView2.h"
//#include "resource.h"
//// </IncludeHeader>/
//
//
//using namespace Microsoft::WRL;
//
//// メインウィンドウのクラス名
//static TCHAR szWindowClass[] = _T("DesktopApp");
//
//// アプリケーションのタイトルバーに表示される文字列
//static TCHAR szTitle[] = _T("Scratch");
//
//HINSTANCE hInst;
//
//// 関数宣言
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//// WebViewControllerへのポインタ
//static wil::com_ptr<ICoreWebView2Controller> webviewController;
//
//// WebViewウィンドウへのポインタ
//static wil::com_ptr<ICoreWebView2> webview;
//
//int CALLBACK WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow
//)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	//wcex.hIcon = LoadIcon(hInstance, TEXT("IDI_ICON1"));
//	wcex.hIcon = (HICON)LoadImage(
//		hInstance,
//		_T("ICON01"),  /* アイコンリソースの名前 */
//		IMAGE_ICON,
//		0, 0, LR_DEFAULTSIZE | LR_SHARED);
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
//
//	if (!RegisterClassEx(&wcex))
//	{
//		MessageBox(NULL,
//			_T("Call to RegisterClassEx failed!"),
//			_T("Windows Desktop Guided Tour"),
//			NULL);
//
//		return 1;
//	}
//
//	// グローバル変数にインスタンスハンドルを保存する
//	hInst = hInstance;
//
//	// ディスプレイサイズを取得
//	RECT rtScreen;
//	GetWindowRect(GetDesktopWindow(), &rtScreen);
//
//	// CreateWindow のパラメータ説明:
//	// szWindowClass: アプリケーション名
//	// szTitle: タイトルバーに表示されるテキスト
//	// WS_OVERLAPPEDWINDOW: 作成するウィンドウの種類
//	// CW_USEDEFAULT, CW_USEDEFAULT: 初期位置 (x, y)
//	// 500, 100: 初期サイズ (width, length)
//	// NULL: このウィンドウの親
//	// NULL: このアプリケーションにはメニューバーがありません
//	// hInstance: WinMainの最初のパラメータ
//	// NULL: このアプリケーションでは使用しない
//	HWND hWnd = CreateWindow(
//		szWindowClass,
//		szTitle,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		rtScreen.left + rtScreen.right, rtScreen.bottom + rtScreen.top,
//		NULL,
//		NULL,	
//		hInstance,
//		NULL
//	);
//
//	// 疑似フルスクリーン
//	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
//	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//
//	if (!hWnd)
//	{
//		MessageBox(NULL,
//			_T("CreateWindow の呼び出しに失敗しました"),
//			_T("Windowsデスクトップ ガイドツアー"),
//			NULL);
//
//		return 1;
//	}
//
//	// ShowWindowのパラメータ:
//	// hWnd: CreateWindow から返される値
//	// nCmdShow: WinMainの4番目のパラメータ
//	ShowWindow(hWnd,
//		nCmdShow);
//	UpdateWindow(hWnd);
//
//	
//	// Step 3 - 親ウィンドウ内に単一のWebViewを作成する
//	// ブラウザの位置を確認し、WebViewの環境を設定する。
//	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
//		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
//			[hWnd](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
//
//				// CoreWebView2Controllerを作成し、メインウィンドウを親とするCoreWebView2を取得する hWnd
//				env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
//					[hWnd](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
//						if (controller != nullptr) {
//							webviewController = controller;
//							webviewController->get_CoreWebView2(&webview);
//						}
//
//						// ウェブビューの設定を追加する
//						// 値はデフォルト設定なので、デモのステップは冗長である。
//						wil::com_ptr<ICoreWebView2Settings> settings;
//						webview->get_Settings(&settings);
//						// スクリプトを有効化
//						settings->put_IsScriptEnabled(TRUE);
//						// デフォルトのダイアログを有効化
//						settings->put_AreDefaultScriptDialogsEnabled(TRUE);
//						// ファイルのドラッグアンドドロップを有効化
//						settings->put_IsWebMessageEnabled(TRUE);
//						//開発者ツールを無効化
//						settings->put_AreDevToolsEnabled(FALSE);
//						//ズームコントロールを無効化
//						settings->put_IsZoomControlEnabled(FALSE);
//						// ステータスバーを無効化
//						settings->put_IsStatusBarEnabled(FALSE);
//						// メイン・ウィンドウを最前面に表示する(強制前面表示)
//						SetForegroundWindow(hWnd);
//
//						// 親ウィンドウの境界に合わせてWebViewのサイズを変更する
//						RECT bounds;
//						GetClientRect(hWnd, &bounds);
//						webviewController->put_Bounds(bounds);
//
//						// Scratchにナビゲートする非同期タスクをスケジュールする
//						//webview->Navigate(L"https://scratch.mit.edu/projects/editor/?tutorial=getStarted");
//						webview->Navigate(L"https://scratch.mit.edu/projects/882371064/editor/");
//						
//
//						// <NavigationEvents>
//						// Step 4 - ナビゲーションイベント
//						// https以外のナビゲーションをキャンセルするためにICoreWebView2NavigationStartingEventHandlerを登録する。
//						EventRegistrationToken token;
//						webview->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
//							[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
//								wil::unique_cotaskmem_string uri;
//								args->get_Uri(&uri);
//								std::wstring source(uri.get());
//								if (source.substr(0, 5) != L"https") {
//									args->put_Cancel(true);
//								}
//								return S_OK;
//							}).Get(), &token);
//						// </NavigationEvents>
//
//						// <Scripting>
//						// Step 5 - Scripting
//						// Objectオブジェクトをフリーズさせる初期化スクリプトを追加する非同期タスクをスケジュールする
//						webview->AddScriptToExecuteOnDocumentCreated(L"Object.freeze(Object);", nullptr);
//						// Schedule an async task to get the document URL
//						webview->ExecuteScript(L"window.document.URL;", Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
//							[](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
//								LPCWSTR URL = resultObjectAsJson;
//								//doSomethingWithURL(URL);
//								return S_OK;
//							}).Get());
//						// </Scripting>
//
//						// <CommunicationHostWeb>
//						// Step 6 - ホストとウェブコンテンツ間の通信
//						// ホストが受信したメッセージをウェブコンテンツに返すためのイベントハンドラを設定する。
//						
//						// ダイヤログメッセージを表示する
//						//webview->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
//						//	[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
//						//		wil::unique_cotaskmem_string message;
//						//		args->TryGetWebMessageAsString(&message);
//						//		// processMessage(&message);
//						//		webview->PostWebMessageAsString(message.get());
//						//		return S_OK;
//						//	}).Get(), &token);
//
//						// 以下の初期化スクリプトを追加し、非同期タスクをスケジュールする。
//						// 1) ホストからのメッセージを表示するリスナーを追加する
//						// 2) ドキュメントのURLをホストに送信
//						webview->AddScriptToExecuteOnDocumentCreated(
//							L"window.chrome.webview.addEventListener(\'message\', event => alert(event.data));" \
//							L"window.chrome.webview.postMessage(window.document.URL);",
//							nullptr);
//						// </CommunicationHostWeb>
//
//						return S_OK;
//					}).Get());
//				return S_OK;
//			}).Get());
//
//
//	// Main message loop:
//	MSG msg;
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return (int)msg.wParam;
//}
//
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  目的：メインウィンドウのメッセージを処理する。
////
////  WM_DESTROY  - 終了メッセージを表示して戻る
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	TCHAR greeting[] = _T("Hello, Windows desktop!");
//
//	switch (message)
//	{
//	case WM_SIZE:
//		if (webviewController != nullptr) {
//			RECT bounds;
//			GetClientRect(hWnd, &bounds);
//			webviewController->put_Bounds(bounds);
//		};
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//		break;
//	}
//
//	return 0;
//}
