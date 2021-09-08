//======================================================================================================
//
//	�e�̏��� [bullet.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"
#include "player.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "score.h"
#include "game.h"


//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************


//*******************************************************************************************************
// �ÓI�����o�ϐ��錾
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CBullet::CBullet()
{
	// 0�N���A
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CBullet::~CBullet()
{

}


//======================================================================================================
// �e�̏���������
//======================================================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	// ������
	m_Scale = scale;
	m_Move = move;
	m_nLife = BULLET_LIFE;

	CScene2D::Init(pos, scale);

	return S_OK;

}

//======================================================================================================
// �e�̏I������
//======================================================================================================
void  CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//======================================================================================================
// �e�̍X�V����
//======================================================================================================
void  CBullet::Update(void)
{	
	// �T�E���h�̎擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// �X�R�A�̎擾����
	CScore *pScore;
	pScore = CGame::GetScore();

	// ���C�t���P�Â��炷
	m_nLife--;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	// �ړ��ʂ��ʒu�ɔ��f
	pos -= m_Move;

	// �ʒu�̐ݒ�
	SetPosition(pos, m_Scale);

	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		// �V�[���̎擾����
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();
			
			if (objType == OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = pScene->GetPosition();
				D3DXVECTOR3 EnemyScale = pScene->GetScale();

				// �����蔻��̌v�Z
				if (pos.y - (m_Scale.y / 2) <= EnemyPos.y + (EnemyScale.y / 3.5) &&
					pos.y + (m_Scale.y / 2) >= EnemyPos.y - (EnemyScale.y / 3.5) &&
					pos.x + (m_Scale.x / 2) >= EnemyPos.x - (EnemyScale.x / 3.5) &&
					pos.x - (m_Scale.x / 2) <= EnemyPos.x + (EnemyScale.x / 3.5))
				{
					// �X�R�A�̉��Z����
					pScore->AddScore(100);

					// ���j�̐���
					CExplosion::Create(EnemyPos, D3DXVECTOR3(45.0f, 45.0f, 0.0f));	// �G�����񂾂Ƃ��̔��j����

					// ���j�̃T�E���h
					pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

					// �G�̔j��
					pScene->Uninit();

					// �e�̔j��
					Uninit();

					return;
				}
			}
		}
	}

	if (m_nLife < 0)
	{
		// ���j�̐���
		CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		// ���j�̃T�E���h
		pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

		Uninit();

		return;
	}

	// ��ʊO�ɏo�������
	if (pos.y + m_Scale.y / 2.0f < 0.0f || pos.y - m_Scale.y / 2.0f > SCREEN_HEIGHT ||
		pos.x - m_Scale.x / 2.0f > SCREEN_WIDTH || pos.x + m_Scale.x / 2.0f < 0.0f)
	{
		Uninit();

		return;
	}	
}

//======================================================================================================
// �e�̕`�揈��
//======================================================================================================
void  CBullet::Draw(void)
{
	CScene2D::Draw();
}

//======================================================================================================
// �e�̐�������
//======================================================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	pBullet->Init(pos, scale,move);
	pBullet->BindTexture(m_pTexture);


	return pBullet;
}

//======================================================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//======================================================================================================
HRESULT CBullet::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�X�}�C��.png", &m_pTexture);

	return S_OK;
}

//======================================================================================================
// �e�N�X�`���̔j������
//======================================================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
