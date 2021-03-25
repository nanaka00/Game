//=================================================================================================================
//
// �c�@�̏����@�klife.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "life.h"
#include "player.h"

//=================================================================================================================
//�}�N����`
//=================================================================================================================
#define MAX_LIFE (4)	//�c��̃��C�t

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
bool bLife;	//
int g_nLife;

//*****************************************************************************************************************
// �c�@�̏���������
//*****************************************************************************************************************
HRESULT InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�������C�t
	g_nLife = 4;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Life00.png", &g_pTextureLife);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++, pVtx += 4)
	{
		//���_���W�̐ݒ� (XYZ)
		pVtx[0].pos = D3DXVECTOR3(900.0f + (nCntLife * 70.0f), 100.0f, 0.0f);	//���()�̒����{����
		pVtx[1].pos = D3DXVECTOR3(900.0f + (nCntLife * 70.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1000.0f + (nCntLife *70.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f + (nCntLife *70.0f), 10.0f, 0.0f);

		//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�c�@�̏I������
//*****************************************************************************************************************
void UninitLife(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
}

//*****************************************************************************************************************
//	�c�@�̍X�V����
//*****************************************************************************************************************
void UpdateLife(void)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();
	g_nLife = pPlayer->nLife / 10;
}

//*****************************************************************************************************************
//	�c�@�̕`�揈��
//*****************************************************************************************************************
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureLife);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
	}
}
