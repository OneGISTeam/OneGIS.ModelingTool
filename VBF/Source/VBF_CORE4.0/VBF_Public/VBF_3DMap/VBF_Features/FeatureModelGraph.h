#ifndef OSGEARTHFEATURES_FEATURE_MODEL_GRAPH_H
#define OSGEARTHFEATURES_FEATURE_MODEL_GRAPH_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBF_SourceModelFeature.h>
#include <VBF_3DMap/VBF_Features/Session.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlay.h>
#include <VBF_3DMap/VBF_Terrain/NodeUtils.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <set>


class CVBFO_SGNodeOverlayClampable;
class CVBFO_SGNodeOverlayDrapeable;


namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    // 该类处理选择的矢量数据，如果需要时对进行数据分块，根据style对数据排序
    // 对于每个分块（cell）及每个style，it will invoke the FeatureNodeFactory to create the actual data for each set.

    // 矢量方式渲染Feature数据的场景图（节点），简称矢量场景图
    class OSGEARTHFEATURES_EXPORT CVBF_SGNodeModelFeature : public osg::CVBF_SGNodeGroup
    {
    public:
		// options：数据源选项；factory：把矢量数据编译到节点；session：Session under which to create elements in this graph
        CVBF_SGNodeModelFeature(Session* session, const FeatureModelSourceOptions& options, FeatureNodeFactory* factory );
		
		// 加载一个子节点，内部用于分页
        osg::IVBF_SGNode* load( unsigned lod, unsigned tileX, unsigned tileY, const std::string& uri );

		// 获取/设置该矢量场景图关联的Style sheet
        StyleSheet* getStyles() { return _session->styles(); }
        void setStyles( StyleSheet* styles );

        // 该矢量要素的Session
        Session* getSession() { return _session; }

		// 注册的ID
        UID getUID() const { return m_uid; }

		// 设置该矢量场景图需要重建的标志
        void dirty();

		// 添加处理节点的操作，只有分页调度器真正加载了数据才对节点进行该操作
        void addPostMergeOperation( NodeOperation* op );

		// 访问（获取）矢量数据的Level（类似于LOD）
        const std::vector<const FeatureLevel*>& getLevels() const { return _lodmap; };

    public:
        virtual void traverse(osg::NodeVisitor& nv);

    protected:

        virtual ~CVBF_SGNodeModelFeature();

        osg::IVBF_SGNode* setupPaging(); // 建立四叉树分页

        osg::IVBF_SGNodeGroup* buildLevel( const FeatureLevel& level, const CVBF_GeoExtent& extent, const CVBF_TileKey* key);
        osg::IVBF_SGNodeGroup* build( const Style& baseStyle, const Query& baseQuery, const CVBF_GeoExtent& extent, FeatureSourceIndex* index);


    private:
        
        osg::IVBF_SGNodeGroup* createStyleGroup( const Style& style, const Query& query, FeatureSourceIndex* index);
        osg::IVBF_SGNodeGroup* createStyleGroup( const Style& style, FeatureList& workingSet, const FilterContext& contextPrototype);

        void buildStyleGroups( const StyleSelector* selector, const Query& baseQuery,
                                FeatureSourceIndex* index, osg::IVBF_SGNodeGroup* parent);

        void queryAndSortIntoStyleGroups( const Query& query, const StringExpression& styleExpr,
                                     FeatureSourceIndex* index, osg::IVBF_SGNodeGroup* parent);

        osg::IVBF_SGNodeGroup* getOrCreateStyleGroupFromFactory( const Style& style);
       
        osg::BoundingSphered getBoundInWorldCoords( const CVBF_GeoExtent& extent, const CVBF_MapFrame* mapf ) const;

        void buildSubTilePagedLODs( unsigned lod, unsigned tileX, unsigned tileY,
                                    const CVBF_MapFrame* mapFrame, osg::IVBF_SGNodeGroup* parent);

        void redraw();

    private:
        FeatureModelSourceOptions   _options;
        ref_ptr<FeatureNodeFactory> _factory;
        ref_ptr<Session>            _session;
        UID                              m_uid;
        std::set<std::string>            _blacklist;
        CVBF_ReadWriteMutex        m_MutexBlacklist;
        CVBF_GeoExtent                   _usableFeatureExtent;
        bool                             _featureExtentClamped;
        CVBF_GeoExtent                   _usableMapExtent;
        osg::BoundingSphered             _fullWorldBound;
        bool                             m_bUseTiledSource;
        osgEarth::Revision               _revision;
        bool                             m_bDirty;
        bool                             _pendingUpdate;
        std::vector<const FeatureLevel*> _lodmap;

        osg::IVBF_SGNodeGroup*          _overlayInstalled;
        osg::IVBF_SGNodeGroup*          _overlayPlaceholder;
        CVBFO_SGNodeOverlayClampable*   _clampable;
        CVBFO_SGNodeOverlayDrapeable*   _drapeable;

        enum OverlayChange 
		{
            OVERLAY_NO_CHANGE,
            OVERLAY_INSTALL_PLACEHOLDER,
            OVERLAY_INSTALL_CLAMPABLE,
            OVERLAY_INSTALL_DRAPEABLE
        };
        OverlayChange  _overlayChange;

        // 对节点进行的操作，如淡入淡出
        ref_ptr<CVBF_NodeOperations> m_postMergeOperations;

        void runPostMergeOperations(osg::IVBF_SGNode* node);
        void checkForGlobalAltitudeStyles(const Style& style);
        void changeOverlay();
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_MODEL_GRAPH_H
