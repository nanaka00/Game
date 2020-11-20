//=================================================================================================================
//
// �G�̏����@�kenemy.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "enemy.h"
#include "explosion.h"
#include "Score.h"
#include "sound.h"
#include "bullet.h"
#include "player.h"
#include <time.h>
#include <cmath>

//=================================================================================================================
//	�}�N����`		(cpp���ł����g��Ȃ��}�N����cpp�ɁA���ɂ́A�ق��ɂ��g�����̂�����j
//=================================================================================================================


//=================================================================================================================
//	�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//================================================================================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//�e�N�X�`���[�ւ̔z��̃|�C���^�[
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^�[
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̏��
int g_TimeCnt;

//*****************************************************************************************************************
// �G�̏���������
//*****************************************************************************************************************
HRESULT InitEnemy(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	srand((unsigned int)time(0));
	g_TimeCnt = 0;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

//===================
//�e�N�X�`���̓ǂݍ���
//===================
	//�{�u
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE3.png", &g_apTextureEnemy[ENEMYTYPE_BOB]);

	//�ڋ�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE1.png", &g_apTextureEnemy[ENEMYTYPE_EYE]);

	//�L
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE2.png", &g_apTextureEnemy[ENEMYTYPE_CAT]);


	//�O���[�o���ϐ��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{

		//���_���W�̐ݒ� (XYZ)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

	return S_OK;

	//�ϐ���atan2f(//�G��X�|�v���C���[��X�A�G��Y�|�v���C���[��Y)//�G�ƃv���C���[�̊p�x
		//D3DXVECTOR3�isinf(D3DX_PI+�ϐ�)*�X�s�[�h,cosf(D3DX_PI-�ϐ�)*�X�s�[�h,0.0f)����������[�u�ɓ����

}

//*****************************************************************************************************************
// �G�̏I������
//*****************************************************************************************************************
void UninitEnemy(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	for (int nCntTex = 0; nCntTex < ENEMYTYPE_MAX; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************************************************
//�@�G�̍X�V����
//*****************************************************************************************************************
void UpdateEnemy(void)
{
	//�ϐ��錾
	ENEMY *pEnemy;			//�G�̃|�C���^
	pEnemy = &g_aEnemy[0];	//�G�̃|�C���^�ɓG�̔z�������
	VERTEX_2D *pVtx;
	g_TimeCnt++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		//�g�p���Ă���Ȃ�
		if (pEnemy->bUse == true)
		{
			//�ʒu�̍X�V
			pEnemy->pos += pEnemy->move;

			//���_���W�̐ݒ� (XYZ)
			SetVertexEnemy(nCntEnemy);

			//�G�̒e
			if (rand() % 300 == 0)
			{
				SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y + (60 / 4.0f), 0.0f),
					BULLET_PLAYER_SIZE, D3DXVECTOR3(-5.0f, 5.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_ENEMY);
				SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y + (60 / 4.0f), 0.0f),
					BULLET_PLAYER_SIZE, D3DXVECTOR3(5.0f, 5.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_ENEMY);
				//�ϐ���atan2f(//�G��X�|�v���C���[��X�A�G��Y�|�v���C���[��Y)//�G�ƃv���C���[�̊p�x
				//D3DXVECTOR3�isinf(D3DX_PI+�ϐ�)*�X�s�[�h,cosf(D3DX_PI-�ϐ�)*�X�s�[�h,0.0f)����������[�u�ɓ����

			}

			//�����`�F�b�N
			if (pEnemy->nLife <= 0)
			{
				//���g�p�ɂ���
				pEnemy->bUse = false;
			}

			//��ʊO�`�F�b�N
		}

		//�G�̏��
		switch (g_aEnemy[nCntEnemy].state)
		{
		case ENEMYSTATE_DAMAGE:
			g_aEnemy[nCntEnemy].nCounterState--;
			if (g_aEnemy[nCntEnemy].nCounterState <= 0)		//�_���[�W���󂯂����ƒʏ�ɂȂ�
			{
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

				//���_�J���[
				pVtx[0 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			break;
		}

	}

	//��Ŋ֐���������G�̃����_���o��
	if (g_TimeCnt % 200 == 0)
	{
		int nPosH = rand() % 350 + 50; //100-400 ->200-800
		int nPosE = rand() % 350 + 450; //100-200 ->300-600
		int nPosC = rand() % 350 + 850; //100-300 ->500->1500
		int nType = rand() % 3;
		switch (nType)
		{
		case 0:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_BOB);			//��̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_EYE);			//�ڋʂ̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_CAT);			//�L�̔z�u
			break;
		case 1:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_EYE);			//��̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_CAT);			//�ڋʂ̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_BOB);			//�L�̔z�u
			break;
		case 2:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_CAT);			//��̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_BOB);			//�ڋʂ̔z�u

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_EYE);			//�L�̔z�u
			break;
		default:
			break;
		}

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
// �G�̕`�揈��
//*****************************************************************************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		//�����g���Ă���Ȃ�
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);	
																			
		}
	}
}

//*****************************************************************************************************************
// �G�̐ݒ菈��
//*****************************************************************************************************************
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	VERTEX_2D *pVtx;	//�֐������Ă��邩�獡�͎g���Ă��Ȃ�
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//���������т���
			pEnemy->pos = pos;		//pos��pEnemy->pos�ɓ����
			pEnemy->type = type;	//type��pEnemy->type�ɓ����

			//���_���W�̐ݒ�
			SetVertexEnemy(nCntEnemy);

			//������
			pEnemy->move = D3DXVECTOR3(0,0,0);
			pEnemy->bUse = true;

			//��ނ��Ƃ̕s�ς̒l�����т���
			switch (pEnemy->type)
			{
			case ENEMYTYPE_BOB:		//�U���K�j�̐ݒ�
				pEnemy->nLife = ENEMY_LIFE_BOB;
				pEnemy->size = ENEMY_SIZE_BOB;
				pEnemy->move = ENEMY_MOVE_BOB;
				break;

			case ENEMYTYPE_EYE:
				pEnemy->nLife = ENEMY_LIFE_EYE;
				pEnemy->size = ENEMY_SIZE_EYE;
				pEnemy->move = ENEMY_MOVE_EYE;
				break;

			case ENEMYTYPE_CAT:
				pEnemy->nLife = ENEMY_LIFE_CAT;
				pEnemy->size = ENEMY_SIZE_CAT;
				pEnemy->move = ENEMY_MOVE_CAT;
				break;
			}
			break;	//for�𔲂��邽��
		}
		pVtx += 4;	//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
// �G�̎擾����
//*****************************************************************************************************************
ENEMY *GetEnemy(void)
{
	//�z��̍ŏ�����|�C���^�œn��
	return &g_aEnemy[0];
}

//*****************************************************************************************************************
//	�G�̒��_���W�̐ݒ�
//*****************************************************************************************************************
void SetVertexEnemy(int nCntEnemy)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEnemy;		

	//���_���̐ݒ�(N�̏��ԁj(Enemy�j
	pVtx[0].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(-(g_aEnemy[nCntEnemy].size.x / 2), +(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[1].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(-(g_aEnemy[nCntEnemy].size.x / 2), -(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[2].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(+(g_aEnemy[nCntEnemy].size.x / 2), +(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[3].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(+(g_aEnemy[nCntEnemy].size.x / 2), -(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
//	�G�̓����蔻��
//*****************************************************************************************************************
bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;

	//�G�Ƀ_���[�W��^�����Ƃ����_����邩
	AddScore(100);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;
	if (g_aEnemy[nIdx].nLife <= 0)		//���C�t��0�ɂȂ�����g���Ă��Ȃ�����
	{
		g_aEnemy[nIdx].bUse = false;
		
		//�G��|�������ɉ��_����邩
		switch (g_aEnemy[nIdx].type)
		{
		case ENEMYTYPE_BOB:
			AddScore(500);
			break;

		case ENEMYTYPE_EYE:
			AddScore(500);
			break;

		case ENEMYTYPE_CAT:
			AddScore(700);
			break;

		default:
			break;
		}
		
		//�����Ƃ��̃T�E���h
		SetExplosion(g_aEnemy[nIdx].pos, g_aEnemy[nIdx].size);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		return true;
	}
	else
	{
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 5;

		//���_�J���[
		pVtx[0 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[1 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[2 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[3 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		
		return false;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}