//=================================================================================================================
//
// �|�[�Y�̏����@�kpause.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "pause.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"

//=================================================================================================================
//	�}�N����`
//=================================================================================================================
#define MAX_PAUSE (5)	//�|�[�Y�̎��

//=================================================================================================================
//	�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexPause[MAX_PAUSE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
bool g_bPausse;
int g_nPointNow;
int g_nPoint;

//*****************************************************************************************************************
//	�|�[�Y�̏���������
//*****************************************************************************************************************
HRESULT InitPause(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//������
	g_nPoint = 1;
	g_nPointNow = 1;
	g_bPausse = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hawaiisbx.jpg", &g_apTexPause[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CONTINUE00.png", &g_apTexPause[PAUSE_MENE_CONTINOE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\RETRY00.png", &g_apTexPause[PAUSE_MENE_RETRY]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\QUIT00.png", &g_apTexPause[PAUSE_MENE_QUIT]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\point000.png", &g_apTexPause[PAUSE_MENE_POINT]);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++, pVtx += 4)
	{
		{
		if (nCntPause == 0)
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);

		}

		if (nCntPause == 1)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 350, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 300, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 350, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 300, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 2)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 450, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 400, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 450, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 400, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 3)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 550, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 550, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 500, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 4)
		{		
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(450.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(450.0f, 300.0f + g_nPoint, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 300.0f + g_nPoint, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 225, 255);
		}
		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�|�[�Y�̏I������
//*****************************************************************************************************************
void UninitPause(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	for (int nCntPause = 0; nCntPause <MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexPause[nCntPause] != NULL)
		{
			g_apTexPause[nCntPause]->Release();
			g_apTexPause[nCntPause] = NULL;
		}
	}
}

//*****************************************************************************************************************
//	�|�[�Y�̍X�V����
//*****************************************************************************************************************
void UpdatePause(void)
{
	VERTEX_2D *pVtx;

	//S�L�[����������(���Ɉړ�)
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_nPoint += 100;
		g_nPointNow++;

		if (g_nPointNow > PAUSE_MENE_QUIT)		//QUIT��艺�̎�
		{
			g_nPointNow = PAUSE_MENE_CONTINOE;	
		}
		if (g_nPoint >= 300)
		{
			g_nPoint -= 300;
		}
	}



	//W�L�[����������(��Ɉړ�)
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_nPoint -= 100;
		g_nPointNow--;
		if (g_nPointNow < PAUSE_MENE_CONTINOE)	//�R���e�j���[����̎�
		{
			g_nPointNow = PAUSE_MENE_QUIT;
		}
		if (g_nPoint <= 0)
		{
			g_nPoint += 300;
		}
	}
	//�G���^�[�Ń|�[�Y�̌���
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		if (g_nPointNow == PAUSE_MENE_CONTINOE)
		{
			SetPause(false);
		}

		if (g_nPointNow == PAUSE_MENE_RETRY)
		{
			StopSound(SOUND_LABEL_BGM000);	//�T�E���h���~�߂� 
			SetFade(FADE_OUT, MODE_GAME);	//�Q�[����ʂɔ�ԁ��t�F�[�h�A�E�g
		}

		if (g_nPointNow == PAUSE_MENE_QUIT)
		{
			StopSound(SOUND_LABEL_BGM001);	//�T�E���h���~�߂�
			SetFade(FADE_OUT, MODE_TITLE);	//�t�F�[�h�A�E�g�����ă��U���g��ʂɔ��
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ� (XYZ)
	pVtx[16].pos = D3DXVECTOR3(450.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(450.0f, 300.0f + g_nPoint, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(500.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(500.0f, 300.0f + g_nPoint, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

}

//*****************************************************************************************************************
//	�|�[�Y�̕`�揈��
//*****************************************************************************************************************
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexPause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}
