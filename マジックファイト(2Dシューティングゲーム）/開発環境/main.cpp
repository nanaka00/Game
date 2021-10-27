//=================================================================================================================
//
// 2D�Q�[���̏����@�kmain.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "main.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "Score.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "light.h"
#include "pause.h"
#include "rule.h"
#include "life.h"
#include "ranking.h"

//=================================================================================================================
//�}�N����`
//=================================================================================================================
#define ID_BUTTON000	(101)		//�{�^��000��ID
#define ID_EDIT000		(111)		//�G�f�B�b�g��ID
#define ID_TIMER		(121)		//�^�C�}�[��ID
#define TIMER_INTERVAL	(1000/60)	//�^�C�}�[�����Ԋu
#define WINDOW_POS_X    (500)		//�E�B���h�E�̍���X���W
#define WINDOW_POS_Y    (100)		//�E�B���h�E�̍���Y���W

//=================================================================================================================
// �v���g�^�C�v�錾
//=================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//=================================================================================================================
//�@�O���[�o���ϐ�
//=================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃|�C���^
int g_nCountFPS;						//FPS�J�E���^

MODE g_mode = MODE_TITLE;				//���[�h�̎��

//*****************************************************************************************************************
//	���C���֐�
//*****************************************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�ϐ��錾
	RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	WNDCLASSEX wcex = 

	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"�t�@�C��",
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;					//�E�B���h�E�n���h���i���ʎq�j
	MSG msg;					//���b�Z�[�W���i�[����
	DWORD dwExecLastTime;		//�������s�ŏI����
	DWORD dwFPSLastTime;		//FPS�v���ŏI����
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwFameCount;			//�t���[���J�E���g

	dwExecLastTime =
	dwFPSLastTime =
	dwCurrentTime = timeGetTime();
	dwFameCount = 0;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̑傫���𒲐�����
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,
		"�t�@�C��",	//�E�B���h�E�N���X�̖��O
		"MAGIC FIGHT",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);


	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))	//false���ƃt���X�N���[��
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{	//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5�b�o��
				g_nCountFPS = (dwFameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //�ŏI�����̕ۑ�
				dwFameCount = 0;
			}


			if ((dwCurrentTime - dwExecLastTime)>(1000/60))
			{
				//DirectX�̏���
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();
				//�`�揈��
				Draw();

				dwFameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		"�t�@�C��",
		wcex.hInstance);

	return (int)msg.wParam;

}

//*****************************************************************************************************************
//�E�B���h�E�v���V�[�W��
//*****************************************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ϐ��錾
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };


	switch (uMsg)
	{
		
	case WM_CLOSE:	//�~�{�^���������ꂽ�ꍇ
		nID = MessageBox(NULL, "�I�����܂����H", "����", MB_YESNO | MB_ICONSTOP);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_DESTROY:				//�E�B���h�E�̔j��
		PostQuitMessage(0);			//WN_QUIT ���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				//ESCAPE�L�[�������ꂽ�Ƃ�
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
	
//*****************************************************************************************************************
//	����������
//*****************************************************************************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�B�X�v���C�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;					// �J���[���[�h�̎w��
	d3dpp.BackBufferCount = 1;								// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;				// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;							// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;				// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// �C���^�[�o��


	//Direct3D�f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU���ōs��
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, 
			hWnd, 
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs��
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�i�`�挳�j
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V�����̍������@�̐ݒ�

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ� (���l�̍����j
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//����������
	InitKeyboard(hInstance,hWnd);

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̐ݒ�
	SetMode(g_mode);
	
	//�t�F�[�h�̏���������
	InitFade(g_mode);

	return S_OK;
}

//*****************************************************************************************************************
//�@�I������
//*****************************************************************************************************************
void Uninit(void)
{
	//�L�[�{�[�h��	�I������
	UninitKeyboard();

	//�t�F�[�h�̏I������
	UninitFade();

	//��ʑJ�ڂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_RULE:
		UninitRule();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}
	//�T�E���h�̏I������
	UninitSound();

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̉��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̉��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL; 
	}
}
//*****************************************************************************************************************
//�X�V����
//*****************************************************************************************************************
void Update(void)
{
	//���̓f�o�C�X�̍X�V����
	UpdateKeyboard();
	
	//��ʑJ�ڂ̍X�V����
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_RULE:
		UpdateRule();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}
	UpdateFade();

}

//*****************************************************************************************************************
//	FPS�̏���
//*****************************************************************************************************************
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//*****************************************************************************************************************
//	�`�揈��
//*****************************************************************************************************************
void Draw(void)
{
	//�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);


	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//��ʑJ��
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_RULE:
			DrawRule();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		default:
			break;
		}
		
		DrawFade();			//�t�F�[�h

		#ifdef _DEBUG
		DrawFPS();			//FPS����
		#endif

		//�`��̏I��
		g_pD3DDevice->EndScene();
	} 
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//*****************************************************************************************************************
//	���[�h�̐ݒ�
//*****************************************************************************************************************
void SetMode(MODE mode)
{
	//��ʑJ�ڂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_RULE:
		UninitRule();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}
	g_mode = mode;

	//��ʑJ�ڂ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_RULE:
		InitRule();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	default:
		break;
	}
}

MODE GetMode(void)
{
	return g_mode;
}
