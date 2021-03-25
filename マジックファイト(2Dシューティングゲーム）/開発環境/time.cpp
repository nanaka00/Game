//=================================================================================================================
//
// �^�C�}�[�̏����@�ktime.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "time.h"
#include "result.h"
#include "fade.h"

//=================================================================================================================
//�}�N����`
//=================================================================================================================
#define MAX_TIME (3)

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufTime = NULL;
int g_nTime;
int g_nCntTime;

//*****************************************************************************************************************
// �^�C�}�[�̏���������
//*****************************************************************************************************************
HRESULT InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	g_nCntTime = 130;
	g_nTime = 44;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufTime,
		NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureTime);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{

		//���_���W�̐ݒ� (XYZ)�iUpdate�����Ȃ����̂́A�����ŏ����ʒu�����߂�j
		pVtx[0].pos = D3DXVECTOR3(500.0f + (nCntTime * 55.0f), 100.0f, 0.0f);	//���()�̒����{����
		pVtx[1].pos = D3DXVECTOR3(500.0f + (nCntTime * 55.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600.0f + (nCntTime * 55.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600.0f + (nCntTime * 55.0f), 10.0f, 0.0f);

		//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 10, 200, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufTime->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�^�C�}�[�̏I������
//*****************************************************************************************************************
void UninitTime(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBufTime != NULL)
	{
		g_pVtxBufTime->Release();
		g_pVtxBufTime = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//*****************************************************************************************************************
//	�^�C�}�[�̍X�V����
//*****************************************************************************************************************
void UpdateTime(void)
{
	VERTEX_2D *pVtx;
	int aNumber[8];

	if (g_nTime != 0)
	{
		g_nCntTime -= 1;
	}
	if (g_nCntTime == 0)
	{
		g_nTime -= 1;
		g_nCntTime = 60;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{
		aNumber[nCntTime] = (g_nTime / (int)powf(10.0f, (float)(MAX_TIME - (nCntTime + 1))));

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufTime->Unlock();

	if (g_nTime == 0)
	{
		SetResult(true);
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//*****************************************************************************************************************
//	�^�C�}�[�̕`�揈��
//*****************************************************************************************************************
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBufTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}
//*****************************************************************************************************************
//	�^�C�}�[�̃e�N�X�`�����W�̍X�V
//*****************************************************************************************************************
void SetTextureTime(int nIdx, int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	//���_���̐ݒ�(N�̏��ԁj
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 0);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufTime->Unlock();
}

