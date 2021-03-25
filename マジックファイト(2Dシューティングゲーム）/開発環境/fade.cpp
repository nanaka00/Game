//=================================================================================================================
//
// �t�F�[�h�̏����@�kfade.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "fade.h"

//=================================================================================================================
// �O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;
FADE g_fade;			//�t�F�[�h�̏��
MODE g_modeNext;		//���̃��[�h(��ʁj
D3DXCOLOR g_colorFade;	//�t�F�[�h�F

//*****************************************************************************************************************
// �t�F�[�h�̏���������
//*****************************************************************************************************************
HRESULT InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\back00.jpg", &g_pTexFade);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_���W�̐ݒ� (XYZ)
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	//rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// �t�F�[�h�̏I������
//*****************************************************************************************************************
void UninitFade(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexFade != NULL)
	{
		g_pTexFade->Release();
		g_pTexFade = NULL;
	}
}

//*****************************************************************************************************************
// �t�F�[�h�̍X�V����
//*****************************************************************************************************************
void UpdateFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	//�����x��1����
	if (g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.03f;

		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}

	else if (g_fade == FADE_OUT)
	{
		g_colorFade.a += 0.03f;

		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;

			SetMode(g_modeNext);
		}
	}
}

//*****************************************************************************************************************
// �t�F�[�h�̕`�揈��
//*****************************************************************************************************************
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************************************************************************************************************
//�@�t�F�[�h�̐ݒ�
//*****************************************************************************************************************
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}

//*****************************************************************************************************************
//�t�F�[�h�̎擾����
//*****************************************************************************************************************
FADE GetFade(void)
{
	return g_fade;
}
