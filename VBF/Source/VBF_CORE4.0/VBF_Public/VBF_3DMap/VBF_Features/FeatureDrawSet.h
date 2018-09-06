#ifndef OSGEARTHFEATURES_FEATURE_DRAW_SET_H
#define OSGEARTHFEATURES_FEATURE_DRAW_SET_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <set>

namespace osgEarth { namespace Features
{
    // 地物绘图集，由Drawable和原始图元对组成，多用于编辑时对原始图元进行编辑
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

        // 组成本绘图集的节点
        Nodes& nodes() { return _nodes; }
        const Nodes& nodes() const { return _nodes; }

        // 组成该绘图集的Drawable/primitive-set-list对
        DrawableSlices& slices() { return _slices; }
        const DrawableSlices& slices() const { return _slices; }

        // 获取与由Drawable对应的原始图元列表
        PrimitiveSets& getOrCreateSlice(osg::Drawable* d);

        // 获取一个部分（由Drawable和原始图元对组成），找不到则返回slices().end()
        DrawableSlices::iterator slice(osg::Drawable* d);
        DrawableSlices::const_iterator slice(osg::Drawable* d) const;


        bool IsEmpty() const { return _nodes.empty() && _slices.empty(); } // 是否为空
        void setVisible( bool value ); // 设置可见性
        void clear();  // 清空

        /** Collects a set containing primitive indicies used in a slice. */
        void collectPrimitiveIndexSet( const DrawableSlice& slice, std::set<unsigned>& output ) const;
        
        osg::IVBF_SGNode* createCopy(); // 浅拷贝

    private:
        Nodes          _nodes;
        DrawableSlices _slices;

        typedef std::vector<unsigned> Masks;

        bool            _visible;
        Masks           _invisibleMasks;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_DRAW_SET_H
