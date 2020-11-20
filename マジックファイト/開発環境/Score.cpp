//=================================================================================================================
//
// �X�R�A�̏����@�kScore.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "Score.h"

//=================================================================================================================
//�}�N����`
//=================================================================================================================
#define MAX_SCORE (8)								//�X�R�A�̍ő包��
#define NUMBER_SIZE_X (40.0f)						//�T�C�Y�̉���
#define NUMBER_SIZE_Y (80.0f)						//�T�C�Y�̏c��


//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
int g_nScore;				//�X�R�A

//*****************************************************************************************************************
// �X�R�A�̏���������
//*****************************************************************************************************************
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nScore = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureScore);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++, pVtx += 4)
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
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�X�R�A�̏I������
//*****************************************************************************************************************
void UninitScore(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//*****************************************************************************************************************
//	�X�R�A�̍X�V����
//*****************************************************************************************************************
void UpdateScore(void)
{

}

//*****************************************************************************************************************
//	�X�R�A�̕`�揈��
//*****************************************************************************************************************
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//*****************************************************************************************************************
//	�X�R�A���Z����
//*****************************************************************************************************************
void AddScore(int nValue)
{
	//�ϐ��錾
	int aNumber[8];
	g_nScore += nValue;

	//�\���̂̃|�C���^�[
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�X�R�A�̊i�[
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++,pVtx += 4)
	{
		//��������i�[
		aNumber[nCntScore] = (g_nScore / (int)powf(10.0f, (float)MAX_SCORE - (nCntScore + 1.0f)));

		//�e�N�X�`�����W�̐ݒ�(N�̏��ԁj
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntScore] * 0.1f), 1.0f / 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntScore] * 0.1f), 1.0f /1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntScore] * 0.1f), 0.0);

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//*****************************************************************************************************************
//	�X�R�A�̃e�N�X�`�����W�̍X�V
//*****************************************************************************************************************
void SetTextureScore(int nIdx,int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx +=(nIdx * 4);

	//���_���̐ݒ�(N�̏��ԁj
	pVtx[0].tex =  D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex =  D3DXVECTOR2(0.0f + (0.1f * nNumber), 0);
	pVtx[2].tex =  D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex =  D3DXVECTOR2(0.1f + (0.1f * nNumber), 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

