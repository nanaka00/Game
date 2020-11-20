//=================================================================================================================
//
// �^�C�g���̏����@�ktitle.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//=================================================================================================================
// �}�N����`
//=================================================================================================================

//=================================================================================================================
//�@�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexResult[MAX_TITLE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
int g_Title;

//*****************************************************************************************************************
// �^�C�g���̏���������
//*****************************************************************************************************************
HRESULT InitTitle(void)
{


	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG002.jpg", &g_apTexResult[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\chara.png", &g_apTexResult[TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cyara.png", &g_apTexResult[TITLE_LOGO2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MAGICFIGHT�@LOGO1.png", &g_apTexResult[TITLE_TITLE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MAGICFIGHT�@LOGO.png", &g_apTexResult[TITLE_MINI]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexResult[TITLE_PUSH]);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_BG)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 0, 100, 255);
		}

		else if (nCntTitle == TITLE_LOGO)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(900.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH + 500.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 500.0f, 0.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		else if (nCntTitle == TITLE_LOGO2)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-400.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(-400.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(350.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(350.0f, 0.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		}

		else if (nCntTitle == TITLE_TITLE)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(370, 370, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(370, 100, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(870, 370, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(870, 100, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 40, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 140, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 40, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 140, 0, 255);
		}
		else if (nCntTitle == TITLE_MINI)
		{
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(350, 350, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(350, 250, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(470, 350, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(470, 250, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 240, 0, 255);
		}
		else if (nCntTitle == TITLE_PUSH)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(325, 650, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(325, 600, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(925, 650, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(925, 600, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		}

		//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
	PlaySound(SOUND_LABEL_BGM000);	//�^�C�g�����̃T�E���h
	return S_OK;
}

//*****************************************************************************************************************
// �^�C�g���̏I������
//*****************************************************************************************************************
void UninitTitle(void)
{
	
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexResult[nCntTitle] != NULL)
		{
			g_apTexResult[nCntTitle]->Release();
			g_apTexResult[nCntTitle] = NULL;
		}
	}
}

//*****************************************************************************************************************
//�@�^�C�g���̍X�V����
//*****************************************************************************************************************
void UpdateTitle(void)
{

	//�G���^�[�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		
		StopSound(SOUND_LABEL_BGM000);	//�T�E���h���~�߂� 
		SetFade(FADE_OUT, MODE_RULE);	//�Q�[����ʂɔ�ԁ��t�F�[�h�A�E�g
	}
}
//*****************************************************************************************************************
// �^�C�g���̕`�揈��
//*****************************************************************************************************************
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexResult[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}
