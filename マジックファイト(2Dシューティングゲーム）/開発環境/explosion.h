//=================================================================================================================
//
// 爆破の処理　〔explosion.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetVertexExplosion(int nPatternAnim,int nCntExplosoin);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size);
#endif
