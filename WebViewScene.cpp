#include "WebViewScene.h"
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <wrl/event.h>

#include "resource.h"

#include "DxLib.h"

using namespace Microsoft::WRL;

// ���C���E�B���h�E�̃N���X��
static TCHAR szWindowClass[] = _T("WebViewSceneWindow");

// �A�v���P�[�V�����̃^�C�g���o�[�ɕ\������镶����
static TCHAR szTitle[] = _T("Scratch");

// �֐��錾
LRESULT CALLBACK WebViewWndProc(HWND, UINT, WPARAM, LPARAM);

// �R���X�g���N�^
WebViewScene::WebViewScene() {
    // WNDCLASSEX �̐ݒ�
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
        _T("ICON01"),  /* �A�C�R�����\�[�X�̖��O */
        IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        // �G���[����
        return;
    }

    // �f�B�X�v���C�T�C�Y���擾
    RECT rtScreen;
    GetWindowRect(GetDesktopWindow(), &rtScreen);

    // �E�B���h�E�̍쐬
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

    // DX���C�u�����̃��C���E�B���h�E�n���h�����擾
    HWND hWnd = (HWND)GetMainWindowHandle();

    // �^���t���X�N���[��
    SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("CreateWindow �̌Ăяo���Ɏ��s���܂���"),
            _T("Windows�f�X�N�g�b�v �K�C�h�c�A�["),
            NULL);

        return;
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    // WebView2 �̏�����
    // ���̕����� HelloWebView.cpp �� WebView2 �̏������������Q�l�ɂ��Ă�������

    // WebViewScene �R���X�g���N�^���A�E�B���h�E�쐬��̕���

// WebView2 ���̏�����
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

                        // ���̑��� WebView2 �̐ݒ�
                        // ��: webview->AddWebResourceRequestedFilter() �Ȃǂ̃��\�b�h�Ăяo��

                                                // �E�F�u�r���[�̐ݒ��ǉ�����
                        // �l�̓f�t�H���g�ݒ�Ȃ̂ŁA�f���̃X�e�b�v�͏璷�ł���B
                        wil::com_ptr<ICoreWebView2Settings> settings;
                        webview->get_Settings(&settings);
                        // �X�N���v�g��L����
                        settings->put_IsScriptEnabled(TRUE);
                        // �f�t�H���g�̃_�C�A���O��L����
                        settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                        // �t�@�C���̃h���b�O�A���h�h���b�v��L����
                        settings->put_IsWebMessageEnabled(TRUE);
                        //�J���҃c�[���𖳌���
                        settings->put_AreDevToolsEnabled(FALSE);
                        //�Y�[���R���g���[���𖳌���
                        settings->put_IsZoomControlEnabled(FALSE);
                        // �X�e�[�^�X�o�[�𖳌���
                        settings->put_IsStatusBarEnabled(FALSE);
                        // ���C���E�E�B���h�E���őO�ʂɕ\������(�����O�ʕ\��)
                        SetForegroundWindow(hWnd);

                        // �e�E�B���h�E�̋��E�ɍ��킹��WebView�̃T�C�Y��ύX����
                        RECT bounds;
                        GetClientRect(hWnd, &bounds);
                        webviewController->put_Bounds(bounds);

                        // Scratch�Ƀi�r�Q�[�g����񓯊��^�X�N���X�P�W���[������
                        //webview->Navigate(L"https://scratch.mit.edu/projects/editor/?tutorial=getStarted");
                        webview->Navigate(L"https://scratch.mit.edu/projects/882371064/editor/");

                        //! F12�Ńf�x���b�p�[���[�h�ɓ��낤�Ƃ���ƃo�O��

                        // <NavigationEvents>
                        // Step 4 - �i�r�Q�[�V�����C�x���g
                        // https�ȊO�̃i�r�Q�[�V�������L�����Z�����邽�߂�ICoreWebView2NavigationStartingEventHandler��o�^����B
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


    // WebView2 �̃C�x���g�n���h���̐ݒ�
    // ��: NavigationCompleted, WebMessageReceived �Ȃǂ̃C�x���g
}

// �f�X�g���N�^
WebViewScene::~WebViewScene() {
    // WebView2 �̃��\�[�X�̉��
    webview = nullptr;
    webviewController = nullptr;

    // �E�B���h�E�̔j��
    DestroyWindow(hWnd);
}

AbstractScene* WebViewScene::Update() {
    // WebView2 �̍X�V������V�[���J�ڂ̃��W�b�N�������Ɏ���

    return this;
}

void WebViewScene::Draw() const {
    // WebView2 �͎����I�ɕ`�悳��邽�߁A���̃��\�b�h���œ��ʂȕ`�揈���͊�{�I�ɕK�v����܂���
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WebViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // HelloWebView.cpp �Œ�`����Ă��� WndProc �֐��̓��e�����̊֐��ɈڐA
    // �K�v�ɉ����ăR�[�h�𒲐����Ă�������

	TCHAR greeting[] = _T("Hello, Windows desktop!");
    WebViewScene* scene = reinterpret_cast<WebViewScene*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (scene) {
        // scene->webviewController �⑼�̃����o�ϐ��ɃA�N�Z�X���邱�Ƃ��ł��܂�
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
