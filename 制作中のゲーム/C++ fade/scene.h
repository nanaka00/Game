//======================================================================================================
//
// メイン処理 [scene.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "main.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************
#define MAX_SCENE (128)	// シーンの最大数


//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CScene
{
public:

	//*************************
	// オブジェクトの種類
	//*************************
	typedef enum 
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_ENEMY,		// 敵
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_LIFE,		// ライフ
		OBJTYPE_MAX,		
	}OBJTYPE;

	CScene();
	virtual ~CScene();
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nCntScene);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetScale(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetScale(D3DXVECTOR3 scale);

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdeteAll(void);
	static void DrawAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_SCENE];	// シーンのインスタンス生成
	static int		m_nNumAll;				// オブジェクトの総数
	int				m_nID;					// 格納先の番号
	OBJTYPE			m_objType;				// オブジェクトの種類
	D3DXVECTOR3     m_Pos;					// 位置
	D3DXVECTOR3     m_Scale;				// 大きさ

};
#endif