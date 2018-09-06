//**********************************************************************************
// �ļ�����  VBF_GeomMath.h
// ������    ����ͼ�εĸ�������
// ����:     ��Ө
// ����:     2014-05-15
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
    int				numPoint;		// ���������
    int				numRing;
    int*			pRingPtsNum;	// ÿ�������ߵĵ���

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

	//�ж������Ƿ��������ཻ
	bool IsLineIntersectPolygon(osg::Vec3d* LineGeom,int nLineGeomPts,osg::Vec3d* PolygonGeom,int PolygonGeomPts) ;

	//�ж�PolygonGeom1�Ƿ���PolygonGeom2�ཻ
	//0 ���� 1 �ཻ 2 ������ -1 �޹�
	int JudgePolygonIntersection(osg::Vec3d* PolygonGeom1,int nPolygonGeom1Pts,osg::Vec3d* PolygonGeom2,int PolygonGeom2Pts) ;

	//�ж�PolygonGeom2�Ƿ���ȫ����PolygonGeom1
	bool Is2ndContain1st(osg::Vec3d* PolygonGeom1,int nPolygonGeom1Pts,osg::Vec3d* PolygonGeom2,int PolygonGeom2Pts) ;

	//�ж������Ƿ�����ڶ������
	bool IsLineContainedInPolygon(osg::Vec3d* LineGeom,int nLineGeomPts,osg::Vec3d* PolygonGeom,int PolygonGeomPts) ;

	//�����������þ����㷨
    int calcBuffer(CVBF_GeosShape* pLines,int nLineNum,double dBufferDist,CVBF_GeosShape*& pContourPts,int &nContourPtsNum);

	// �����������ñ�����
    int calcBuffer1(CVBF_GeosShape* pLines,int nLineNum,double dBufferDist,CVBF_GeosShape*& pContourPts,int &nContourPtsNum,int nEndCapStyle = 2);
	int ClearBuffer();

	// ������ɢ
    int calcBuffer2(CVBF_GeosShape* pLines,double dBufferDist,bool bLeft,CVBF_GeosShape*& pContourPts);

	// �����
    bool contain(CVBF_GeosShape& outer ,CVBF_GeosShape& inter);
};

#endif
