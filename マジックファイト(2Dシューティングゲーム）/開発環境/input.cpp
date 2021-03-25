//=================================================================================================================
//
// �L�[�{�[�h�̏����@�kinput.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "input.h"

//=================================================================================================================
//	�}�N����`
//=================================================================================================================
#define NUM_KEY_MAX (256)	//�L�[�̍ő吔

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECTINPUT8 g_pInput = NULL;							//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;				//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX]; 							//�L�[�{�[�h�ւ̓��͏��
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];					//�L�[�g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];					//�L�[�����[�X���
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];					//�L�[���s�[�g���
int g_aCountRepeat[NUM_KEY_MAX];						//�L�[���s�[�g�J�E���^�[


//*****************************************************************************************************************
//	����������
//*****************************************************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	g_pDevkeyboard->Acquire();
	{
		return S_OK;
	}
}

//*****************************************************************************************************************
//�I������
//*****************************************************************************************************************
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̊J��
	if (g_pDevkeyboard != NULL)
	{
		//�A�N�Z�X���̔j��
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	//Directinput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//*****************************************************************************************************************
//	�X�V����
//*****************************************************************************************************************
void UpdateKeyboard(void)
{
	//�ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h���݂̓��͏��

	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < NUM_KEY_MAX; nKey++)
		{
			//�g���K�[
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] & aKeyState[nKey] ^ aKeyState[nKey] );

			//�����[�X
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] | aKeyState[nKey] ^ aKeyState[nKey]);

			//1�t���[���O�̃L�[�v���X���ۑ�
			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		g_pDevkeyboard->Acquire();
	}
}


//*****************************************************************************************************************
//�L�[�{�[�h���擾�i�v���X�j
//*****************************************************************************************************************
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}
//*****************************************************************************************************************
//�L�[�{�[�h���擾�i�g���K�[�j
//*****************************************************************************************************************
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//*****************************************************************************************************************
//�L�[�{�[�h���擾(�����[�X�j
//*****************************************************************************************************************
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}