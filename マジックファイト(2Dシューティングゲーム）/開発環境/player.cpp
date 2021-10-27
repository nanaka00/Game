//=================================================================================================================
//
// �v���C���[�̏����@�kplayer.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "player.h"	// �C���N���[�h�t�@�C��
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "enemy.h"
#include "explosion.h"
#include "light.h"
#include "fade.h"
#include"result.h"

//=================================================================================================================
//	�}�N����`
//=================================================================================================================
#define PLAYER_SPEED (7.0f)	// �v���C���[�ړ��̑���
#define PLAYER_SIZE (60.0f)	// �v���C���[�̃T�C�Y

//=================================================================================================================
//�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�̃|�C���^
PLAYER g_Player;

//*****************************************************************************************************************
//	�v���C���[�̏���������
//*****************************************************************************************************************
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	// �v���C���[�̃��C�t
	g_Player.nLife = PLAYER_LIFE;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\chara.png", &g_pTexturePlayer);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// �e�N�X�`�����̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	// rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �����l�ݒ�
	g_Player.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 3.5 / 4), 0.0f);
	 
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//�@�v���C���[�̏I������
//*****************************************************************************************************************
void UninitPlayer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//*****************************************************************************************************************
//�@�v���C���[�̍X�V����
//*****************************************************************************************************************

void UpdatePlayer(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;		// �v���C���[�̃|�C���^
	ENEMY *pEnemy;			// �G�̃|�C���^
	

	// ��ނ��Ƃ̕s�ς̒l�����т���
	g_Player.size = PLAYER_SIZE2;
	
	// �v���C���[�̈ړ�
	ControlPlayer();

	// Space�L�[�������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		// �e�̔���(�T�E���h�j
		PlaySound(SOUND_LABEL_SE_SHOT);

		// �e�̔��ˈʒu�̐ݒ�
		// ����
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);

		// �E�΂�
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(5.0f, -10.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);

		// ���΂�
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(-5.0f, -10.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);
	}
	
	// ��ʊO����̊֐��i���_���̐ݒ������ł���j
	StayPlayer();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �v���C���[�̏��
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.nCounterstate--;
		
		if (g_Player.nCounterstate % 4 < 2)
		{
			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_Player.nCounterstate % 4 >= 2)
		{
			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		}

		if (g_Player.nCounterstate < 0)
		{
			// ���_�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			
			g_Player.nCounterstate = PLAYERSTATE_NORMAL;
		}
	}

	// ���_���̐ݒ�(N�̏��ԁj(Player)
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE / 2), g_Player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE / 2), g_Player.pos.y - (PLAYER_SIZE / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE / 2), g_Player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE / 2), g_Player.pos.y - (PLAYER_SIZE / 2), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
	
	pPlayer = GetPlayer();
	pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			// �G�ƃv���C���[�̓����蔻��
			if (pEnemy->pos.y - (pEnemy->size.y / 2) <= pPlayer->pos.y + (pPlayer->size.y / 2) &&
				pEnemy->pos.y + (pEnemy->size.y / 2) >= pPlayer->pos.y - (pPlayer->size.y / 2) &&
				pEnemy->pos.x + (pEnemy->size.x / 2) >= pPlayer->pos.x - (pPlayer->size.x / 2) &&
				pEnemy->pos.x - (pEnemy->size.x / 2) <= pPlayer->pos.x + (pPlayer->size.x / 2))
			{
				// �q�b�g�����Ƃ��̃T�E���h
				PlaySound(SOUND_LABEL_SE_HIT);

				HitPlayer(10);
			}
		}
	}
}		

//*****************************************************************************************************************
//�@�v���C���[�̕`�揈��
//*****************************************************************************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************************************************************************************************************
//	�v���C���[�ړ��̑���
//*****************************************************************************************************************
void ControlPlayer(void)
{
	if (GetKeyboardPress(DIK_L) == false)
	{
		// �L�[�{�[�h����
		// �E�iD)�ɉ����ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_D) == true)
		{
			// D��W�������ꂽ�ꍇ
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Player.pos.x += sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y -= cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			// D��S�������ꂽ�ꍇ
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.pos.x += sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y += cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			else
			{
				g_Player.pos.x += PLAYER_SPEED;
			}
		}

		// ���iA�j�������ꂽ�ꍇ
		else if (GetKeyboardPress(DIK_A) == true)
		{	// A��W�������ɉ����ꂽ�ꍇ
			if (GetKeyboardPress(DIK_W) == true)
			{
				// �΂߈ړ��̌v�Z
				g_Player.pos.x -= sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y -= cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}

			// A��S�������ɉ����ꂽ�ꍇww
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.pos.x -= sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y += cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			else
			{
				g_Player.pos.x -= PLAYER_SPEED;
			}
		}

		// ���i���j�������ꂽ�ꍇ
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.pos.y += PLAYER_SPEED;
		}
		// ��iw�j�������ꂽ�ꍇ
		else if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.pos.y -= PLAYER_SPEED;
		}
	}
}

//*****************************************************************************************************************
//	��ʊO����i���_���̐ݒ������ł���j
//*****************************************************************************************************************
void StayPlayer(void)
{
	// ��ʂ̉E�[���v���C���[�̉E�[���o����
	if (g_Player.pos.x + (PLAYER_SIZE / 2) > SCREEN_WIDTH-150)
	{
		// �E�[�Ńv���C���[���~�߂�
		g_Player.pos.x = SCREEN_WIDTH-150 - (PLAYER_SIZE / 2);
	}

	// ��ʂ̉��[���v���C���[�̉��[���o����
	if (g_Player.pos.y + (PLAYER_SIZE / 2) > SCREEN_HEIGHT)
	{
		g_Player.pos.y = SCREEN_HEIGHT - (PLAYER_SIZE / 2);
	}

	// ��ʂ̍��[���v���C���[�̍��[���o����
	if (g_Player.pos.x - (PLAYER_SIZE / 2) < 100)
	{
		g_Player.pos.x = 100 + (PLAYER_SIZE / 2);
	}

	// ��ʂ̏�[���v���C���[�̏�[���o����
	if (g_Player.pos.y - (PLAYER_SIZE / 2) <  100)
	{
		g_Player.pos.y = 100 + (PLAYER_SIZE / 2);
	}
}

//*****************************************************************************************************************
// �v���C���[�̎擾����
//*****************************************************************************************************************
PLAYER *GetPlayer(void)
{
	// �|�C���^��Ԃ�
	return &g_Player;
}

//*****************************************************************************************************************
// �v���C���[�̓����蔻��
//*****************************************************************************************************************
bool HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;		// �v���C���[�̃��C�t����G�̒e�̃_���[�W������
	if (g_Player.nLife <= 0)		// ���C�t��0�ɂȂ�����
	{
		g_Player.state = PLAYERSTATE_DEATH;
		SetExplosion(g_Player.pos, g_Player.size);	// ����
		PlaySound(SOUND_LABEL_SE_EXPLOSION);		// ���j�T�E���h
		StopSound(SOUND_LABEL_BGM001);				// �T�E���h���~�߂�
		SetResult(false);							// �Q�[���I�[�o�[�ɔ��
		SetFade(FADE_OUT, MODE_RESULT);				// �t�F�[�h�A�E�g�����ă��U���g��ʂɔ��

		return true;
	}
	else
	{
		g_Player.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 3.5 / 4), 0.0f);	// �����ʒu�ɖ߂�

		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterstate= 120;

		return false;
	}
}

