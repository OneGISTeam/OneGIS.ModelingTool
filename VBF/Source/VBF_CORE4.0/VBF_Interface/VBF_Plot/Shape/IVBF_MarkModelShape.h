//*******************************************************************
// FileName��IVBF_MarkModelShape.h
// Function��������״����ʵ��ģ�͵Ļ��࣬�����塢Բ׶�塢Բ�����
// Author:   ��Ө
// Date:     2013-08-01
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_H__
#define __IVBF_MARK_MODEL_SHAPE_H__


#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>
#include <VBF_Plot/VBF_3DPlotDataTypes.h>



// ������ּ������ΨһID��
const unsigned int VBF_MARK_SHAPE_DOME				= VBF_PLOT_SHAPE + 1;	// Բ����
const unsigned int VBF_MARK_SHAPE_SPHERE			= VBF_PLOT_SHAPE + 2;	// ����
const unsigned int VBF_MARK_SHAPE_HEMISPHERE		= VBF_PLOT_SHAPE + 3;	// ������
const unsigned int VBF_MARK_SHAPE_CONE			    = VBF_PLOT_SHAPE + 4;	// Բ׶��
const unsigned int VBF_MARK_SHAPE_CYLINDER			= VBF_PLOT_SHAPE + 5;	// Բ����
const unsigned int VBF_MARK_SHAPE_OVAL			    = VBF_PLOT_SHAPE + 6;	// ��Բ����
const unsigned int VBF_MARK_SHAPE_PRISM				= VBF_PLOT_SHAPE + 7;	// ����
const unsigned int VBF_MARK_SHAPE_FRUSTUM_FLAT		= VBF_PLOT_SHAPE + 8;	// ƽ��ͷ�壨��ƽ״��
const unsigned int VBF_MARK_SHAPE_FRUSTUM_DOME		= VBF_PLOT_SHAPE + 9;	// ƽ��ͷ�壨��״��
const unsigned int VBF_MARK_SHAPE_PLANE             = VBF_PLOT_SHAPE + 10;	// ƽ��
const unsigned int VBF_MARK_SHAPE_CUBOID            = VBF_PLOT_SHAPE + 11;	// ������
const unsigned int VBF_MARK_SHAPE_CUBE              = VBF_PLOT_SHAPE + 12;	// ������
const unsigned int VBF_MARK_SHAPE_TORUS				= VBF_PLOT_SHAPE + 13;	// Բ��
const unsigned int VBF_MARK_SHAPE_TETRAHEDRON		= VBF_PLOT_SHAPE + 14;	// ������
const unsigned int VBF_MARK_SHAPE_REVOSURFACE		= VBF_PLOT_SHAPE + 15;	// �򵥻�ת��
const unsigned int VBF_MARK_SHAPE_SPHERE_ATTITUDE	= VBF_PLOT_SHAPE + 16;	// ��̬��
const unsigned int VBF_MARK_SHAPE_SECTOR			= VBF_PLOT_SHAPE + 17;	// ����
const unsigned int VBF_MARK_SHAPE_POINT2D			= VBF_PLOT_SHAPE + 18;	// ��ά��
const unsigned int VBF_MARK_SHAPE_POINT3D			= VBF_PLOT_SHAPE + 19;	// ��ά��
const unsigned int VBF_MARK_SHAPE_CYLINDERS			= VBF_PLOT_SHAPE + 20;	// �ֲ�Բ����
const unsigned int VBF_MARK_SHAPE_ELLIPSE2D			= VBF_PLOT_SHAPE + 21;	// ��ά�ռ��е���Բ
const unsigned int VBF_MARK_SHAPE_ELLIPSE3D			= VBF_PLOT_SHAPE + 22;	// ��ά�ռ��е���Բ
const unsigned int VBF_MARK_SHAPE_ARC2D				= VBF_PLOT_SHAPE + 23;	// ��ά�ռ��еĻ���
const unsigned int VBF_MARK_SHAPE_ARC3D				= VBF_PLOT_SHAPE + 24;	// ��ά�ռ��еĻ���
const unsigned int VBF_MARK_SHAPE_RECT2D			= VBF_PLOT_SHAPE + 25;  // ��ά�ռ��еľ���
const unsigned int VBF_MARK_SHAPE_RECT3D			= VBF_PLOT_SHAPE + 26;  // ��ά�ռ��еľ���


// ��������᷽����γ�ȷ��򣩷ָ�������С���ֵ
#define VBF_SPHERE_SPLIT_ROW_MIN	3
#define VBF_SPHERE_SPLIT_ROW_MAX	180


// ���������ݷ����ؾ��ȷ��򣩷ָ�������С���ֵ
#define VBF_SPHERE_SPLIT_COL_MIN	3
#define VBF_SPHERE_SPLIT_COL_MAX	3600
#define VBF_SPHERE_SPLIT_OUTER		3600


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelShape
// �ӿ�������������״����ʵ��ģ�͵Ļ��࣬�����塢Բ׶�塢Բ�����
//--------------------------------------------------------------------
class IVBF_MarkModelShape : public IVBF_MarkModelGraphics
{
public:
	virtual ~IVBF_MarkModelShape() {}

    // ����ģ�����������н��㣨�������꣩
    virtual void CalIntersectWithEarth(bool bOnlyOnGeoid, std::vector<osg::Vec3d>& vPointsGeo)=0;
};



#endif 
