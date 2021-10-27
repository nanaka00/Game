//#include "polygon.h"
//#include "input.h"


//*****************************************************************************************************************
////グローバル変数
//*****************************************************************************************************************
//LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
//int g_nCounterAnim;			//アニメーションカウンター
//int g_nPatternAnim;			//アニメーションパターンNo.
//D3DXVECTOR3 g_posPolygon;		//ポリゴンの位置
//D3DXVECTOR3 g_movePolygon;	//移動量


//*****************************************************************************************************************
////ポリゴンの初期化処理
//*****************************************************************************************************************
//HRESULT InitPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	VERTEX_2D *pVtx;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファの生成
//	if (FAILED(pDevice->CreateVertexBuffer(
//		sizeof(VERTEX_2D) * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffPolygon,
//		NULL)))
//	{
//		return E_FAIL;
//	}
//
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice, "TEXTURE\\runningman102.png", &g_pTexturePolygon);
//
//	//0にする
//	g_nCounterAnim = 0;
//	g_nPatternAnim = 0;
//
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//
//	//頂点情報の設定
//	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y - 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y + 50, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y - 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y + 50, 0.0f);
//
//	//頂点情報の設定
//	pVtx[0].tex = D3DXVECTOR2(0, 0.5f);
//	pVtx[1].tex = D3DXVECTOR2(0, 0);
//	pVtx[2].tex = D3DXVECTOR2(0.2f, 0.5f);
//	pVtx[3].tex = D3DXVECTOR2(0.2f, 0);
//
//	//頂点座標の設定 (XYZ)
//	pVtx[0].pos = D3DXVECTOR3(100, 300, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(100, 200, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(300, 300, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(300, 200, 0.0f);
//
//	//
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//頂点カラー
//	pVtx[0].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[1].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[2].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[3].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//
//	//初期値設定
//	g_posPolygon = D3DXVECTOR3(100, 200, 0.0f);
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffPolygon->Unlock();
//
//	return S_OK;
//}
//
//*****************************************************************************************************************
////ポリゴン終了処理
//*****************************************************************************************************************
//void UninitPolygon(void)
//{
//	//頂点バッファの開放
//	if (g_pVtxBuffPolygon != NULL)
//	{
//		g_pVtxBuffPolygon->Release();
//		g_pVtxBuffPolygon = NULL;
//	}
//
//	//テクスチャの開放
//	if (g_pTexturePolygon != NULL)
//	{
//		g_pTexturePolygon->Release();
//		g_pTexturePolygon = NULL;
//	}
//}
//*****************************************************************************************************************
////ポリゴンの更新処理
//*****************************************************************************************************************
//void UpdatePolygon(void)
//{
//	//変数宣言
//	static int Wall = 1;
//	static int Move = 5;
//	VERTEX_2D *pVtx;
//	g_nCounterAnim++;	//アニメーションカウンターの更新
//	static float TexY = 0.0;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	if ((g_nCounterAnim % 8) == 0)
//	{
//		g_nPatternAnim++;
//
//		g_nCounterAnim = 0;
//
//		//頂点情報の設定
//		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y - 50, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y + 50, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y - 50, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y + 50, 0.0f);
//
//

//			//ポリゴンが壁に当たった時
//			//if (g_posPolygon.x + 100 >= 800 || g_posPolygon.x <= -150)
//			//{
//			//	Move *= -1;
//			//	Wall *= -1;
//			//}
//		}
//	}
//
//	/*if (g_nPatternAnim == 5)
//	{
//	TexY = 0.5f;
//	}
//
//	if (g_nPatternAnim == 10)
//	{
//	TexY = 0;
//	g_nPatternAnim = 0;
//	}*/
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffPolygon->Unlock();
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	if (Wall <= 0)
//	{
//		pVtx[0].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0, TexY + 0.5f);
//		pVtx[1].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0, TexY + 0);
//		pVtx[2].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0.2f, TexY + 0.5f);
//		pVtx[3].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0.2f, TexY + 0);
//	}
//	else if (Wall >= 0)
//	{
//		pVtx[0].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0.2f, TexY + 0.5f);
//		pVtx[1].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0.2f, TexY + 0);
//		pVtx[2].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0, TexY + 0.5f);
//		pVtx[3].tex = D3DXVECTOR2(((float)g_nPatternAnim * 0.2f) + 0, TexY + 0);
//	}
//
//	////ポリゴンの位置を更新
//	//g_posPolygon.x += Move;
//	//g_posPolygon.y += 4;
//
//	////頂点座標の更新
//	//pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x, 400, 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x, 200, 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, 400, 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100,200, 0.0f);
//
//	//頂点バッファをアンロックする
//	g_pVtxBuffPolygon->Unlock();
//

//*****************************************************************************************************************
////ポリゴンの描画処理
//*****************************************************************************************************************
//void DrawPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリームに設立
//	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, g_pTexturePolygon);
//
//	//ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//}