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
//	�񋓌^ (�����̕ϐ��Ɉ�A�̐����l��t����K�v������ꍇ�Ɏg���j
//=================================================================================================================
//�G�̎��
typedef enum
{
	RESULT_000 = 0,	//�V�Ė��@�g���G���h
	RESULT_001,		//�ɂ킩���@�g���G���h
	RESULT_002,		//��l�O�̖��@�g���G���h
	RESULT_003,		//�i�v�s�ł̖��@�g���G���h
	RESULT_004,		//�Q�[���I�[�o�[�G���h
	RESULT_MAX		//��ނ̍ő�l
}RESULT;

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexResult = NULL;
LPDIRECT3DTEXTURE9 g_pTexGameOver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
bool g_bClear;	//

//*****************************************************************************************************************
// ����������
//*****************************************************************************************************************
HRESULT InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM003);

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG006.png", &g_pTexResult);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG004.png", &g_pTexGameOver);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// �I������
//*****************************************************************************************************************
void UninitResult(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexGameOver != NULL)
	{
		g_pTexGameOver->Release();
		g_pTexGameOver = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pTexResult != NULL)
	{
		g_pTexResult->Release();
		g_pTexResult = NULL;
	}
}

//*****************************************************************************************************************
//�@�X�V����
//*****************************************************************************************************************
void UpdateResult(void)
{
	//�G���^�[�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		StopSound(SOUND_LABEL_BGM003);
		SetFade(FADE_OUT,MODE_TITLE); 
	}
}
//********************************************************************** *******************************************
// ���U���g�̕`�揈��
//*****************************************************************************************************************
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�Q�[���N���A������
	if (g_bClear == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexResult);
	}
	else if(g_bClear == false)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexGameOver);
	}
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
}
//*****************************************************************************************************************
// ���U���g�̐ݒ�
//*****************************************************************************************************************
void SetResult(bool bClear)
{
	g_bClear = bClear;
}