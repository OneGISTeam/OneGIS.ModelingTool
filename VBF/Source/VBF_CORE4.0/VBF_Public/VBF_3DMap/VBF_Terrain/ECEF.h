#ifndef OSGEARTH_ECEF_H
#define OSGEARTH_ECEF_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SpatialReference.h>
#include <Types/VBF_Matrix.h>

namespace osgEarth
{
    struct OSGEARTH_EXPORT ECEF
    {
        // 为一个地理位置创建一个局部变换矩阵（模型矩阵），局部坐标系变换到世界坐标系，已过时（改用CVBF_SpatialReference::createLocalToWorld）
        static osg::Matrixd createLocalToWorld( const osg::Vec3d& ecefRefPoint );

        // 把一个点转换到ECEF坐标系，并使用提供的world2local矩阵把它转换到局部坐标系，并把结果放到"output"中
        static void transformAndLocalize( const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
               osg::Vec3d& output, const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local =osg::Matrixd() );

         // 把一个点列转换到ECEF坐标系，并使用提供的world2local矩阵把它们转换到局部坐标系，把结果放到"output"中
        static void transformAndLocalize( const std::vector<osg::Vec3d>& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3Array* output, const CVBF_SpatialReference* outputSRS, const osg::Matrixd& world2local =osg::Matrixd() );

        // 把一个点列转换到ECEF坐标系，并使用提供的world2local矩阵把它们转换到局部坐标系，把结果放到"output"中
        // and the resulting localized normals in "out_normals" (if "out_normals" is non-NULL).
        static void transformAndLocalize( const std::vector<osg::Vec3d>& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3Array* out_verts, osg::Vec3Array* out_normals,const CVBF_SpatialReference* outputSRS,
            const osg::Matrixd& world2local =osg::Matrixd() );

        // 把一个点转换到ECEF坐标系，同时返回a quaternion that rotates the point into the local tangent place at that point.
        static void transformAndGetRotationMatrix( const osg::Vec3d& input, const CVBF_SpatialReference* inputSRS,
            osg::Vec3d& out_ecef_point, const CVBF_SpatialReference* outputSRS, osg::Matrixd& out_rotation );
    };
}

#endif // OSGEARTH_ECEF_H
