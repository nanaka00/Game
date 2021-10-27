//=================================================================================================================
//
// �e�̏����@�kbullet.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "bullet.h"	// �C���N���[�h�t�@�C��
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "Score.h"
#include "player.h"

//=================================================================================================================
// �}�N����`
//=================================================================================================================
#define MAX_BULLET (256)


//=================================================================================================================
//	�e�̍\����
//=================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 size;	// �傫��
	D3DXVECTOR3 move;	// �ړ���
	int nLife;			// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
	BULLETTYRE type;	// ���
}BULLET;


//=================================================================================================================
//	�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				// �e�̃e�N�X�`���[���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// �e�̃o�b�t�@���
BULLET g_aBullet[MAX_BULLET];							// �e�̏��
 

//*****************************************************************************************************************
//	�e�̏���������
//*****************************************************************************************************************
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bulled-light-yellow.png", &g_pTextureBullet);
	
	// �O���[�o���ϐ��̏������i�e�̏��̏�����)
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		// ���_���W�̐ݒ� (XYZ)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[1].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[2].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[3].col = D3DCOLOR_RGBA(250, 0, 250, 255);

		// ���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	�e�̏I������
//*****************************************************************************************************************
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}


//*****************************************************************************************************************
//	�e�̍X�V����
//*****************************************************************************************************************
void UpdateBullet(void)
{
	// �ϐ��錾
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pBullet = &g_aBullet[0];
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++, pVtx += 4)
	{
		// �g�p���Ă���Ȃ�
		if (pBullet->bUse == true)
		{
			// �ʒu�̍X�V
			pBullet->pos += pBullet->move;

			if (pBullet->type == BULLETTYRE_PLAYER)
			{ // �G�Ƃ̓����蔻��
				// �G���擾
				pEnemy = GetEnemy();

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					// �G���g���Ă���Ȃ�
					if (pEnemy->bUse == true)
					{
						// �����蔻��̌v�Z
						if (pBullet->pos.y - (pBullet->size.y / 2) <= pEnemy->pos.y + (pEnemy->size.y / 2) &&
							pBullet->pos.y + (pBullet->size.y / 2) >= pEnemy->pos.y - (pEnemy->size.y / 2) &&
							pBullet->pos.x + (pBullet->size.x / 2) >= pEnemy->pos.x - (pEnemy->size.x / 2) &&
							pBullet->pos.x - (pBullet->size.x / 2) <= pEnemy->pos.x + (pEnemy->size.x / 2))
						{
							// �_���[�W��
							HitEnemy(nCntEnemy, 10);

							// �q�b�g�����Ƃ��̃T�E���h
							PlaySound(SOUND_LABEL_SE_HIT);

							// ���g�p�ɂ���
							pBullet->bUse = false;
						}
					}
				}
			}
			// �G�̒e
			else if (pBullet->type == BULLETTYRE_ENEMY)
			{// �v���C���[�Ƃ̓����蔻��

				// �f�o�C�X�̎擾
				pPlayer = GetPlayer();

				if (pBullet->pos.y - (pBullet->size.y / 2) <= pPlayer->pos.y + (pPlayer->size.y / 2) &&
					pBullet->pos.y + (pBullet->size.y / 2) >= pPlayer->pos.y - (pPlayer->size.y / 2) &&
					pBullet->pos.x + (pBullet->size.x / 2) >= pPlayer->pos.x - (pPlayer->size.x / 2) &&
					pBullet->pos.x - (pBullet->size.x / 2) <= pPlayer->pos.x + (pPlayer->size.x / 2))
				{
					// �_���[�W��
					HitPlayer(10);

					// �q�b�g�����Ƃ��̃T�E���h
					PlaySound(SOUND_LABEL_SE_HIT);

					// ���g�p�ɂ���
					pBullet->bUse = false;
				}
			}
		}

		// ���_���W�̐ݒ� (XYZ)
		SetVertexBullet(nCntBullet);

		// 1�t���[�����ƂɃ��C�t�����炷
		pBullet->nLife--;

		// �e�̎����`�F�b�N
		if (pBullet->nLife <= 0)
		{
			// ���g�p�ɂ���
			pBullet->bUse = false;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//*****************************************************************************************************************
//	�e�̕`�揈��
//*****************************************************************************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

  	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);	//
		}
	}
}
//*****************************************************************************************************************
//	�e�̐ݒ�
//*****************************************************************************************************************
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, BULLETTYRE type)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;		// �֐������Ă��邩�獡�͎g���Ă��Ȃ�
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		// ����
		if (pBullet->bUse == false)
		{
			pBullet->pos = pos;
			pBullet->size = size;

			// ���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			// �������ނ��т���
			pBullet->move = move;
			pBullet->bUse = true;
			pBullet->nLife = nLife;
			pBullet->type = type;
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//*****************************************************************************************************************
//	�e�̒��_���W�̐ݒ�
//*****************************************************************************************************************
void SetVertexBullet(int nCntBullet)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	// pVtx�����킹��
	pVtx += 4 * nCntBullet;

	// ���_���̐ݒ�(N�̏��ԁj
	pVtx[0].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(-(g_aBullet[nCntBullet].size.x / 2), +(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[1].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(-(g_aBullet[nCntBullet].size.x / 2), -(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[2].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(+(g_aBullet[nCntBullet].size.x / 2), +(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[3].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(+(g_aBullet[nCntBullet].size.x / 2), -(g_aBullet[nCntBullet].size.y / 2), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
