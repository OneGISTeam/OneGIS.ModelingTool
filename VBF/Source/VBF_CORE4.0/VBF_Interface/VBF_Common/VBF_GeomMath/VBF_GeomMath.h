//**********************************************************************************
// 文件名：  VBF_GeomMath.h
// 描述：    几何图形的各种运算
// 作者:     杜莹
// 日期:     2014-05-15
//**********************************************************************************

#ifndef __VBF_GEOM_MATH_H__
#define __VBF_GEOM_MATH_H__

#include <VBF_Common/VBF_GeomMath/VBF_GeomMathExport.h>
#include <VBF_STL.h>
#include <VBF_Macros.h>
namespace osg
{
    class Vec3d;
}

class CVBF_GeosShape
{
public:
    osg::Vec3d*		pPoints;
    int				numPoint;		// 点的总数量
    int				numRing;
    int*			pRingPtsNum;	// 每个轮廓线的点数

    CVBF_GeosShape()
	{
        pPoints	= NULL;
        numPoint = 0;
        numRing	= 0;
        pRingPtsNum = NULL;
	}
    ~CVBF_GeosShape()
    {
        SAFE_DELETE(pPoints);
        SAFE_DELETE(pRingPtsNum);
        numPoint = 0;
        numRing	= 0;
    }
};


class VBF_GEOMMATH_EXPORT CVBF_GeomMath
{
public:
	CVBF_GeomMath();
	virtual ~CVBF_GeomMath();

public:
	bool GetGeomBuffer(osg::Vec3d* inGeom,int ninGeomPts,double dBufferDist, osg::Vec3d* &outGeom,int& noutGeomPts);

	//判断折线是否与多边形相交
	bool IsLineIntersectPolygon(osg::Vec3d* LineGeom,int nLineGeomPts,osg::Vec3d* PolygonGeom,int PolygonGeomPts) ;

	//判断PolygonGeom1是否与PolygonGeom2相交
	//0 包含 1 相交 2 被包含 -1 无关
	int JudgePolygonIntersection(osg::Vec3d* PolygonGeom1,int nPolygonGeom1Pts,osg::Vec3d* PolygonGeom2,int PolygonGeom2Pts) ;

	//判断PolygonGeom2是否完全包含PolygonGeom1
	bool Is2ndContain1st(osg::Vec3d* PolygonGeom1,int nPolygonGeom1Pts,osg::Vec3d* PolygonGeom2,int PolygonGeom2Pts) ;

	//判断折线是否包含于多边形内
	bool IsLineContainedInPolygon(osg::Vec3d* LineGeom,int nLineGeomPts,osg::Vec3d* PolygonGeom,int PolygonGeomPts) ;

	//求轮廓，利用聚类算法
    int calcBuffer(CVBF_GeosShape* pLines,int nLineNum,double dBufferDist,CVBF_GeosShape*& pContourPts,int &nContourPtsNum);

	// 求轮廓，利用本身函数
    int calcBuffer1(CVBF_GeosShape* pLines,int nLineNum,double dBufferDist,CVBF_GeosShape*& pContourPts,int &nContourPtsNum,int nEndCapStyle = 2);
	int ClearBuffer();

	// 求单向扩散
    int calcBuffer2(CVBF_GeosShape* pLines,double dBufferDist,bool bLeft,CVBF_GeosShape*& pContourPts);

	// 求包含
    bool contain(CVBF_GeosShape& outer ,CVBF_GeosShape& inter);
};

#endif
