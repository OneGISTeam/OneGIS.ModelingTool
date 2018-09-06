#ifndef OSGEARTHFEATURES_FEATURE_DRAW_SET_H
#define OSGEARTHFEATURES_FEATURE_DRAW_SET_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <set>

namespace osgEarth { namespace Features
{
    // �����ͼ������Drawable��ԭʼͼԪ����ɣ������ڱ༭ʱ��ԭʼͼԪ���б༭
    class OSGEARTHFEATURES_EXPORT FeatureDrawSet
    {     
    public: // types
        typedef osg::Geometry::PrimitiveSetList  PrimitiveSets;
        struct DrawableSlice
        {
            ref_ptr<osg::Drawable> drawable;
            PrimitiveSets               primSets;
            osg::Matrixd                local2world;
        };

        typedef std::vector<DrawableSlice>                 DrawableSlices;
        typedef std::vector< ref_ptr<osg::IVBF_SGNode> >   Nodes;

    public:
        FeatureDrawSet();
        virtual ~FeatureDrawSet() { }

        // ��ɱ���ͼ���Ľڵ�
        Nodes& nodes() { return _nodes; }
        const Nodes& nodes() const { return _nodes; }

        // ��ɸû�ͼ����Drawable/primitive-set-list��
        DrawableSlices& slices() { return _slices; }
        const DrawableSlices& slices() const { return _slices; }

        // ��ȡ����Drawable��Ӧ��ԭʼͼԪ�б�
        PrimitiveSets& getOrCreateSlice(osg::Drawable* d);

        // ��ȡһ�����֣���Drawable��ԭʼͼԪ����ɣ����Ҳ����򷵻�slices().end()
        DrawableSlices::iterator slice(osg::Drawable* d);
        DrawableSlices::const_iterator slice(osg::Drawable* d) const;


        bool IsEmpty() const { return _nodes.empty() && _slices.empty(); } // �Ƿ�Ϊ��
        void setVisible( bool value ); // ���ÿɼ���
        void clear();  // ���

        /** Collects a set containing primitive indicies used in a slice. */
        void collectPrimitiveIndexSet( const DrawableSlice& slice, std::set<unsigned>& output ) const;
        
        osg::IVBF_SGNode* createCopy(); // ǳ����

    private:
        Nodes          _nodes;
        DrawableSlices _slices;

        typedef std::vector<unsigned> Masks;

        bool            _visible;
        Masks           _invisibleMasks;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_DRAW_SET_H
