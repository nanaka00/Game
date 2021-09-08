//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Maeno Nanaka
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"

//*******************************************************************************************************
// ���C�u�����t�@�C���̃����N
//*******************************************************************************************************

//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	//*****************************************************************************
	// �T�E���h�t�@�C��
	//*****************************************************************************
	typedef enum
	{
		//SOUND_LABEL_BGM000 = 0,		// BGM	�^�C�g��
		//SOUND_LABEL_BGM001,			// BGM	�Q�[��
		//SOUND_LABEL_BGM002,			// BGM	�{�X
		//SOUND_LABEL_BGM003,			// BGM	���U���g
		SOUND_LABEL_SE_SHOT = 0,		// �e���ˉ�
		//SOUND_LABEL_SE_HIT,			// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		//{ "data/BGM/bgm007.wav", -1 },		// �^�C�g��
		//{ "data/BGM/bgm010.wav", -1 },		// �Q�[��
		//{ "data/BGM/bgm008.wav", -1 },		// ���U���g
		{ "data/SE/shot003.wav", 0 },		// �e���ˉ�
		//{ "data/SE/hit002.wav", 0 },		// �q�b�g��
		{ "data/SE/explosion000.wav", 0 },	// ������
	};

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
