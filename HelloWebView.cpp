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
//// ���C���E�B���h�E�̃N���X��
//static TCHAR szWindowClass[] = _T("DesktopApp");
//
//// �A�v���P�[�V�����̃^�C�g���o�[�ɕ\������镶����
//static TCHAR szTitle[] = _T("Scratch");
//
//HINSTANCE hInst;
//
//// �֐��錾
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//// WebViewController�ւ̃|�C���^
//static wil::com_ptr<ICoreWebView2Controller> webviewController;
//
//// WebView�E�B���h�E�ւ̃|�C���^
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
//		_T("ICON01"),  /* �A�C�R�����\�[�X�̖��O */
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
//	// �O���[�o���ϐ��ɃC���X�^���X�n���h����ۑ�����
//	hInst = hInstance;
//
//	// �f�B�X�v���C�T�C�Y���擾
//	RECT rtScreen;
//	GetWindowRect(GetDesktopWindow(), &rtScreen);
//
//	// CreateWindow �̃p�����[�^����:
//	// szWindowClass: �A�v���P�[�V������
//	// szTitle: �^�C�g���o�[�ɕ\�������e�L�X�g
//	// WS_OVERLAPPEDWINDOW: �쐬����E�B���h�E�̎��
//	// CW_USEDEFAULT, CW_USEDEFAULT: �����ʒu (x, y)
//	// 500, 100: �����T�C�Y (width, length)
//	// NULL: ���̃E�B���h�E�̐e
//	// NULL: ���̃A�v���P�[�V�����ɂ̓��j���[�o�[������܂���
//	// hInstance: WinMain�̍ŏ��̃p�����[�^
//	// NULL: ���̃A�v���P�[�V�����ł͎g�p���Ȃ�
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
//	// �^���t���X�N���[��
//	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
//	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//
//	if (!hWnd)
//	{
//		MessageBox(NULL,
//			_T("CreateWindow �̌Ăяo���Ɏ��s���܂���"),
//			_T("Windows�f�X�N�g�b�v �K�C�h�c�A�["),
//			NULL);
//
//		return 1;
//	}
//
//	// ShowWindow�̃p�����[�^:
//	// hWnd: CreateWindow ����Ԃ����l
//	// nCmdShow: WinMain��4�Ԗڂ̃p�����[�^
//	ShowWindow(hWnd,
//		nCmdShow);
//	UpdateWindow(hWnd);
//
//	
//	// Step 3 - �e�E�B���h�E���ɒP���WebView���쐬����
//	// �u���E�U�̈ʒu���m�F���AWebView�̊���ݒ肷��B
//	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
//		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
//			[hWnd](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
//
//				// CoreWebView2Controller���쐬���A���C���E�B���h�E��e�Ƃ���CoreWebView2���擾���� hWnd
//				env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
//					[hWnd](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
//						if (controller != nullptr) {
//							webviewController = controller;
//							webviewController->get_CoreWebView2(&webview);
//						}
//
//						// �E�F�u�r���[�̐ݒ��ǉ�����
//						// �l�̓f�t�H���g�ݒ�Ȃ̂ŁA�f���̃X�e�b�v�͏璷�ł���B
//						wil::com_ptr<ICoreWebView2Settings> settings;
//						webview->get_Settings(&settings);
//						// �X�N���v�g��L����
//						settings->put_IsScriptEnabled(TRUE);
//						// �f�t�H���g�̃_�C�A���O��L����
//						settings->put_AreDefaultScriptDialogsEnabled(TRUE);
//						// �t�@�C���̃h���b�O�A���h�h���b�v��L����
//						settings->put_IsWebMessageEnabled(TRUE);
//						//�J���҃c�[���𖳌���
//						settings->put_AreDevToolsEnabled(FALSE);
//						//�Y�[���R���g���[���𖳌���
//						settings->put_IsZoomControlEnabled(FALSE);
//						// �X�e�[�^�X�o�[�𖳌���
//						settings->put_IsStatusBarEnabled(FALSE);
//						// ���C���E�E�B���h�E���őO�ʂɕ\������(�����O�ʕ\��)
//						SetForegroundWindow(hWnd);
//
//						// �e�E�B���h�E�̋��E�ɍ��킹��WebView�̃T�C�Y��ύX����
//						RECT bounds;
//						GetClientRect(hWnd, &bounds);
//						webviewController->put_Bounds(bounds);
//
//						// Scratch�Ƀi�r�Q�[�g����񓯊��^�X�N���X�P�W���[������
//						//webview->Navigate(L"https://scratch.mit.edu/projects/editor/?tutorial=getStarted");
//						webview->Navigate(L"https://scratch.mit.edu/projects/882371064/editor/");
//						
//
//						// <NavigationEvents>
//						// Step 4 - �i�r�Q�[�V�����C�x���g
//						// https�ȊO�̃i�r�Q�[�V�������L�����Z�����邽�߂�ICoreWebView2NavigationStartingEventHandler��o�^����B
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
//						// Object�I�u�W�F�N�g���t���[�Y�����鏉�����X�N���v�g��ǉ�����񓯊��^�X�N���X�P�W���[������
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
//						// Step 6 - �z�X�g�ƃE�F�u�R���e���c�Ԃ̒ʐM
//						// �z�X�g����M�������b�Z�[�W���E�F�u�R���e���c�ɕԂ����߂̃C�x���g�n���h����ݒ肷��B
//						
//						// �_�C�����O���b�Z�[�W��\������
//						//webview->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
//						//	[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
//						//		wil::unique_cotaskmem_string message;
//						//		args->TryGetWebMessageAsString(&message);
//						//		// processMessage(&message);
//						//		webview->PostWebMessageAsString(message.get());
//						//		return S_OK;
//						//	}).Get(), &token);
//
//						// �ȉ��̏������X�N���v�g��ǉ����A�񓯊��^�X�N���X�P�W���[������B
//						// 1) �z�X�g����̃��b�Z�[�W��\�����郊�X�i�[��ǉ�����
//						// 2) �h�L�������g��URL���z�X�g�ɑ��M
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
////  �ړI�F���C���E�B���h�E�̃��b�Z�[�W����������B
////
////  WM_DESTROY  - �I�����b�Z�[�W��\�����Ė߂�
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
