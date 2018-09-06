//**************************************************************************
// �ļ���  VBF_LodMath.inl
// ������  ��Lod�йص���ѧ����(ʵ�ֲ���)
// ���ߣ�  ��Ө 
// ʱ�䣺  2005-1-12
//**************************************************************************

#ifndef __VBF_LOD_MATH_INL__
#define __VBF_LOD_MATH_INL__

#include "VBF_OS.h"
#include "VBF_Common/VBF_Utils/VBF_3DMath.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------------------------
// ������EncodeBlkNo()
// �������Ե��ο���б��룬������ʽΪUINT64������
//----------------------------------------------------------------------------
inline UINT64 EncodeBlkNo(int nLodNo, int nBlkNoX, int nBlkNoY)
{
	if(nLodNo < 0) return 0;

	UINT64 t0 = nLodNo;
	t0 <<= 59;

	UINT64 t1 = nBlkNoX;
	t1 <<= 30;

	return (t0 + t1 + nBlkNoY);
}

//----------------------------------------------------------------------------
// ������DecodeBlkNo()
// �������Ե��ο�ı�Ž��н���
//----------------------------------------------------------------------------
inline void DecodeBlkNo(UINT64 key, int& nLodNo, int& nBlkNoX, int& nBlkNoY)
{
	nLodNo  = (int)(key>>59);	
	nBlkNoX = (int)(key<<5>>35);
	nBlkNoY = (int)(key<<35>>35);
}


//----------------------------------------------------------------------------------------
// ����������GetLodFromMapNo()
// �������������ݵ�ͼ�ļ�������ȡ��Lod����
//----------------------------------------------------------------------------------------
inline int GetLodFromMapNo(const char* szMapNo)
{
	const char* pDst = strchr(szMapNo, '_');
	if(NULL==pDst) return -1;

    //_int64 nPos = pDst - szMapNo;

    // wuyuguo
    int nPos = pDst - szMapNo;

	char szLod[8] = {'\0'};

	VBF_strncpy(szLod, szMapNo, (int)nPos);

	return atoi( szLod );
}

//----------------------------------------------------------------------------------------
// ����������ConnectLod_X_Y16()
// ������������16�������ּ�¼�ļ�������ʽΪ��noLod_nBlkNoX_nBlkNoY
//----------------------------------------------------------------------------------------
inline void ConnectLod_X_Y16(int noLod, int nBlkNoX, int nBlkNoY, char* bufKey)
{
	// ��Ө�޸ģ�2004-10-26
	// ΪʲôҪʹ��16���� ?
	// ��ΪĿǰȱ��atoui64()�������޷����з������
//	char bufT[8];
//	strcpy( bufKey, itoa(noLod,bufT,16) );
//	strcat( bufKey, "_" );
//	strcat( bufKey, itoa(nBlkNoX,bufT,16) );
//	strcat( bufKey, "_" );
//	strcat( bufKey, itoa(nBlkNoY,bufT,16) );

	char bufT[8];
        strcpy( bufKey, itoa(noLod,bufT,10) );
	strcat( bufKey, "_" );
	strcat( bufKey, itoa(nBlkNoX,bufT,10) );
	strcat( bufKey, "_" );
	strcat( bufKey, itoa(nBlkNoY,bufT,10) );
}

/* wuyuguo
//----------------------------------------------------------------------------------------
// ����������GetFileNoFromMapNo()
// �������������ݵ�ͼ�ļ�������ȡ���ļ����к�
//----------------------------------------------------------------------------------------
inline void GetFileNoFromMapNo(const char* szMapNo, int& nFileNoX, int& nFileNoY)
{
	const char* pDst1 = strchr(szMapNo,  '_');	// ��һ�����Ӻŵ�λ��
	const char* pDst2 = strrchr(szMapNo, '_');	// �ڶ������Ӻŵ�λ��
	if(NULL==pDst1 || NULL==pDst2) return;

	_int64 nPos1 = pDst1 - szMapNo;
	_int64 nPos2 = pDst2 - szMapNo;

	char szFileNoX[32] = {'\0'};
	char szFileNoY[32] = {'\0'};

	strncpy(szFileNoX, szMapNo+nPos1+1, (int)(nPos2-1-nPos1));
	strncpy(szFileNoY, szMapNo+nPos2+1, (int)(strlen(szMapNo)-nPos2-1));

	nFileNoX = atoi( szFileNoX );
	nFileNoY = atoi( szFileNoY );
}
*/

//----------------------------------------------------------------------------------------
// ����������GetBlkNoInFileFromCode()
// �������������ݿ����ļ��е�λ�ã����������ļ��е����к�
//----------------------------------------------------------------------------------------
inline void GetBlkNoInFileFromCode(int nCode, int nPerFileBlkNumX, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	nBlkNoInFileX = nCode % nPerFileBlkNumX;
	nBlkNoInFileY = nCode / nPerFileBlkNumX;
}

//----------------------------------------------------------------------------------------
// ������GetPerFileBlkNumXY()
// ����������ÿ���ļ���ʵ�ʱ���Ŀ�����������ΪConfigPar.nPerFileBlkNumX��ConfigPar.nPerFileBlkNumY
//       ����LOD������������û����ô���
//----------------------------------------------------------------------------------------
inline void GetPerFileBlkNumXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod,int& nPerFileBlkNumX,int& nPerFileBlkNumY)
{
	// ��noLod�����ܿ���
	int nTotalBlkNumX = (int)( ConfigPar.nRootBlkNumX * pow(2, (float)noLod) );
	int nTotalBlkNumY = (int)( ConfigPar.nRootBlkNumY * pow(2, (float)noLod) );

	// ÿ���ļ�����Ŀ���
	nPerFileBlkNumX = ConfigPar.nPerFileBlkNumX;
	nPerFileBlkNumY = ConfigPar.nPerFileBlkNumY;

	if( nPerFileBlkNumX > nTotalBlkNumX ) nPerFileBlkNumX = nTotalBlkNumX;
	if( nPerFileBlkNumY > nTotalBlkNumY ) nPerFileBlkNumY = nTotalBlkNumY;
}

//----------------------------------------------------------------------------------------
// ������GetBlkNoFromNoInFile()
// ���������ݿ����ļ��еı��(i,j)��������ȫ����(nBlkNoX,nBlkNoY)
//----------------------------------------------------------------------------------------
inline void GetBlkNoFromNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, const char* szMapNo, int nBlkNoInFileX, int nBlkNoInFileY, int& nBlkNoX, int& nBlkNoY)
{
	int noLod = GetLodFromMapNo(szMapNo);

	int nPerFileBlkNumX;
	int nPerFileBlkNumY;
	GetPerFileBlkNumXY(ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY);

	int nFileNoX;
	int nFileNoY;
	GetFileNoFromMapNo(szMapNo, nFileNoX, nFileNoY);

	nBlkNoX = nFileNoX * nPerFileBlkNumX + nBlkNoInFileX;
	nBlkNoY = nFileNoY * nPerFileBlkNumY + nBlkNoInFileY;
}

//---------------------------------------------------------------------
// ������GetBlkNoInFile()
// ����������ȫ���ţ�����ÿ����ڵ��ļ����Լ����ڸ��ļ��еĿ��
//---------------------------------------------------------------------
inline void GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	assert(nBlkNoX>=0 && nBlkNoY>=0);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );	

	// ���ݿ�ż���ÿ����ļ��еı��
	nBlkNoInFileX = nBlkNoX % nPerFileBlkNumX;
	nBlkNoInFileY = nBlkNoY % nPerFileBlkNumY;	
}

//---------------------------------------------------------------------
// ������GetBlkNoInFile()
// ����������ȫ���ţ�����ÿ����ڵ��ļ����Լ����ڸ��ļ��еĿ��
//---------------------------------------------------------------------
inline void GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	assert(nBlkNoX>=0 && nBlkNoY>=0);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );

	// �����noLod������(nBlkNoX, nBlkNoY) ���ڵ��ļ���
	// ÿ���ļ����� (nPerFileBlkNumX * nPerFileBlkNumY) ����
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;	
	ConnectLod_X_Y16( noLod, nFileNoX, nFileNoY, szMapNo );

	// ���ݿ�ż���ÿ����ļ��еı��
	nBlkNoInFileX = nBlkNoX % nPerFileBlkNumX;
	nBlkNoInFileY = nBlkNoY % nPerFileBlkNumY;	
}

//----------------------------------------------------------------------------------------
// ������GetMapNoFromBlkNo()
// ���������ݿ��ȫ���ţ���ȡ�������ļ��ı��
//----------------------------------------------------------------------------------------
inline void GetMapNoFromBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo)
{
	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );

	// �����noLod������(nBlkNoX, nBlkNoY) ���ڵ��ļ���
	// ÿ���ļ����� (nPerFileBlkNumX * nPerFileBlkNumY) ����
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;
	
	ConnectLod_X_Y16( noLod, nFileNoX, nFileNoY, szMapNo );
}

//----------------------------------------------------------------------------------------
// ������GetMapNoFromBlkKey()
// ���������ݿ�Ļ����ţ���ȡ�������ļ��ı��
//----------------------------------------------------------------------------------------
inline void GetMapNoFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szMapNo)
{
	int nLodNo, nBlkNoX, nBlkNoY;
	DecodeBlkNo(unKey, nLodNo, nBlkNoX, nBlkNoY);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, nLodNo, nPerFileBlkNumX, nPerFileBlkNumY );

	// �����noLod������(nBlkNoX, nBlkNoY) ���ڵ��ļ���
	// ÿ���ļ����� (nPerFileBlkNumX * nPerFileBlkNumY) ����
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;
	
	ConnectLod_X_Y16( nLodNo, nFileNoX, nFileNoY, szMapNo );
}

//----------------------------------------------------------------------------------------
// ������GetTableNameFromBlkKey()
// ���������ݿ�Ļ����ţ���ȡ���������ݿ��ı��
// ˵������������Ӧ�����ļ���һ�£����������ݿ��ж������ֿ�ͷ�ı��������ƣ�
//       ���������(T1_0_0) = T_ + �ļ���(1_0_0)
//----------------------------------------------------------------------------------------
inline void GetTableNameFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szTableName)
{
	char szMapNo[30];
	GetMapNoFromBlkKey( ConfigPar, unKey, szMapNo );

	MapNoToTableName( szMapNo, szTableName );
}

//----------------------------------------------------------------------------
// ������MapNoToTableName()
// ����������MapNo����ȡ��洢�洢��Ԫ��(����ȫ·���ļ���/���ݿ����)
//----------------------------------------------------------------------------
inline void MapNoToTableName(char* szMapNo, char* szTableName)
{
	strcpy( szTableName , "T" );
	strcat( szTableName , szMapNo );
}

//----------------------------------------------------------------------------------------
// ������GetBlkKeyFromBlkCodeInFile()
// ���������ݿ����ڵ��ļ����Լ����ļ��е�λ�ã���ȡ�仺����
//----------------------------------------------------------------------------------------
inline void GetBlkKeyFromBlkCodeInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, const char* szMapNo, int nBlkCode, UINT64& unKey)
{	
	int nLodNo = GetLodFromMapNo( szMapNo );
	
	int nPerFileBlkNumX, nPerFileBlkNumY;
	GetPerFileBlkNumXY( ConfigPar, nLodNo, nPerFileBlkNumX, nPerFileBlkNumY );

	int nBlkNoInFileX, nBlkNoInFileY;
	GetBlkNoInFileFromCode( nBlkCode, nPerFileBlkNumX, nBlkNoInFileX, nBlkNoInFileY );

	int nBlkNoX, nBlkNoY;				
	GetBlkNoFromNoInFile( ConfigPar, szMapNo, nBlkNoInFileX, nBlkNoInFileY, nBlkNoX, nBlkNoY );
	
	unKey = EncodeBlkNo( nLodNo, nBlkNoX, nBlkNoY );
}

//----------------------------------------------------------------------------
// ����������GetSameLodBlkKey()
// ������������ȡ�ĸ�ͬ����Ļ�����(UINT64��): LOD-X-Y
//----------------------------------------------------------------------------
inline void GetSameLodBlkKey(int nLodNo, int nBlkNoX, int nBlkNoY, UINT64 unKeySameLod[4])
{
	int nLowerBlkNoX = nBlkNoX>>1;
	int nLowerBlkNoY = nBlkNoY>>1;

	for(int nr=0; nr<2; nr++)
	{
		for(int nc=0; nc<2; nc++)
		{
			int nBlkNoX = nLowerBlkNoX*2 + nc;
			int nBlkNoY = nLowerBlkNoY*2 + nr;			
			unKeySameLod[nr*2+nc] = EncodeBlkNo(nLodNo, nBlkNoX, nBlkNoY);
		}
	}
}

//----------------------------------------------------------------------------
// ����������GetBlkSize()
// ������������k��ÿһ��Ĵ�С(��λ: ��)
//----------------------------------------------------------------------------
inline void GetBlkSize(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, double& dBlkSizeX, double& dBlkSizeY)
{	
	dBlkSizeX = (ConfigPar.dGlobalX1 - ConfigPar.dGlobalX0)/(ConfigPar.nRootBlkNumX*pow(2,(float)nLodNo));
	dBlkSizeY = (ConfigPar.dGlobalY1 - ConfigPar.dGlobalY0)/(ConfigPar.nRootBlkNumY*pow(2,(float)nLodNo));
}

//----------------------------------------------------------------------------
// ����������GetBlkNoFromLB()
// ��������������ĳ���LOD����;�γ�ȣ����������ڵ�ȫ����ο�
//----------------------------------------------------------------------------
inline void GetBlkNoFromLB(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, double L, double B, int& nBlkNoX, int& nBlkNoY)
{
	// �����k��ÿһ��Ĵ�С(��λ: ��)	
	double dBlkSizeX, dBlkSizeY;
	::GetBlkSize(ConfigPar, nLodNo, dBlkSizeX, dBlkSizeY);

	// ����õ����ڵ�ȫ����ο�
	nBlkNoX = int( (L-ConfigPar.dGlobalX0)/dBlkSizeX );
	nBlkNoY = int( (B-ConfigPar.dGlobalY0)/dBlkSizeY );
}

//----------------------------------------------------------------------------
// ����������GetBlkBound()
// ��������������LOD����Ϳ�ţ�����ÿ�ľ�γ�ȷ�Χ
//----------------------------------------------------------------------------
inline void GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, int nBlkNoX, int nBlkNoY, 
						double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1)
{	
	// �����k��ÿһ��Ĵ�С(��λ: ��)	
	double dBlkSizeX, dBlkSizeY;
	::GetBlkSize(ConfigPar, nLodNo, dBlkSizeX, dBlkSizeY);

	dBlkX0 = dBlkSizeX * nBlkNoX + ConfigPar.dGlobalX0;
	dBlkY0 = dBlkSizeY * nBlkNoY + ConfigPar.dGlobalY0;
	dBlkX1 = dBlkX0 + dBlkSizeX;	
	dBlkY1 = dBlkY0 + dBlkSizeY;
}

//----------------------------------------------------------------------------
// ����������GetBlkBound()
// �������������ݿ��ȫ���ţ�����ÿ�ľ�γ�ȷ�Χ
//----------------------------------------------------------------------------
inline void GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unBlkKey, 
						double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1)
{	
	int nLodNo, nBlkNoX, nBlkNoY;
	DecodeBlkNo( unBlkKey, nLodNo, nBlkNoX, nBlkNoY );

	GetBlkBound( ConfigPar, nLodNo, nBlkNoX, nBlkNoY, dBlkX0, dBlkY0, dBlkX1, dBlkY1 );
}



//----------------------------------------------------------------------------
// ����������UINT64toString()
// ������������INT64������ת���16���ַ����ַ�������Ϊ���ο�(��һ����¼)�����ݿ��е�����
//----------------------------------------------------------------------------
inline void UINT64toString(UINT64 key, char* buf)
{
	_ui64toa( key, buf, 16 );
	buf[16] = '\0';
}

//----------------------------------------------------------------------------
// ����������BuildSQL()
// �������������ݵ��ο���ڴ��ţ�����SQL��ѯ���
//----------------------------------------------------------------------------
inline void BuildSQL(UINT64 key, const char* szTableName, char* szSQL)
{
	char buf[BLKKEY_LENGTH+1];
	UINT64toString(key, buf);
	
	strcpy(szSQL, "SELECT * FROM ");
	strcat(szSQL, szTableName);
	strcat(szSQL, " WHERE ID = '");
	strcat(szSQL, buf);
	strcat(szSQL, "'");
}

//----------------------------------------------------------------------------------------
// ������GetLowerBlkNo()
// ��������ȡָ�������ڵͼ����XY���
//----------------------------------------------------------------------------------------
inline void GetLowerBlkNo(int nLodNo, int nBlkNoX, int nBlkNoY, int& nLowerLodNo, int& nLowerBlkNoX, int& nLowerBlkNoY)
{
	if(nLodNo==0)  // �������:��0��
	{
		nLowerLodNo  = nLodNo;
		nLowerBlkNoX = nBlkNoX;
		nLowerBlkNoY = nBlkNoY;
	}
	else
	{
		nLowerLodNo  = nLodNo-1;
		nLowerBlkNoX = nBlkNoX/2;
		nLowerBlkNoY = nBlkNoY/2;
	}
}

//----------------------------------------------------------------------------------------
// ������GetLowerBlkKey()
// ��������ȡָ�������ڵͼ����ȫ����
//----------------------------------------------------------------------------------------
inline UINT64 GetLowerBlkKey(UINT64 unBlkKey)
{
	int nLodNo, nBlkNoX, nBlkNoY;
	::DecodeBlkNo(unBlkKey, nLodNo, nBlkNoX, nBlkNoY);	

	return ::GetLowerBlkKey(nLodNo, nBlkNoX, nBlkNoY);
}

//----------------------------------------------------------------------------------------
// ������GetLowerBlkKey()
// ��������ȡָ�������ڵͼ����ȫ����
//----------------------------------------------------------------------------------------
inline UINT64 GetLowerBlkKey(int nLodNo, int nBlkNoX, int nBlkNoY)
{
	int nLodNoLower, nBlkNoXLower, nBlkNoYLower;
	::GetLowerBlkNo(nLodNo, nBlkNoX, nBlkNoY, nLodNoLower, nBlkNoXLower, nBlkNoYLower);

	return ::EncodeBlkNo(nLodNoLower, nBlkNoXLower, nBlkNoYLower);
}

//----------------------------------------------------------------------------------------
// ������GetBlkNoMax()
// ��������ȡָ��Lod�����XY��ŵ����ֵ
//----------------------------------------------------------------------------------------
inline void GetBlkNoMax(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int& nBlkNoXMax, int& nBlkNoYMax)
{
	nBlkNoXMax = (int)( ConfigPar.nRootBlkNumX * pow(2, (float)noLod) ) - 1;
	nBlkNoYMax = (int)( ConfigPar.nRootBlkNumY * pow(2, (float)noLod) ) - 1;
}

//----------------------------------------------------------------------------------------
// ������GetLowerNeighborBlkNo()
// ��������ȡ��ĳ���߽��ϵĵͼ����ڿ��ȫ����
//----------------------------------------------------------------------------------------
inline void GetLowerNeighborBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, VBF_BLK_EDGE nBlkEdge, int nBlkNoX, int nBlkNoY, VBF_BLK_EDGE& nLowerNeighBlkEdge, int& nLowerNeighBlkNoX, int& nLowerNeighBlkNoY)
{	
	int nModX = nBlkNoX % 2;  // X�����ű�2��֮�������(Ϊ0��1)
	int nModY = nBlkNoY % 2;  // Y�����ű�2��֮�������(Ϊ0��1)

	switch(nBlkEdge)
	{
		case VBF_BLK_EDGE_LEFT:   { nLowerNeighBlkEdge = VBF_BLK_EDGE_RIGHT;   nLowerNeighBlkNoX = nBlkNoX/2-1;      nLowerNeighBlkNoY = (nBlkNoY-nModY)/2;  break; }
		case VBF_BLK_EDGE_RIGHT:  { nLowerNeighBlkEdge = VBF_BLK_EDGE_LEFT;    nLowerNeighBlkNoX = (nBlkNoX-1)/2+1;  nLowerNeighBlkNoY = (nBlkNoY-nModY)/2;  break; }
		case VBF_BLK_EDGE_TOP:    { nLowerNeighBlkEdge = VBF_BLK_EDGE_BOTTOM;  nLowerNeighBlkNoY = nBlkNoY/2-1;      nLowerNeighBlkNoX = (nBlkNoX-nModX)/2;  break; }
		case VBF_BLK_EDGE_BOTTOM: { nLowerNeighBlkEdge = VBF_BLK_EDGE_TOP;     nLowerNeighBlkNoY = (nBlkNoY-1)/2+1;  nLowerNeighBlkNoX = (nBlkNoX-nModX)/2;  break; }
	}	
	
	// �������Ե����������
	int nLowerBlkNoXMax, nLowerBlkNoYMax;
	GetBlkNoMax( ConfigPar, noLod-1, nLowerBlkNoXMax, nLowerBlkNoYMax );
	
	// ����߿�������ڵͼ���Ϊ��X=nLowerBlkNoXMax
	// ���ұ߿�������ڵͼ���Ϊ��X=0
	// ���ϱ߿�������ڵͼ���Ϊ��Y=0
	// ���±߿�������ڵͼ���Ϊ��Y=nLowerBlkNoYMax

	if(nBlkEdge==VBF_BLK_EDGE_LEFT && nBlkNoX==0)                   
		nLowerNeighBlkNoX = nLowerBlkNoXMax;

	else if(nBlkEdge==VBF_BLK_EDGE_RIGHT && nBlkNoX==nLowerBlkNoXMax)
		nLowerNeighBlkNoX = 0;

	else if( nBlkEdge==VBF_BLK_EDGE_TOP && nBlkNoY==0 )	            
		nLowerNeighBlkNoY = 0;

	else if( nBlkEdge==VBF_BLK_EDGE_BOTTOM && nBlkNoY==nLowerBlkNoYMax )	
		nLowerNeighBlkNoY = nLowerBlkNoYMax;
}

//----------------------------------------------------------------------------------------
// ������GetSameNeighborBlkNo()
// ��������ȡ��ĳ���߽��ϵ�ͬ�����ڿ��ȫ����
//----------------------------------------------------------------------------------------
inline void GetSameNeighborBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, VBF_BLK_EDGE nBlkEdge, int nBlkNoX, int nBlkNoY, VBF_BLK_EDGE& nSameNeighBlkEdge, int& nSameNeighBlkNoX, int& nSameNeighBlkNoY)
{
	switch(nBlkEdge)
	{
		case VBF_BLK_EDGE_LEFT:   { nSameNeighBlkEdge = VBF_BLK_EDGE_RIGHT;  nSameNeighBlkNoX = nBlkNoX-1; nSameNeighBlkNoY = nBlkNoY;   break; }
		case VBF_BLK_EDGE_RIGHT:  { nSameNeighBlkEdge = VBF_BLK_EDGE_LEFT;   nSameNeighBlkNoX = nBlkNoX+1; nSameNeighBlkNoY = nBlkNoY;   break; }
		case VBF_BLK_EDGE_TOP:    { nSameNeighBlkEdge = VBF_BLK_EDGE_BOTTOM; nSameNeighBlkNoY = nBlkNoY-1; nSameNeighBlkNoX = nBlkNoX;   break; }
		case VBF_BLK_EDGE_BOTTOM: { nSameNeighBlkEdge = VBF_BLK_EDGE_TOP;    nSameNeighBlkNoY = nBlkNoY+1; nSameNeighBlkNoX = nBlkNoX;   break; }
	}

	// �������Ե����������
	int nSameBlkNoXMax, nSameBlkNoYMax;
	GetBlkNoMax( ConfigPar, noLod, nSameBlkNoXMax, nSameBlkNoYMax );
	
	// ����߿�������ڵͼ���Ϊ��X=nSameBlkNoXMax
	// ���ұ߿�������ڵͼ���Ϊ��X=0
	// ���ϱ߿�������ڵͼ���Ϊ��Y=0
	// ���±߿�������ڵͼ���Ϊ��Y=nSameBlkNoYMax

	if(nBlkEdge==VBF_BLK_EDGE_LEFT && nBlkNoX==0)             
		nSameNeighBlkNoX = nSameBlkNoXMax;

	else if(nBlkEdge==VBF_BLK_EDGE_RIGHT && nBlkNoX==nSameBlkNoXMax)    
		nSameNeighBlkNoX = 0;

	else if( nBlkEdge==VBF_BLK_EDGE_TOP && nBlkNoY==0 )	            
		nSameNeighBlkNoY = 0;

	else if( nBlkEdge==VBF_BLK_EDGE_BOTTOM && nBlkNoY==nSameBlkNoYMax )	
		nSameNeighBlkNoY = nSameBlkNoYMax;
}

//----------------------------------------------------------------------------------------
// ������GetBlkNoXY()
// ��������ȡָ������ָ��Lod����ʱ���ڵĿ�
//----------------------------------------------------------------------------------------
inline bool GetBlkNoXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double dX, double dY, int& nBlkNoX, int& nBlkNoY)
{
	// ���ܳ���ȫ��Χ
	if(dY<ConfigPar.dGlobalY0) return false;
	if(dY>ConfigPar.dGlobalY1) return false;
	if(dX<ConfigPar.dGlobalX0) return false;
	if(dX>ConfigPar.dGlobalX1) return false;

	double dBlkSizeX;
	double dBlkSizeY;
	GetBlkSize(ConfigPar, noLod, dBlkSizeX, dBlkSizeY);
			
//	nBlkNoX = ::VBF_DevideExactly<double,double>(dX-ConfigPar.dGlobalX0,dBlkSizeX);
//	nBlkNoY = ::VBF_DevideExactly<double,double>(dY-ConfigPar.dGlobalY0,dBlkSizeY);

	nBlkNoX = (int)((dX-ConfigPar.dGlobalX0)/dBlkSizeX);
	nBlkNoY = (int)((dY-ConfigPar.dGlobalY0)/dBlkSizeY);
	return true;
}

//----------------------------------------------------------------------------------------
// ������GetBlkNoXYBeginEnd()
// ���������㵱ǰ�ӳ���Χ�������ɵ�noLod�������ݿ�ķ�Χ
//----------------------------------------------------------------------------------------
inline void GetBlkNoXYBeginEnd(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double dX0, double dY0, double dX1, double dY1, int& nBlkNoXBegin, int& nBlkNoYBegin, int& nBlkNoXEnd, int& nBlkNoYEnd)
{
	// ���겻�ܳ���ȫ��Χ
	if( dX0 < ConfigPar.dGlobalX0 ) dX0 = ConfigPar.dGlobalX0;
	if( dY0 < ConfigPar.dGlobalY0 ) dY0 = ConfigPar.dGlobalY0;
	if( dX1 > ConfigPar.dGlobalX1 ) dX1 = ConfigPar.dGlobalX1;
	if( dY1 > ConfigPar.dGlobalY1 ) dY1 = ConfigPar.dGlobalY1;

	double dBlkSizeX;
	double dBlkSizeY;
	GetBlkSize(ConfigPar, noLod, dBlkSizeX, dBlkSizeY);

	// ���㵱ǰ�ӳ���Χ�������ɵ�noLod�������ݿ�ķ�Χ
	nBlkNoXBegin = int( (dX0-ConfigPar.dGlobalX0)/dBlkSizeX );
	nBlkNoYBegin = int( (dY0-ConfigPar.dGlobalY0)/dBlkSizeY );	

	nBlkNoXEnd   = ::VBF_DevideExactly(dX1-ConfigPar.dGlobalX0, dBlkSizeX)-1;
	nBlkNoYEnd   = ::VBF_DevideExactly(dY1-ConfigPar.dGlobalY0, dBlkSizeY)-1;
}

//-----------------------------------------------------------------------------
// ��������: GetFitLod()
// ��������: ���ݵ���Χ��ͼ���ȣ���ȡһ�����ʵ�Lod����
//-----------------------------------------------------------------------------
inline int GetFitLod(double dGeoL, int nImgWidth)
{
	float fWidth = (float)(180.0f * nImgWidth)/(float)(256 * dGeoL);
	int nLodNo = (int)( log10(fWidth)/log10(2.0f) );
	return nLodNo;
}

#endif 

