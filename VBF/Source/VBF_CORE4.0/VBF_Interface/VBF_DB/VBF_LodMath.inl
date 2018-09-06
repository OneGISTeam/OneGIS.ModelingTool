//**************************************************************************
// 文件：  VBF_LodMath.inl
// 描述：  与Lod有关的数学函数(实现部分)
// 作者：  杜莹 
// 时间：  2005-1-12
//**************************************************************************

#ifndef __VBF_LOD_MATH_INL__
#define __VBF_LOD_MATH_INL__

#include "VBF_OS.h"
#include "VBF_Common/VBF_Utils/VBF_3DMath.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------------------------
// 函数：EncodeBlkNo()
// 描述：对地形块进行编码，编码形式为UINT64型整数
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
// 函数：DecodeBlkNo()
// 描述：对地形块的编号进行解码
//----------------------------------------------------------------------------
inline void DecodeBlkNo(UINT64 key, int& nLodNo, int& nBlkNoX, int& nBlkNoY)
{
	nLodNo  = (int)(key>>59);	
	nBlkNoX = (int)(key<<5>>35);
	nBlkNoY = (int)(key<<35>>35);
}


//----------------------------------------------------------------------------------------
// 内联函数：GetLodFromMapNo()
// 函数描述：根据地图文件名，获取其Lod级别
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
// 内联函数：ConnectLod_X_Y16()
// 函数描述：用16进制数字记录文件名，形式为：noLod_nBlkNoX_nBlkNoY
//----------------------------------------------------------------------------------------
inline void ConnectLod_X_Y16(int noLod, int nBlkNoX, int nBlkNoY, char* bufKey)
{
	// 杜莹修改：2004-10-26
	// 为什么要使用16进制 ?
	// 因为目前缺少atoui64()函数，无法进行反向计算
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
// 内联函数：GetFileNoFromMapNo()
// 函数描述：根据地图文件名，获取其文件行列号
//----------------------------------------------------------------------------------------
inline void GetFileNoFromMapNo(const char* szMapNo, int& nFileNoX, int& nFileNoY)
{
	const char* pDst1 = strchr(szMapNo,  '_');	// 第一个连接号的位置
	const char* pDst2 = strrchr(szMapNo, '_');	// 第二个连接号的位置
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
// 内联函数：GetBlkNoInFileFromCode()
// 函数描述：根据块在文件中的位置，计算其在文件中的行列号
//----------------------------------------------------------------------------------------
inline void GetBlkNoInFileFromCode(int nCode, int nPerFileBlkNumX, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	nBlkNoInFileX = nCode % nPerFileBlkNumX;
	nBlkNoInFileY = nCode / nPerFileBlkNumX;
}

//----------------------------------------------------------------------------------------
// 函数：GetPerFileBlkNumXY()
// 描述：计算每个文件中实际保存的块数，理论上为ConfigPar.nPerFileBlkNumX，ConfigPar.nPerFileBlkNumY
//       但该LOD级别总数可能没有这么多块
//----------------------------------------------------------------------------------------
inline void GetPerFileBlkNumXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod,int& nPerFileBlkNumX,int& nPerFileBlkNumY)
{
	// 第noLod级的总块数
	int nTotalBlkNumX = (int)( ConfigPar.nRootBlkNumX * pow(2, (float)noLod) );
	int nTotalBlkNumY = (int)( ConfigPar.nRootBlkNumY * pow(2, (float)noLod) );

	// 每个文件保存的块数
	nPerFileBlkNumX = ConfigPar.nPerFileBlkNumX;
	nPerFileBlkNumY = ConfigPar.nPerFileBlkNumY;

	if( nPerFileBlkNumX > nTotalBlkNumX ) nPerFileBlkNumX = nTotalBlkNumX;
	if( nPerFileBlkNumY > nTotalBlkNumY ) nPerFileBlkNumY = nTotalBlkNumY;
}

//----------------------------------------------------------------------------------------
// 函数：GetBlkNoFromNoInFile()
// 描述：根据块在文件中的编号(i,j)，求它的全球编号(nBlkNoX,nBlkNoY)
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
// 函数：GetBlkNoInFile()
// 描述：根据全球块号，计算该块所在的文件，以及它在该文件中的块号
//---------------------------------------------------------------------
inline void GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	assert(nBlkNoX>=0 && nBlkNoY>=0);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );	

	// 根据块号计算该块在文件中的编号
	nBlkNoInFileX = nBlkNoX % nPerFileBlkNumX;
	nBlkNoInFileY = nBlkNoY % nPerFileBlkNumY;	
}

//---------------------------------------------------------------------
// 函数：GetBlkNoInFile()
// 描述：根据全球块号，计算该块所在的文件，以及它在该文件中的块号
//---------------------------------------------------------------------
inline void GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo, int& nBlkNoInFileX, int& nBlkNoInFileY)
{
	assert(nBlkNoX>=0 && nBlkNoY>=0);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );

	// 计算第noLod级，块(nBlkNoX, nBlkNoY) 所在的文件号
	// 每个文件保存 (nPerFileBlkNumX * nPerFileBlkNumY) 个块
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;	
	ConnectLod_X_Y16( noLod, nFileNoX, nFileNoY, szMapNo );

	// 根据块号计算该块在文件中的编号
	nBlkNoInFileX = nBlkNoX % nPerFileBlkNumX;
	nBlkNoInFileY = nBlkNoY % nPerFileBlkNumY;	
}

//----------------------------------------------------------------------------------------
// 函数：GetMapNoFromBlkNo()
// 描述：根据块的全球编号，获取其所在文件的编号
//----------------------------------------------------------------------------------------
inline void GetMapNoFromBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo)
{
	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, noLod, nPerFileBlkNumX, nPerFileBlkNumY );

	// 计算第noLod级，块(nBlkNoX, nBlkNoY) 所在的文件号
	// 每个文件保存 (nPerFileBlkNumX * nPerFileBlkNumY) 个块
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;
	
	ConnectLod_X_Y16( noLod, nFileNoX, nFileNoY, szMapNo );
}

//----------------------------------------------------------------------------------------
// 函数：GetMapNoFromBlkKey()
// 描述：根据块的缓存编号，获取其所在文件的编号
//----------------------------------------------------------------------------------------
inline void GetMapNoFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szMapNo)
{
	int nLodNo, nBlkNoX, nBlkNoY;
	DecodeBlkNo(unKey, nLodNo, nBlkNoX, nBlkNoY);

	int nPerFileBlkNumX = 0;
	int nPerFileBlkNumY = 0;
	GetPerFileBlkNumXY( ConfigPar, nLodNo, nPerFileBlkNumX, nPerFileBlkNumY );

	// 计算第noLod级，块(nBlkNoX, nBlkNoY) 所在的文件号
	// 每个文件保存 (nPerFileBlkNumX * nPerFileBlkNumY) 个块
	int nFileNoX = nBlkNoX / nPerFileBlkNumX;
	int nFileNoY = nBlkNoY / nPerFileBlkNumY;
	
	ConnectLod_X_Y16( nLodNo, nFileNoX, nFileNoY, szMapNo );
}

//----------------------------------------------------------------------------------------
// 函数：GetTableNameFromBlkKey()
// 描述：根据块的缓存编号，获取其所在数据库表的编号
// 说明：表名本来应该与文件名一致，但由于数据库中对以数字开头的表名有限制，
//       所以令：表名(T1_0_0) = T_ + 文件名(1_0_0)
//----------------------------------------------------------------------------------------
inline void GetTableNameFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szTableName)
{
	char szMapNo[30];
	GetMapNoFromBlkKey( ConfigPar, unKey, szMapNo );

	MapNoToTableName( szMapNo, szTableName );
}

//----------------------------------------------------------------------------
// 函数：MapNoToTableName()
// 描述：根据MapNo，获取其存储存储单元名(即：全路经文件名/数据库表名)
//----------------------------------------------------------------------------
inline void MapNoToTableName(char* szMapNo, char* szTableName)
{
	strcpy( szTableName , "T" );
	strcat( szTableName , szMapNo );
}

//----------------------------------------------------------------------------------------
// 函数：GetBlkKeyFromBlkCodeInFile()
// 描述：根据块所在的文件，以及在文件中的位置，获取其缓存编号
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
// 内联函数：GetSameLodBlkKey()
// 函数描述：获取四个同级块的缓存编号(UINT64型): LOD-X-Y
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
// 内联函数：GetBlkSize()
// 函数描述：第k级每一块的大小(单位: 度)
//----------------------------------------------------------------------------
inline void GetBlkSize(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, double& dBlkSizeX, double& dBlkSizeY)
{	
	dBlkSizeX = (ConfigPar.dGlobalX1 - ConfigPar.dGlobalX0)/(ConfigPar.nRootBlkNumX*pow(2,(float)nLodNo));
	dBlkSizeY = (ConfigPar.dGlobalY1 - ConfigPar.dGlobalY0)/(ConfigPar.nRootBlkNumY*pow(2,(float)nLodNo));
}

//----------------------------------------------------------------------------
// 内联函数：GetBlkNoFromLB()
// 函数描述：根据某点的LOD级别和经纬度，计算其所在的全球地形块
//----------------------------------------------------------------------------
inline void GetBlkNoFromLB(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, double L, double B, int& nBlkNoX, int& nBlkNoY)
{
	// 计算第k级每一块的大小(单位: 度)	
	double dBlkSizeX, dBlkSizeY;
	::GetBlkSize(ConfigPar, nLodNo, dBlkSizeX, dBlkSizeY);

	// 计算该点所在的全球地形块
	nBlkNoX = int( (L-ConfigPar.dGlobalX0)/dBlkSizeX );
	nBlkNoY = int( (B-ConfigPar.dGlobalY0)/dBlkSizeY );
}

//----------------------------------------------------------------------------
// 内联函数：GetBlkBound()
// 函数描述：根据LOD级别和块号，计算该块的经纬度范围
//----------------------------------------------------------------------------
inline void GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, int nBlkNoX, int nBlkNoY, 
						double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1)
{	
	// 计算第k级每一块的大小(单位: 度)	
	double dBlkSizeX, dBlkSizeY;
	::GetBlkSize(ConfigPar, nLodNo, dBlkSizeX, dBlkSizeY);

	dBlkX0 = dBlkSizeX * nBlkNoX + ConfigPar.dGlobalX0;
	dBlkY0 = dBlkSizeY * nBlkNoY + ConfigPar.dGlobalY0;
	dBlkX1 = dBlkX0 + dBlkSizeX;	
	dBlkY1 = dBlkY0 + dBlkSizeY;
}

//----------------------------------------------------------------------------
// 内联函数：GetBlkBound()
// 函数描述：根据块的全球编号，计算该块的经纬度范围
//----------------------------------------------------------------------------
inline void GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unBlkKey, 
						double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1)
{	
	int nLodNo, nBlkNoX, nBlkNoY;
	DecodeBlkNo( unBlkKey, nLodNo, nBlkNoX, nBlkNoY );

	GetBlkBound( ConfigPar, nLodNo, nBlkNoX, nBlkNoY, dBlkX0, dBlkY0, dBlkX1, dBlkY1 );
}



//----------------------------------------------------------------------------
// 内联函数：UINT64toString()
// 函数描述：把INT64型整数转变成16个字符的字符串，作为地形块(即一条记录)在数据库中的主键
//----------------------------------------------------------------------------
inline void UINT64toString(UINT64 key, char* buf)
{
	_ui64toa( key, buf, 16 );
	buf[16] = '\0';
}

//----------------------------------------------------------------------------
// 内联函数：BuildSQL()
// 函数描述：根据地形块的内存编号，构造SQL查询语句
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
// 函数：GetLowerBlkNo()
// 描述：获取指定块所在低级块的XY编号
//----------------------------------------------------------------------------------------
inline void GetLowerBlkNo(int nLodNo, int nBlkNoX, int nBlkNoY, int& nLowerLodNo, int& nLowerBlkNoX, int& nLowerBlkNoY)
{
	if(nLodNo==0)  // 特殊情况:第0级
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
// 函数：GetLowerBlkKey()
// 描述：获取指定块所在低级块的全球编号
//----------------------------------------------------------------------------------------
inline UINT64 GetLowerBlkKey(UINT64 unBlkKey)
{
	int nLodNo, nBlkNoX, nBlkNoY;
	::DecodeBlkNo(unBlkKey, nLodNo, nBlkNoX, nBlkNoY);	

	return ::GetLowerBlkKey(nLodNo, nBlkNoX, nBlkNoY);
}

//----------------------------------------------------------------------------------------
// 函数：GetLowerBlkKey()
// 描述：获取指定块所在低级块的全球编号
//----------------------------------------------------------------------------------------
inline UINT64 GetLowerBlkKey(int nLodNo, int nBlkNoX, int nBlkNoY)
{
	int nLodNoLower, nBlkNoXLower, nBlkNoYLower;
	::GetLowerBlkNo(nLodNo, nBlkNoX, nBlkNoY, nLodNoLower, nBlkNoXLower, nBlkNoYLower);

	return ::EncodeBlkNo(nLodNoLower, nBlkNoXLower, nBlkNoYLower);
}

//----------------------------------------------------------------------------------------
// 函数：GetBlkNoMax()
// 描述：获取指定Lod级别的XY块号的最大值
//----------------------------------------------------------------------------------------
inline void GetBlkNoMax(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int& nBlkNoXMax, int& nBlkNoYMax)
{
	nBlkNoXMax = (int)( ConfigPar.nRootBlkNumX * pow(2, (float)noLod) ) - 1;
	nBlkNoYMax = (int)( ConfigPar.nRootBlkNumY * pow(2, (float)noLod) ) - 1;
}

//----------------------------------------------------------------------------------------
// 函数：GetLowerNeighborBlkNo()
// 描述：获取块某条边界上的低级相邻块的全球编号
//----------------------------------------------------------------------------------------
inline void GetLowerNeighborBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, VBF_BLK_EDGE nBlkEdge, int nBlkNoX, int nBlkNoY, VBF_BLK_EDGE& nLowerNeighBlkEdge, int& nLowerNeighBlkNoX, int& nLowerNeighBlkNoY)
{	
	int nModX = nBlkNoX % 2;  // X方向块号被2除之后的余数(为0或1)
	int nModY = nBlkNoY % 2;  // Y方向块号被2除之后的余数(为0或1)

	switch(nBlkEdge)
	{
		case VBF_BLK_EDGE_LEFT:   { nLowerNeighBlkEdge = VBF_BLK_EDGE_RIGHT;   nLowerNeighBlkNoX = nBlkNoX/2-1;      nLowerNeighBlkNoY = (nBlkNoY-nModY)/2;  break; }
		case VBF_BLK_EDGE_RIGHT:  { nLowerNeighBlkEdge = VBF_BLK_EDGE_LEFT;    nLowerNeighBlkNoX = (nBlkNoX-1)/2+1;  nLowerNeighBlkNoY = (nBlkNoY-nModY)/2;  break; }
		case VBF_BLK_EDGE_TOP:    { nLowerNeighBlkEdge = VBF_BLK_EDGE_BOTTOM;  nLowerNeighBlkNoY = nBlkNoY/2-1;      nLowerNeighBlkNoX = (nBlkNoX-nModX)/2;  break; }
		case VBF_BLK_EDGE_BOTTOM: { nLowerNeighBlkEdge = VBF_BLK_EDGE_TOP;     nLowerNeighBlkNoY = (nBlkNoY-1)/2+1;  nLowerNeighBlkNoX = (nBlkNoX-nModX)/2;  break; }
	}	
	
	// 处理最边缘块的特殊情况
	int nLowerBlkNoXMax, nLowerBlkNoYMax;
	GetBlkNoMax( ConfigPar, noLod-1, nLowerBlkNoXMax, nLowerBlkNoYMax );
	
	// 最左边块的左相邻低级块为：X=nLowerBlkNoXMax
	// 最右边块的右相邻低级块为：X=0
	// 最上边块的上相邻低级块为：Y=0
	// 最下边块的下相邻低级块为：Y=nLowerBlkNoYMax

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
// 函数：GetSameNeighborBlkNo()
// 描述：获取块某条边界上的同级相邻块的全球编号
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

	// 处理最边缘块的特殊情况
	int nSameBlkNoXMax, nSameBlkNoYMax;
	GetBlkNoMax( ConfigPar, noLod, nSameBlkNoXMax, nSameBlkNoYMax );
	
	// 最左边块的左相邻低级块为：X=nSameBlkNoXMax
	// 最右边块的右相邻低级块为：X=0
	// 最上边块的上相邻低级块为：Y=0
	// 最下边块的下相邻低级块为：Y=nSameBlkNoYMax

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
// 函数：GetBlkNoXY()
// 描述：获取指定点在指定Lod级别时所在的块
//----------------------------------------------------------------------------------------
inline bool GetBlkNoXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double dX, double dY, int& nBlkNoX, int& nBlkNoY)
{
	// 不能超过全球范围
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
// 函数：GetBlkNoXYBeginEnd()
// 描述：计算当前视场范围可以生成的noLod级别数据块的范围
//----------------------------------------------------------------------------------------
inline void GetBlkNoXYBeginEnd(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double dX0, double dY0, double dX1, double dY1, int& nBlkNoXBegin, int& nBlkNoYBegin, int& nBlkNoXEnd, int& nBlkNoYEnd)
{
	// 坐标不能超过全球范围
	if( dX0 < ConfigPar.dGlobalX0 ) dX0 = ConfigPar.dGlobalX0;
	if( dY0 < ConfigPar.dGlobalY0 ) dY0 = ConfigPar.dGlobalY0;
	if( dX1 > ConfigPar.dGlobalX1 ) dX1 = ConfigPar.dGlobalX1;
	if( dY1 > ConfigPar.dGlobalY1 ) dY1 = ConfigPar.dGlobalY1;

	double dBlkSizeX;
	double dBlkSizeY;
	GetBlkSize(ConfigPar, noLod, dBlkSizeX, dBlkSizeY);

	// 计算当前视场范围可以生成的noLod级别数据块的范围
	nBlkNoXBegin = int( (dX0-ConfigPar.dGlobalX0)/dBlkSizeX );
	nBlkNoYBegin = int( (dY0-ConfigPar.dGlobalY0)/dBlkSizeY );	

	nBlkNoXEnd   = ::VBF_DevideExactly(dX1-ConfigPar.dGlobalX0, dBlkSizeX)-1;
	nBlkNoYEnd   = ::VBF_DevideExactly(dY1-ConfigPar.dGlobalY0, dBlkSizeY)-1;
}

//-----------------------------------------------------------------------------
// 内联函数: GetFitLod()
// 函数描述: 根据地理范围和图像宽度，获取一个合适的Lod级别
//-----------------------------------------------------------------------------
inline int GetFitLod(double dGeoL, int nImgWidth)
{
	float fWidth = (float)(180.0f * nImgWidth)/(float)(256 * dGeoL);
	int nLodNo = (int)( log10(fWidth)/log10(2.0f) );
	return nLodNo;
}

#endif 

