//**************************************************************************
// 文件：  VBF_LodMath.h
// 描述：  与Lod有关的数学函数(声明部分)
// 作者：  杜莹 
// 时间：  2005-1-12
//**************************************************************************

#ifndef __VBF_LOD_MATH_H__
#define __VBF_LOD_MATH_H__

#include "VBF_DemTexDataType.h"
#include "VBF_Macros.h"


// 对地形块的编号进行编码和解码
UINT64   EncodeBlkNo(int nLodNo, int nBlkNoX, int nBlkNoY);
void     DecodeBlkNo(UINT64 key, int& nLodNo, int& nBlkNoX, int& nBlkNoY);
int      GetLodFromMapNo(const char* szMapNo);
void     ConnectLod_X_Y16(int noLod, int nBlkNoX, int nBlkNoY, char* bufKey);
void     GetFileNoFromMapNo(const char* szMapNo, int& nFileNoX, int& nFileNoY);
void     GetBlkNoInFileFromCode(int nCode, int nPerFileBlkNumX, int& nBlkNoInFileX, int& nBlkNoInFileY);
void     GetPerFileBlkNumXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod,int& nPerFileBlkNumX,int& nPerFileBlkNumY);
void     GetBlkNoFromNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, const char* szMapNo, int nBlkNoInFileX, int nBlkNoInFileY, int& nBlkNoX, int& nBlkNoY);
void     GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo, int& nBlkNoInFileX, int& nBlkNoInFileY);
void     GetBlkNoInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, int& nBlkNoInFileX, int& nBlkNoInFileY);
void     GetBlkSize(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, double& dBlkSizeX, double& dBlkSizeY);
void     GetBlkNoFromLB(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, double L, double B, int nLodNo, int& nBlkNoX, int& nBlkNoY);
bool	 GetBlkNoXY(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double dX, double dY, int& nBlkNoX, int& nBlkNoY);
void	 GetBlkNoXYBeginEnd(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, double X0, double dY0, double dX1, double dY1, int& nBlkNoXBegin, int& nBlkNoYBegin, int& nBlkNoXEnd, int& nBlkNoYEnd);
void     GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int nLodNo, int nBlkNoX, int nBlkNoY, double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1);
void     GetBlkBound(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unBlkKey, double& dBlkX0, double& dBlkY0, double& dBlkX1, double& dBlkY1);
void	 GetMapNoFromBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int nBlkNoX, int nBlkNoY, char* szMapNo);
void     GetMapNoFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szMapNo);
void     GetTableNameFromBlkKey(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, UINT64 unKey, char* szTableName);
void     GetBlkKeyFromBlkCodeInFile(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, const char* szMapNo, int nBlkCode, UINT64& unKey);
void     GetSameLodBlkKey(int nLodNo, int nBlkNoX, int nBlkNoY, UINT64 unKeySameLod[4]);
void     MapNoToTableName(char* szMapNo, char* szTableName);
UINT64   GetLowerBlkKey(UINT64 unBlkKey);
UINT64   GetLowerBlkKey(int nLodNo, int nBlkNoX, int nBlkNoY);
void     GetLowerBlkNo(int nLodNo, int nBlkNoX, int nBlkNoY, int& nLowerLodNo, int& nLowerBlkNoX, int& nLowerBlkNoY);
void	 GetBlkNoMax(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, int& nBlkNoXMax, int& nBlkNoYMax);
void	 GetLowerNeighborBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, VBF_BLK_EDGE nBlkEdge, int nBlkNoX, int nBlkNoY, VBF_BLK_EDGE& nLowerNeighBlkEdge, int& nLowerNeighBlkNoX, int& nLowerNeighBlkNoY);
void	 GetSameNeighborBlkNo(const VBF_DEMTEXENGINECONFIGPAR& ConfigPar, int noLod, VBF_BLK_EDGE nBlkEdge, int nBlkNoX, int nBlkNoY, VBF_BLK_EDGE& nSameNeighBlkEdge, int& nSameNeighBlkNoX, int& nSameNeighBlkNoY);
int      GetFitLod(double dGeoL, int nImgWidth);

// 构建SQL语句
void     BuildSQL(UINT64 key, const char* szTableName, char* szSQL);
void     UINT64toString(UINT64 key, char* buf);


//-------------------------------------------------------------------------------------------
// 需要包含实现文件
#include "VBF_LodMath.inl"
//-------------------------------------------------------------------------------------------


#endif 

