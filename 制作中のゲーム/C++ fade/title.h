//=================================================================================================================
//
// �^�C�g���̏����@�ktitle.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_


//*******************************************************************************************************
// �O���錾
//*******************************************************************************************************


//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************
#define MAX_TITLE_BG (4)		// �w�i�̍ő吔
#define TITLE_SPEED_1 (0.001f)	// ��O�̔w�i�̃X�s�[�h
#define TITLE_SPEED_2 (0.004f)	// �^�񒆂̔w�i�̃X�s�[�h
#define TITLE_SPEED_3 (0.0001f)	// ���̔w�i�̃X�s�[�h

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CTitle : public CScene
{
public:
	typedef enum
	{
		TITLE_BG = 0,
		TITLE_DOT1,
		TITLE_DOT2,
		TITLE_ENTER,
		TITLE_MAX
	}TITLE;

	CTitle();
	~CTitle();
	static CTitle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void EnterUI(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE_BG];	// �w�i�̃e�N�X�`���[�|�C���^
	CScene2D *m_apScene2D[MAX_TITLE_BG];				// �|���S���̃|�C���^
	D3DXCOLOR m_ButtonCol;								// �{�^���̕ϐ�
	float AddCol = 0.0f;								// ���Z�̕ϐ�
	int m_nCntPush;										// �J�E���^�[
	bool m_bPush;										// ���������ǂ���
	float m_fSpeed[MAX_TITLE_BG];						// �w�i�̃X�s�[�h
	float m_fPosTexU[MAX_TITLE_BG];						// �e�N�X�`��U���W
	float m_fPosTexV[MAX_TITLE_BG];						// �e�N�X�`��V���W

};



//=================================================================================================================
// �v���g�^�C�v�錾
//=================================================================================================================

#endif // !_TITLE_H_


