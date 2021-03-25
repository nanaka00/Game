//#include "polygon.h"
//#include "input.h"


//*****************************************************************************************************************
////�O���[�o���ϐ�
//*****************************************************************************************************************
//LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
//int g_nCounterAnim;			//�A�j���[�V�����J�E���^�[
//int g_nPatternAnim;			//�A�j���[�V�����p�^�[��No.
//D3DXVECTOR3 g_posPolygon;		//�|���S���̈ʒu
//D3DXVECTOR3 g_movePolygon;	//�ړ���


//*****************************************************************************************************************
////�|���S���̏���������
//*****************************************************************************************************************
//HRESULT InitPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	VERTEX_2D *pVtx;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@�̐���
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
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, "TEXTURE\\runningman102.png", &g_pTexturePolygon);
//
//	//0�ɂ���
//	g_nCounterAnim = 0;
//	g_nPatternAnim = 0;
//
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//
//	//���_���̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y - 50, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y + 50, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y - 50, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y + 50, 0.0f);
//
//	//���_���̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0, 0.5f);
//	pVtx[1].tex = D3DXVECTOR2(0, 0);
//	pVtx[2].tex = D3DXVECTOR2(0.2f, 0.5f);
//	pVtx[3].tex = D3DXVECTOR2(0.2f, 0);
//
//	//���_���W�̐ݒ� (XYZ)
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
//	//���_�J���[
//	pVtx[0].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[1].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[2].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//	pVtx[3].col = D3DCOLOR_RGBA(225, 225, 225, 0);
//
//	//�����l�ݒ�
//	g_posPolygon = D3DXVECTOR3(100, 200, 0.0f);
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPolygon->Unlock();
//
//	return S_OK;
//}
//
//*****************************************************************************************************************
////�|���S���I������
//*****************************************************************************************************************
//void UninitPolygon(void)
//{
//	//���_�o�b�t�@�̊J��
//	if (g_pVtxBuffPolygon != NULL)
//	{
//		g_pVtxBuffPolygon->Release();
//		g_pVtxBuffPolygon = NULL;
//	}
//
//	//�e�N�X�`���̊J��
//	if (g_pTexturePolygon != NULL)
//	{
//		g_pTexturePolygon->Release();
//		g_pTexturePolygon = NULL;
//	}
//}
//*****************************************************************************************************************
////�|���S���̍X�V����
//*****************************************************************************************************************
//void UpdatePolygon(void)
//{
//	//�ϐ��錾
//	static int Wall = 1;
//	static int Move = 5;
//	VERTEX_2D *pVtx;
//	g_nCounterAnim++;	//�A�j���[�V�����J�E���^�[�̍X�V
//	static float TexY = 0.0;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	if ((g_nCounterAnim % 8) == 0)
//	{
//		g_nPatternAnim++;
//
//		g_nCounterAnim = 0;
//
//		//���_���̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y - 50, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x - 100, g_posPolygon.y + 50, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y - 50, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100, g_posPolygon.y + 50, 0.0f);
//
//

//			//�|���S�����ǂɓ���������
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
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPolygon->Unlock();
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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
//	////�|���S���̈ʒu���X�V
//	//g_posPolygon.x += Move;
//	//g_posPolygon.y += 4;
//
//	////���_���W�̍X�V
//	//pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x, 400, 0.0f);
//	//pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x, 200, 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100, 400, 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100,200, 0.0f);
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPolygon->Unlock();
//

//*****************************************************************************************************************
////�|���S���̕`�揈��
//*****************************************************************************************************************
//void DrawPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
//	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pTexturePolygon);
//
//	//�|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//}