//=================================================================================================================
//
// eΜ@kbullet.cppl
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"
//=================================================================================================================
//ρ^
//=================================================================================================================
typedef enum
{
	BULLETTYRE_PLAYER = 0,	//vC[Μe
	BULLETTYRE_ENEMY,		//GΜe
	BULLETTYRE_MAX
}BULLETTYRE;

//=================================================================================================================
//}Nθ`
//=================================================================================================================
#define BULLET_PLAYER_LIFE (30)								//vC[ΜeΜυ½
#define BULLET_PLAYER_SIZE (D3DXVECTOR3(15.0f,15.0f,0.0f))	//vC[ΜeΜε«³
#define BULLET_ENEMY_SIZE (D3DXVECTOR3(15.0f,15.0f,0.0f))	//vC[ΜeΜε«³

//=================================================================================================================
//vg^CvιΎ
//=================================================================================================================
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, BULLETTYRE type);
void SetVertexBullet(int nCntBullet);

#endif