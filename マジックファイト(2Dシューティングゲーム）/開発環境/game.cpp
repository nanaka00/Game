//=================================================================================================================
//
// �Q�[���̏����@�kgame.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "main.h"
#include "game.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "Score.h"
#include "explosion.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "light.h"
#include "pause.h"
#include "result.h"
#include "time.h"
#include "fade.h"
#include "life.h"

//=================================================================================================================
//	�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
//================================================================================================================
bool g_bPause = false;	// �|�[�Y�������ꂽ��

//*****************************************************************************************************************
//�@�Q�[����ʂ̏���������
//*****************************************************************************************************************
HRESULT InitGame(void)
{

	Initbg();			// �w�i
	InitPlayer();		// �v���C���[
	InitEnemy();		// �G
	InitBullet();		// �e
	InitScore();		// �X�R�A
	InitExplosion();	// ���j
	InitLight();		// ���C�g
	InitPause();		// �|�[�Y
	InitTime();			// �^�C�}�[
	InitLife();			// �c�@

	PlaySound(SOUND_LABEL_BGM001);	// �T�E���h�J�n

	return S_OK;
}


//*****************************************************************************************************************
//�@�Q�[����ʂ̏I������
//*****************************************************************************************************************
void UninitGame(void)
{
	g_bPause = false;

	StopSound();
	Uninitbg();			// �w�i
	UninitPlayer();		// �v���C���[
	UninitBullet();		// �e		
	UninitEnemy();		// �G
	UninitScore();		// �X�R�A
	UninitExplosion();	// ���j
	UninitLight();		// ���C�g
	UninitPause();		// �|�[�Y
 	UninitTime();		// �^�C�}�[
	UninitLife();		// �c�@
}
//*****************************************************************************************************************
//�@�Q�[����ʂ̍X�V����
//*****************************************************************************************************************
void UpdateGame(void)
{

	// �|�[�Y�{�^�����������Ƃ�
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	if(g_bPause == true)
	{
		UpdatePause();		// �|�[�Y
	}
	else
	{
		UpdatePlayer();		// �v���C���[
		Updatebg();			// �w�i
		UpdateBullet();		// �e
		UpdateEnemy();		// �G
		UpdateExplosion();	// ���j
		UpdateScore();		// �X�R�A
		UpdateLight();		// ���C�g
		UpdateTime();		// �^�C�}�[
		UpdateFade();		// �t�F�[�h
		UpdateLife();		// �c�@
	}
	
}

//*****************************************************************************************************************
//�@�Q�[����ʂ̕`�揈��
//*****************************************************************************************************************
void DrawGame(void)
{
	Drawbg();			// �w�i
	DrawEnemy();		// �G
	DrawBullet();		// �e
	DrawPlayer();		// �v���C���[
	DrawExplosion();	// ���j
	DrawLight();		// ���C�g
	DrawScore();		// �X�R�A
	DrawTime();			// �^�C�}�[
	DrawLife();			// �c�@

	// �|�[�Y��ʂ̎�
	if (g_bPause == true)
	{
		DrawPause();	// �|�[�Y
	}
}
//*****************************************************************************************************************
// �|�[�Y�̐ݒ�
//*****************************************************************************************************************
void SetPause(bool bPause)
{
	g_bPause = bPause;
}