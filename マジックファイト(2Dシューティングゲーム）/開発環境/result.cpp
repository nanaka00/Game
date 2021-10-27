//=================================================================================================================
//
// ���U���g��ʂ̏����@�kresult.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "player.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Score.h"
#include "sound.h"

//=================================================================================================================
// �O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexClear[RESULT_CLEAR_MAX] = {};		// �Q�[���N���A�������̕ϐ�
LPDIRECT3DTEXTURE9 g_apTexGameOver[RESULT_OVER_MAX] = {};	// �Q�[���I�[�o�[�������̕ϐ�
LPDIRECT3DTEXTURE9 g_pTexPush = NULL;						// �Q�[���I�[�o�[�������̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
bool g_bClear;							// �N���A�������ǂ���
bool g_bPushResult;						// �v�b�V���������ꂽ��
int g_nCntPushResult;					// �v�b�V���{�^���̕ϐ�
int g_nCntEnterResult;					// �v�b�V���{�^���̕ϐ�
bool g_bEnterResult;					// �v�b�V���������ꂽ��
float g_fResultMove;					// ���S�̕ϐ�
int g_nCntLogoMove;						// ���S�̕ϐ�



//*****************************************************************************************************************
// ����������
//*****************************************************************************************************************
HRESULT InitResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ������
	g_nCntPushResult = 0;
	g_nCntEnterResult = 40;
	g_bPushResult = true;
	g_fResultMove = 18.0f;
	g_nCntLogoMove = 0;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG002.jpg", &g_apTexClear[RESULT_CLEAR_BG]);				// �Q�[���N���A�w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GAME CLEAR01.png", &g_apTexClear[RESULT_CLEAR_LOGO]);	// �Q�[���N���A���S
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexClear[RESULT_CLEAR_PUSH]);	// �Q�[���N���A���S

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG000.jpg", &g_apTexGameOver[RESULT_OVER_BG]);			// �Q�[���I�[�o�[�̔w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GAME OVER00.png", &g_apTexGameOver[RESULT_OVER_LOGO]);	// �Q�[���I�[�o�[�̃��S
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexGameOver[RESULT_OVER_PUSH]);	// �G���^�[���S

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++, pVtx += 4)
	{
		// �Q�[���N���A�A�Q�[���I�[�o�[�̔w�i�ݒ�
		if (nCntResult == RESULT_CLEAR_BG)
		{
			// ���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		// �Q�[���N���A�A�Q�[���I�[�o�[�̃��S�ݒ�
		else if (nCntResult == RESULT_CLEAR_LOGO)
		{
			// ���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1000.0f, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 200.0f, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		else if (nCntResult == RESULT_CLEAR_PUSH)
		{
			// ���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(900.0f, 700.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 650.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1250.0f, 650.0f, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		// rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	// ���U���g�pBGM
	PlaySound(SOUND_LABEL_BGM003);

	return S_OK;
}

//*****************************************************************************************************************
// �I������
//*****************************************************************************************************************
void UninitResult(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++)
	{
		// �e�N�X�`���̊J��
		if (g_apTexClear[nCntResult] != NULL)
		{
			g_apTexClear[nCntResult]->Release();
			g_apTexClear[nCntResult] = NULL;
		}

		// �e�N�X�`���̊J��
		if (g_apTexGameOver[nCntResult] != NULL)
		{
			g_apTexGameOver[nCntResult]->Release();
			g_apTexGameOver[nCntResult] = NULL;
		}
	}

	//if (g_pTexPush != NULL)
	//{
	//	g_pTexPush->Release();
	//	g_pTexPush = NULL;
	//}

}
//*****************************************************************************************************************
//�@�X�V����
//*****************************************************************************************************************
void UpdateResult(void)
{
	VERTEX_2D *pVtx;

	// �G���^�[�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		StopSound(SOUND_LABEL_BGM003);	// �T�E���h���~�߂�
		SetFade(FADE_OUT,MODE_TITLE);	// �t�F�[�h�����A�^�C�g����ʂɑJ�ڂ���
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++, pVtx += 4)
	{
		if (nCntResult == RESULT_CLEAR_LOGO)
		{
			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(1000.0f - g_fResultMove * g_nCntLogoMove, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f - g_fResultMove * g_nCntLogoMove, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1600.0f - g_fResultMove * g_nCntLogoMove, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1600.0f - g_fResultMove * g_nCntLogoMove, 200.0f, 0.0f);

			if (g_fResultMove * g_nCntLogoMove <= 650)
			{	
				g_nCntLogoMove++;
			}
		}

		// �v�b�V���G���^�[�̓_�ŏ���
		if (nCntResult == RESULT_CLEAR_PUSH)
		{
			g_nCntPushResult++;

			if (g_nCntPushResult >= g_nCntEnterResult)
			{
				if (g_bPushResult == true)
				{
					// ���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPushResult = false;
				}

				else if (g_bPushResult == false)
				{
					// ���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPushResult = true;
				}
				g_nCntPushResult = 0;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

}

//*****************************************************************************************************************
// ���U���g�̕`�揈��
//*****************************************************************************************************************
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++)
	{
		// �Q�[���N���A������
		if (g_bClear == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexClear[nCntResult]);
		}

		// �Q�[���I�[�o�[�̎�
		if (g_bClear == false)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexGameOver[nCntResult]);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);
	}
}

//*****************************************************************************************************************
// ���U���g�̐ݒ�
//*****************************************************************************************************************
void SetResult(bool bClear)
{
	g_bClear = bClear;
}