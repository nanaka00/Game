//======================================================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_


//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"


//*******************************************************************************************************
// �O���錾
//*******************************************************************************************************
class CFade;

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:

#ifdef _DEBUG
	void DrawFPS(void);
#endif

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9      m_pTexture = NULL;		// �e�N�X�`���̃|�C���^
	D3DXVECTOR3             m_posPolygon;			// �|���S���̈ʒu
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^


};
#endif

