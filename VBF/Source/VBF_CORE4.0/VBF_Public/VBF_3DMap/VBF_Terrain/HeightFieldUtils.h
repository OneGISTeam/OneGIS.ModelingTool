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
    // ��߳���صĹ���
    class OSGEARTH_EXPORT HeightFieldUtils
    {
    public:
        // ��ȡ�������У�С����λ�õ��ڲ�ĸ߳�ֵ
        static float getHeightAtPixel( const osg::HeightField* hf,
                    double c, double r, ElevationInterpolation interpoltion = INTERP_BILINEAR);
        
        // ��ȡ��������λ�õ��ڲ�ĸ߳�ֵ������ֱ�Ӷ����������ڽ����ֵ
        static bool getInterpolatedHeight( const osg::HeightField* hf,
            unsigned c, unsigned r, float& out_height,
            ElevationInterpolation interpoltion = INTERP_BILINEAR);
        
        // ��ȡָ������λ�õĸ߳�ֵ���ڲ壩
        static float getHeightAtLocation( const osg::HeightField* hf,
            double x, double y, double llx, double lly, double dx, double dy,
            ElevationInterpolation interpolation = INTERP_BILINEAR);

        // ��ȡָ�����λ�õ��ڲ�߳�ֵnx => [0.0, 1.0], ny => [0.0, 1.0]��[0.0, 1.0]Ϊ����ڽǵ������
        static float getHeightAtNormalizedLocation( const osg::HeightField* hf,
            double nx, double ny,ElevationInterpolation interp = INTERP_BILINEAR);

        // ���Ÿ߶ȳ��е����и߳�ֵ���ӳ��ȵ�λת�������ԵĶȣ���Ψһ��Ŀ�������� projected Plate Carre map
        static void scaleHeightFieldToDegrees( osg::HeightField* hf );
        
        // Creates a heightfield containing MSL heights for the specified extent.
        // ���SRS (in CVBF_GeoExtent)�д�ֱ��׼���߳�ֵ�������ˮ׼�棻
        // ���SRSû�д�ֱ��׼����ΪMSL == �ο������棬���е�HFֵΪ0��
        static osg::HeightField* createReferenceHeightField( const CVBF_GeoExtent& ex,
            unsigned numCols, unsigned numRows );

        // ����ָ����Χ�ز����߶ȳ�
        static osg::HeightField* createSubSample( osg::HeightField* input,
            const CVBF_GeoExtent& inputEx, const CVBF_GeoExtent& outputEx,
            ElevationInterpolation interpolation = INTERP_BILINEAR);

        // �ز����߶ȳ������ֽǵ�ֵ���䣬�ز����ڲ�ֵ
        static osg::HeightField* resampleHeightField( osg::HeightField* input,
            int newX, int newY, ElevationInterpolation interp = INTERP_BILINEAR );

        // �滻�߶ȳ��е���Чֵ��������Geoid����Чֵ�滻�����û��Geoid����0�滻��
        static void resolveInvalidHeights( osg::HeightField* grid,
            const CVBF_GeoExtent& extent, float invalidValue, const Geoid* geoid );
        
        // ���ݸ߶ȳ�����һ������ɸѡ��
        static osg::NodeCallback* createClusterCullingCallback(
            osg::HeightField* grid, osg::EllipsoidModel* em, float verticalScale =1.0f );
    };

    // ��Чֵ�����ļ��ϣ���������в�������������Ч��
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

    // �ø���ֵ�滻��Чֵ�ı�����
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


    // ��Ĭ��ֵ�滻��Чֵ�ı�����
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
