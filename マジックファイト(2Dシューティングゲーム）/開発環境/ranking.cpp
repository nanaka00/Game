//=================================================================================================================
//
// �����L���O�̏����@�kranking.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "ranking.h"

//=================================================================================================================
//�}�N����`
//=================================================================================================================
#define MAX_RANKING (8)								//�X�R�A�̍ő包��


//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;

//*****************************************************************************************************************
// �X�R�A�̏���������
//*****************************************************************************************************************
HRESULT InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureRanking);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++, pVtx += 4)
	{

		//���_���W�̐ݒ� (XYZ)�iUpdate�����Ȃ����̂́A�����ŏ����ʒu�����߂�j
		pVtx[0].pos = D3DXVECTOR3(40.0f + (nCntScore * 35.0f), 100.0f, 0.0f);	//���()�̒����{����
		pVtx[1].pos = D3DXVECTOR3(40.0f + (nCntScore * 35.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(100.0f + (nCntScore * 35.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f + (nCntScore * 35.0f), 10.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�X�R�A�̏I������
//*****************************************************************************************************************
void UninitRanking(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
}

//*****************************************************************************************************************
//	�X�R�A�̍X�V����
//*****************************************************************************************************************
void UpdateRanking(void)
{

}

//*****************************************************************************************************************
//	�X�R�A�̕`�揈��
//*****************************************************************************************************************
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRanking);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//*****************************************************************************************************************
//	�X�R�A�̕`�揈��
//*****************************************************************************************************************
void OldScore(void)
{
	
}

