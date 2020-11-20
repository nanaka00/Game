//=================================================================================================================
//
// ���C�g�̏����@�kmain.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "light.h"
#include "input.h"
#include "player.h"

//=================================================================================================================
//	�}�N����`
//=================================================================================================================
#define LIGHT_X (1300)		//���C�g�e�N�X�`����X�̒l
#define LIGHT_Y (800)		//���C�g�e�N�X�`����Y�̒l
#define LIGHT_SPEED (6.5f)
#define GAUGE_X_1	(950.0f)
#define GAUGE_X_2	(1250.0f)
#define GAUGE_Y_1	(700.0f)
#define GAUGE_Y_2	(670.0f)

#define MAX_LIGHT (3)

//=================================================================================================================
//	�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexLight[MAX_LIGHT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLight = NULL;
PLAYER g_posLight;		//���C�g�̈ʒu
float g_Light;			//���C�g�̕ϐ�
bool g_bLight;			//���C�g���g���Ă��邩

//*****************************************************************************************************************
//	���C�g�̏���������
//*****************************************************************************************************************
HRESULT InitLight(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//������
	g_Light = 0;
	g_bLight = true;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\light.png", &g_apTexLight[LIGHT_LIGHT]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Gauge00.png", &g_apTexLight[LIGHT_GAUGE]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GaugeW.png", &g_apTexLight[LIGHT_GAUGEW]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_LIGHT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLight,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLight->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++, pVtx += 4)
	{
		if (nCntLight == LIGHT_LIGHT)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT * 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, -SCREEN_HEIGHT, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 245);
		}

		if (nCntLight == LIGHT_GAUGE)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_1, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_2, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntLight == LIGHT_GAUGEW)
		{
			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_1, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_2, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
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
	g_pVtxBuffLight->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	���C�g�̏I������
//*****************************************************************************************************************
void UninitLight(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffLight != NULL)
	{
		g_pVtxBuffLight->Release();
		g_pVtxBuffLight = NULL;
	}

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexLight[nCntLight] != NULL)
		{
			g_apTexLight[nCntLight]->Release();
			g_apTexLight[nCntLight] = NULL;
		}
	}
}

//*****************************************************************************************************************
//	���C�g�̍X�V����
//*****************************************************************************************************************
void UpdateLight(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	//�v���C���[�ƈꏏ�ɓ�����
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLight->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W�̐ݒ� (XYZ)
	pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x -SCREEN_WIDTH, pPlayer->pos.y + SCREEN_HEIGHT * 1.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x -SCREEN_WIDTH, pPlayer->pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH * 1.0f, pPlayer->pos.y + SCREEN_HEIGHT * 1.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH * 1.0f, pPlayer->pos.y - SCREEN_HEIGHT, 0.0f);

	//***************************
	//���C�g�̃Q�[�W�̏���
	//***************************
	//�ϐ��錾
	g_Light -= 1.5f;	//�X�V���邽�уQ�[�W�����炷
	
	//0���傫���Ȃ����烉�C�g���g����
	if (g_Light <= 0)
	{
		g_Light = 0;
		g_bLight = true;
	}

	if (g_bLight == true)
	{
		//���C�g���傫���Ȃ�
		if (GetKeyboardPress(DIK_L) == true)
		{
			g_Light += 3.5f;

			//���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - SCREEN_WIDTH - LIGHT_X, pPlayer->pos.y + SCREEN_HEIGHT + LIGHT_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x - SCREEN_WIDTH - LIGHT_X, pPlayer->pos.y - SCREEN_HEIGHT - LIGHT_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH + LIGHT_X, pPlayer->pos.y + SCREEN_HEIGHT + LIGHT_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH + LIGHT_X, pPlayer->pos.y - SCREEN_HEIGHT - LIGHT_Y, 0.0f);

			//300���傫���Ȃ����烉�C�g���g���Ȃ��Ȃ�
			if (g_Light >= 300)
			{
				g_bLight = false;

			}
		}
	}
	//���_���W�̐ݒ� (XYZ)
	pVtx[4].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(GAUGE_X_2 - g_Light, GAUGE_Y_1, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(GAUGE_X_2 - g_Light, GAUGE_Y_2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLight->Unlock();
}

//*****************************************************************************************************************
//	���C�g�̕`�揈��
//*****************************************************************************************************************
void DrawLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffLight, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexLight[nCntLight]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLight * 4, 2);
	}
}


