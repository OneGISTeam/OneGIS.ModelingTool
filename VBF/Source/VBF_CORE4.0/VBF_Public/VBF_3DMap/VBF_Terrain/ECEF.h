#ifndef OSGEARTH_ECEF_H
#define OSGEARTH_ECEF_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <Types/VBF_Matrix.h>

namespace osgEarth
{
    struct OSGEARTH_EXPORT ECEF
    {
        // Ϊһ������λ�ô���һ���ֲ��任����ģ�;��󣩣��ֲ�����ϵ�任����������ϵ���ѹ�ʱ������CVBF_SpatialReference::createLocalToWorld��
        static osg::Matrixd createLocalToWorld( const osg::Vec3d& ecefRefPoint );

        // ��һ����ת����ECEF����ϵ����ʹ���ṩ��world2local�������ת�����ֲ�����ϵ�����ѽ���ŵ�"output"��
        static void transformAndLocalize( const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
               osg::Vec3d& output, const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local =osg::Matrixd() );

         // ��һ������ת����ECEF����ϵ����ʹ���ṩ��world2local���������ת�����ֲ�����ϵ���ѽ���ŵ�"output"��
        static void transformAndLocalize( const std::vector<osg::Vec3d>& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3Array* output, const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local =osg::Matrixd() );

        // ��һ������ת����ECEF����ϵ����ʹ���ṩ��world2local���������ת�����ֲ�����ϵ���ѽ���ŵ�"output"��
        // and the resulting localized normals in "out_normals" (if "out_normals" is non-NULL).
        static void transformAndLocalize( const std::vector<osg::Vec3d>& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3Array* out_verts, osg::Vec3Array* out_normals,const CVBF_SpatialReference* outputSRS,
            const osg::Matrixd& world2local =osg::Matrixd() );

        // ��һ����ת����ECEF����ϵ��ͬʱ����a quaternion that rotates the point into the local tangent place at that point.
        static void transformAndGetRotationMatrix( const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3d& out_ecef_point, const CVBF_SpatialReference* outputSRS, osg::Matrixd& out_rotation );
    };
}

#endif // OSGEARTH_ECEF_H
