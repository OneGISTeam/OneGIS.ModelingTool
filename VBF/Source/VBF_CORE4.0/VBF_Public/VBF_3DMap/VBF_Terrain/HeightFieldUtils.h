#ifndef OSGEARTH_HEIGHTFIELDUTILS_H
#define OSGEARTH_HEIGHTFIELDUTILS_H

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_Shape.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/ClusterCullingCallback.h>
#include <VBF_Engine/VBF_Terrain/ValidDataOperator>

namespace osgEarth
{
    // 与高程相关的工具
    class OSGEARTH_EXPORT HeightFieldUtils
    {
    public:
        // 获取给定行列（小数）位置的内插的高程值
        static float getHeightAtPixel( const osg::HeightField* hf,
                    double c, double r, ElevationInterpolation interpoltion = INTERP_BILINEAR);
        
        // 获取给定行列位置的内插的高程值，不是直接读，而是用邻近点差值
        static bool getInterpolatedHeight( const osg::HeightField* hf,
            unsigned c, unsigned r, float& out_height,
            ElevationInterpolation interpoltion = INTERP_BILINEAR);
        
        // 获取指定地理位置的高程值（内插）
        static float getHeightAtLocation( const osg::HeightField* hf,
            double x, double y, double llx, double lly, double dx, double dy,
            ElevationInterpolation interpolation = INTERP_BILINEAR);

        // 获取指定相对位置的内插高程值nx => [0.0, 1.0], ny => [0.0, 1.0]，[0.0, 1.0]为相对于角点的坐标
        static float getHeightAtNormalizedLocation( const osg::HeightField* hf,
            double nx, double ny,ElevationInterpolation interp = INTERP_BILINEAR);

        // 缩放高度场中的所有高程值（从长度单位转换到线性的度），唯一的目的是用于 projected Plate Carre map
        static void scaleHeightFieldToDegrees( osg::HeightField* hf );
        
        // Creates a heightfield containing MSL heights for the specified extent.
        // 如果SRS (in CVBF_GeoExtent)有垂直基准，高程值相对于其水准面；
        // 如果SRS没有垂直基准，认为MSL == 参考椭球面，所有的HF值为0。
        static osg::HeightField* createReferenceHeightField( const CVBF_GeoExtent& ex,
            unsigned numCols, unsigned numRows );

        // 根据指定范围重采样高度场
        static osg::HeightField* createSubSample( osg::HeightField* input,
            const CVBF_GeoExtent& inputEx, const CVBF_GeoExtent& outputEx,
            ElevationInterpolation interpolation = INTERP_BILINEAR);

        // 重采样高度场，保持角点值不变，重采样内部值
        static osg::HeightField* resampleHeightField( osg::HeightField* input,
            int newX, int newY, ElevationInterpolation interp = INTERP_BILINEAR );

        // 替换高度场中的无效值，用来自Geoid的有效值替换（如果没有Geoid，用0替换）
        static void resolveInvalidHeights( osg::HeightField* grid,
            const CVBF_GeoExtent& extent, float invalidValue, const Geoid* geoid );
        
        // 根据高度场创建一个集簇筛选器
        static osg::NodeCallback* createClusterCullingCallback(
            osg::HeightField* grid, osg::EllipsoidModel* em, float verticalScale =1.0f );
    };

    // 有效值操作的集合，传入的所有操作都必须是有效的
    struct OSGEARTH_EXPORT CompositeValidValueOperator : public osgTerrain::ValidDataOperator
    {
        typedef std::vector<ref_ptr<osgTerrain::ValidDataOperator> > ValidDataOperatorList;
        ValidDataOperatorList& getOperators() { return _operators;}

        virtual bool operator() (float value) const
        {
            for (ValidDataOperatorList::const_iterator itr = _operators.begin(); itr != _operators.end(); ++itr)
            {
                if (!(*itr->get())(value)) return false;
            }
            return true;
        }

        ValidDataOperatorList _operators;
    };

    // 用给定值替换无效值的遍历器
    struct OSGEARTH_EXPORT ReplaceInvalidDataOperator : public ::CVBF_Referenced
    {
        ReplaceInvalidDataOperator();

        virtual void operator()(osg::HeightField* heightField);

        osgTerrain::ValidDataOperator* getValidDataOperator() { return _validDataOperator.get(); }
        void setValidDataOperator(osgTerrain::ValidDataOperator* validDataOperator) { _validDataOperator = validDataOperator; }

        float getReplaceWith() { return _replaceWith; }
        void setReplaceWith( float replaceWith ) { _replaceWith = replaceWith; }

        ref_ptr<osgTerrain::ValidDataOperator> _validDataOperator;
        float _replaceWith;
    };


    // 用默认值替换无效值的遍历器
    struct OSGEARTH_EXPORT FillNoDataOperator : public ::CVBF_Referenced
    {
        FillNoDataOperator();
        virtual void operator()(osg::HeightField* heightField);

        osgTerrain::ValidDataOperator* getValidDataOperator() { return _validDataOperator.get(); }
        void setValidDataOperator(osgTerrain::ValidDataOperator* validDataOperator) { _validDataOperator = validDataOperator; }

        float getDefaultValue() { return _defaultValue; }
        void setDefaultValue(float defaultValue) { _defaultValue = defaultValue; }

        ref_ptr<osgTerrain::ValidDataOperator> _validDataOperator;

        float _defaultValue;
    };
}

#endif //OSGEARTH_HEIGHTFIELDUTILS_H
