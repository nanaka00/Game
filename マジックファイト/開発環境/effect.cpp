////=================================================================================================================
////
//// 2Dゲームの処理　〔main.cpp〕
//// Anthor:Nanaka maemo
////
////=================================================================================================================
//#include "explosion.h"	//インクルードファイル
//#include "enemy.h"
//#include "bullet.h"
//
////=================================================================================================================
////マクロ定義
////=================================================================================================================
//#define MAX_EXPLOSION (256)	//爆破の最大数
//
////=================================================================================================================
////爆破の構造体
////=================================================================================================================
//typedef struct
//{
//	D3DXVECTOR3 pos;	//位置
//	D3DXVECTOR3 size;	//大きさ
//	int nCounterAnim;	//アニメーションカウンター
//	int nPatternAnim;	//アニメーションパターンNo.
//	bool bUse;			//使用しているかどうか
//}EXPLOSION;
//
////=================================================================================================================
////グローバル変数（cpp内で共通でも一つ一つの値）
////=================================================================================================================
//LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
//EXPLOSION g_aExplosion[MAX_EXPLOSION];							//弾の情報
//
//																//*****************************************************************************************************************
//																//	爆破の初期化処理
//																//*****************************************************************************************************************
//HRESULT InitExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	VERTEX_2D *pVtx;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_pTextureExplosion);
//
//
//	//グローバル変数の初期化（弾の情報の初期化)
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].bUse = false;
//
//		g_aExplosion[nCntExplosion].nCounterAnim = 0;
//		g_aExplosion[nCntExplosion].nPatternAnim = 0;
//	}
//
//	//頂点バッファの生成
//	if (FAILED(pDevice->CreateVertexBuffer(
//		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffExplosion,
//		NULL)))
//	{
//		return E_FAIL;
//	}
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
//	{
//
//		//頂点座標の設定 (XYZ)
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//rhwの設定（（（（（（（２Dでしか使わない））））））
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラー
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//頂点情報の設定
//		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
//		pVtx[1].tex = D3DXVECTOR2(0, 0);
//		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.125f, 0);
//
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffExplosion->Unlock();
//
//	return S_OK;
//}
//
//
//
//
////*****************************************************************************************************************
////	爆破の終了処理
////*****************************************************************************************************************
//void UninitExplosion(void)
//{
//	//頂点バッファの開放
//	if (g_pVtxBuffExplosion != NULL)
//	{
//		g_pVtxBuffExplosion->Release();
//		g_pVtxBuffExplosion = NULL;
//	}
//
//	//テクスチャの開放
//	if (g_pTextureExplosion != NULL)
//	{
//		g_pTextureExplosion->Release();
//		g_pTextureExplosion = NULL;
//	}
//}
//
////*****************************************************************************************************************
////	爆破の更新処理
////*****************************************************************************************************************
//void UpdateExplosion(void)
//{
//	//変数宣言
//	EXPLOSION *pExplosion;
//	pExplosion = &g_aExplosion[0];
//	VERTEX_2D *pVtx;
//
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++, pVtx += 4)
//	{
//		//使用しているなら
//		if (pExplosion->bUse == true)
//		{
//			//アニメーションカウンターの更新
//			pExplosion->nCounterAnim++;
//
//			//頂点座標の設定 (XYZ)
//			SetVertexExplosion(pExplosion->nPatternAnim, nCntExplosion);
//
//			if (pExplosion->nCounterAnim % 6 == 0)
//			{
//				pExplosion->nPatternAnim++;
//
//				if (pExplosion->nPatternAnim > 8)
//				{
//					//未使用にする
//					pExplosion->bUse = false;
//					pExplosion->nCounterAnim = 0;
//					pExplosion->nPatternAnim = 0;
//					pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//					pExplosion->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				}
//			}
//		}
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffExplosion->Unlock();
//}
//
////*****************************************************************************************************************
////	爆破の描画処理
////*****************************************************************************************************************
//void DrawExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリームに設立
//	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, g_pTextureExplosion);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{
//			//ポリゴンの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);	//
//		}
//	}
//}
//
////*****************************************************************************************************************
////	爆発の設定
////*****************************************************************************************************************
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size)
//{
//	//変数宣言
//	VERTEX_2D *pVtx;	//関数化しているから今は使っていない
//	EXPLOSION *pExplosion;
//	pExplosion = &g_aExplosion[0];
//
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
//	{
//		//もし
//		if (pExplosion->bUse == false)
//		{
//			pExplosion->pos = pos;
//			pExplosion->size = size;
//			pExplosion->nPatternAnim = 0;
//			pExplosion->nCounterAnim = 0;
//			pExplosion->bUse = true;
//			break;
//		}
//		pVtx += 4;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffExplosion->Unlock();
//}
//
//
////*****************************************************************************************************************
////	爆破の頂点座標の設定
////*****************************************************************************************************************
//void SetVertexExplosion(int nPatternAnim, int nCntExplosion)
//{
//	VERTEX_2D *pVtx;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtxを合わせる
//	pVtx += 4 * nCntExplosion;
//
//	//頂点情報の設定(Nの順番）
//	pVtx[0].pos = g_aExplosion[nCntExplosion].pos + D3DXVECTOR3(-(g_aExplosion[nCntExplosion].size.x / 2), +(g_aExplosion[nCntExplosion].size.y / 2), 0.0f);
//	pVtx[1].pos = g_aExplosion[nCntExplosion].pos + D3DXVECTOR3(-(g_aExplosion[nCntExplosion].size.x / 2), -(g_aExplosion[nCntExplosion].size.y / 2), 0.0f);
//	pVtx[2].pos = g_aExplosion[nCntExplosion].pos + D3DXVECTOR3(+(g_aExplosion[nCntExplosion].size.x / 2), +(g_aExplosion[nCntExplosion].size.y / 2), 0.0f);
//	pVtx[3].pos = g_aExplosion[nCntExplosion].pos + D3DXVECTOR3(+(g_aExplosion[nCntExplosion].size.x / 2), -(g_aExplosion[nCntExplosion].size.y / 2), 0.0f);
//
//	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.0f, 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 0.0f);
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffExplosion->Unlock();
//}