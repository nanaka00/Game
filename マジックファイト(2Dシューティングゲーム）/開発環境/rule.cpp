//=================================================================================================================
//
// ���[����ʂ̏����@�krule.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "rule.h"
#include "fade.h"
#include "input.h"

//=================================================================================================================
// �O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexRule[MAX_RULE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;

bool g_bPushRule;			// �v�b�V���������ꂽ��
int g_nCntPushRule;			// �v�b�V���{�^���̕ϐ�
int g_nCntEnterRule;		// �v�b�V���{�^���̕ϐ�
bool g_bEnterRule;			// �v�b�V���������ꂽ��

//*****************************************************************************************************************
// ����������
//*****************************************************************************************************************
HRESULT InitRule(void)
{
	// �ϐ�
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	 
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ������
	g_nCntPushRule = 0;
	g_nCntEnterRule = 40;
	g_bPushRule = true;
	g_bEnterRule = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial000.png", &g_apTexRule[RULE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexRule[RULE_PUSH]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RULE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++, pVtx += 4)
	{
		if (nCntRule == RULE_BG)
		{

			// ���_���W�̐ݒ� (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		else if (nCntRule == RULE_PUSH)
		{

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
	g_pVtxBuffRule->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// �I������
//*****************************************************************************************************************
void UninitRule(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++)
	{
		// �e�N�X�`���̊J��
		if (g_apTexRule[nCntRule] != NULL)
		{
			g_apTexRule[nCntRule]->Release();
			g_apTexRule[nCntRule] = NULL;
		}
	}
}

//*****************************************************************************************************************
//�@�X�V����
//*****************************************************************************************************************
void UpdateRule(void)
{
	VERTEX_2D *pVtx;

	// �G���^�[�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);	// �t�F�[�h���A�Q�[����ʂɑJ�ڂ���
		g_bEnterRule = true;			// �G���^�[������������ɂ���
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++, pVtx += 4)
	{
		// �v�b�V���G���^�[�̓_�ŏ���
		if (nCntRule == RULE_PUSH)
		{
			g_nCntPushRule++;

			if (g_nCntPushRule >= g_nCntEnterRule)
			{
				if (g_bPushRule == true)
				{
					// ���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPushRule = false;
				}

				else if (g_bPushRule == false)
				{
					// ���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPushRule = true;
				}
				g_nCntPushRule = 0;
			}

			// �G���^�[�����ꂽ��
			if (g_bEnterRule == true)
			{
				g_nCntEnterRule = 12;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRule->Unlock();
}
//*****************************************************************************************************************
// ���U���g�̕`�揈��
//*****************************************************************************************************************
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexRule[nCntRule]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRule * 4, 2);
	}
}
