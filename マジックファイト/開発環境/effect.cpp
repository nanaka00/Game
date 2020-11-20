////=================================================================================================================
////
//// 2D�Q�[���̏����@�kmain.cpp�l
//// Anthor:Nanaka maemo
////
////=================================================================================================================
//#include "explosion.h"	//�C���N���[�h�t�@�C��
//#include "enemy.h"
//#include "bullet.h"
//
////=================================================================================================================
////�}�N����`
////=================================================================================================================
//#define MAX_EXPLOSION (256)	//���j�̍ő吔
//
////=================================================================================================================
////���j�̍\����
////=================================================================================================================
//typedef struct
//{
//	D3DXVECTOR3 pos;	//�ʒu
//	D3DXVECTOR3 size;	//�傫��
//	int nCounterAnim;	//�A�j���[�V�����J�E���^�[
//	int nPatternAnim;	//�A�j���[�V�����p�^�[��No.
//	bool bUse;			//�g�p���Ă��邩�ǂ���
//}EXPLOSION;
//
////=================================================================================================================
////�O���[�o���ϐ��icpp���ŋ��ʂł����̒l�j
////=================================================================================================================
//LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
//EXPLOSION g_aExplosion[MAX_EXPLOSION];							//�e�̏��
//
//																//*****************************************************************************************************************
//																//	���j�̏���������
//																//*****************************************************************************************************************
//HRESULT InitExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	VERTEX_2D *pVtx;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_pTextureExplosion);
//
//
//	//�O���[�o���ϐ��̏������i�e�̏��̏�����)
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
//	//���_�o�b�t�@�̐���
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
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
//	{
//
//		//���_���W�̐ݒ� (XYZ)
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//rhw�̐ݒ�i�i�i�i�i�i�i�QD�ł����g��Ȃ��j�j�j�j�j�j
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//���_���̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
//		pVtx[1].tex = D3DXVECTOR2(0, 0);
//		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.125f, 0);
//
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//
//	return S_OK;
//}
//
//
//
//
////*****************************************************************************************************************
////	���j�̏I������
////*****************************************************************************************************************
//void UninitExplosion(void)
//{
//	//���_�o�b�t�@�̊J��
//	if (g_pVtxBuffExplosion != NULL)
//	{
//		g_pVtxBuffExplosion->Release();
//		g_pVtxBuffExplosion = NULL;
//	}
//
//	//�e�N�X�`���̊J��
//	if (g_pTextureExplosion != NULL)
//	{
//		g_pTextureExplosion->Release();
//		g_pTextureExplosion = NULL;
//	}
//}
//
////*****************************************************************************************************************
////	���j�̍X�V����
////*****************************************************************************************************************
//void UpdateExplosion(void)
//{
//	//�ϐ��錾
//	EXPLOSION *pExplosion;
//	pExplosion = &g_aExplosion[0];
//	VERTEX_2D *pVtx;
//
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++, pVtx += 4)
//	{
//		//�g�p���Ă���Ȃ�
//		if (pExplosion->bUse == true)
//		{
//			//�A�j���[�V�����J�E���^�[�̍X�V
//			pExplosion->nCounterAnim++;
//
//			//���_���W�̐ݒ� (XYZ)
//			SetVertexExplosion(pExplosion->nPatternAnim, nCntExplosion);
//
//			if (pExplosion->nCounterAnim % 6 == 0)
//			{
//				pExplosion->nPatternAnim++;
//
//				if (pExplosion->nPatternAnim > 8)
//				{
//					//���g�p�ɂ���
//					pExplosion->bUse = false;
//					pExplosion->nCounterAnim = 0;
//					pExplosion->nPatternAnim = 0;
//					pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//					pExplosion->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//				}
//			}
//		}
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//}
//
////*****************************************************************************************************************
////	���j�̕`�揈��
////*****************************************************************************************************************
//void DrawExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
//	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pTextureExplosion);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{
//			//�|���S���̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);	//
//		}
//	}
//}
//
////*****************************************************************************************************************
////	�����̐ݒ�
////*****************************************************************************************************************
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 size)
//{
//	//�ϐ��錾
//	VERTEX_2D *pVtx;	//�֐������Ă��邩�獡�͎g���Ă��Ȃ�
//	EXPLOSION *pExplosion;
//	pExplosion = &g_aExplosion[0];
//
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
//	{
//		//����
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
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//}
//
//
////*****************************************************************************************************************
////	���j�̒��_���W�̐ݒ�
////*****************************************************************************************************************
//void SetVertexExplosion(int nPatternAnim, int nCntExplosion)
//{
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	//pVtx�����킹��
//	pVtx += 4 * nCntExplosion;
//
//	//���_���̐ݒ�(N�̏��ԁj
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
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//}