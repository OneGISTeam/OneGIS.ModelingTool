#ifndef OSGEARTHFEATURES_FILTER_CONTEXT_H
#define OSGEARTHFEATURES_FILTER_CONTEXT_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/OptimizerHints.h>
#include <VBF_3DMap/VBF_Features/Session.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceCache.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <Types/VBF_Matrix.h>
#include <list>



namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;
    class Session;
    class FeatureProfile;
    class FeatureSourceIndex;


    // 过滤器（链）执行的环境
    class OSGEARTHFEATURES_EXPORT FilterContext
    {
    public:
        FilterContext( Session* session =0L, const FeatureProfile* profile =0L,
            const CVBF_GeoExtent& workingExtent =CVBF_GeoExtent::INVALID, FeatureSourceIndex* index =0L);

        FilterContext( const FilterContext& rhs );      
        virtual ~FilterContext() { }

        // Assigns a resource cache to use. 如果没有指定则自动生成
        void setResourceCache( ResourceCache* value ) { _resourceCache = value; }

        /**
         * Sets the feature index that the filter chain should populate
         */
        void setFeatureIndex( FeatureSourceIndex* value ) { _index = value; }


    public: // properties

        // 是否包含完整的空间参考信息
        bool isGeoreferenced() const { return _session.valid() && _profile.valid(); }

        /**
         * Access to the Session under which this filter context operates
         */
        Session* getSession() { return _session.get(); }
        const Session* getSession() const { return _session.get(); }

        /**
         * The spatial profile of the feature data in this context.
         */
        const FeatureProfile* profile() const { return _profile.get(); }
        ref_ptr<const FeatureProfile>& profile() { return _profile; }

        /**
         * The spatial extent of the working cell
         */
        CVBF_Optional<CVBF_GeoExtent>& extent() { return _extent; }
        const CVBF_Optional<CVBF_GeoExtent>& extent() const { return _extent; }

        // feature的索引
        FeatureSourceIndex* featureIndex() { return _index; }
        const FeatureSourceIndex* featureIndex() const { return _index; }

         // 是否有一个未标识（non-identity）的参考坐标系
        bool hasReferenceFrame() const { return !_referenceFrame.isIdentity(); }

        // 从世界坐标转换到局部坐标
        osg::Vec3d toLocal( const osg::Vec3d& world ) const { return world * _referenceFrame; }

        // 把Geometry从世界坐标转换到局部坐标
        void toLocal( Geometry* geom ) const;

        // 从局部坐标转换到世界坐标
        osg::Vec3d toWorld( const osg::Vec3d& local ) const { return local * _inverseReferenceFrame; }

        // 把Geometry从局部坐标转换到世界坐标
        void toWorld( Geometry* geom ) const;

        /**
         * Converts a context-local point to a map coordinate.
         */
        osg::Vec3d toMap( const osg::Vec3d& local ) const;

        /**
         * Converts a map coordinate to a context-local point.
         */
        osg::Vec3d fromMap( const osg::Vec3d& map ) const;

        // 坐标参考系矩阵，乘以该矩阵可以把点从世界坐标变换到局部坐标
        const osg::Matrixd& referenceFrame() const { return _referenceFrame; }

        // 坐标参考系逆矩阵，乘以该矩阵可以把点从局部坐标变换到世界坐标
        const osg::Matrix& inverseReferenceFrame() const { return _inverseReferenceFrame; }

        // 设置坐标参考系矩阵及其逆矩阵
        void setReferenceFrame( const osg::Matrixd& in )
        {
            _referenceFrame = in;
            _inverseReferenceFrame.invert( _referenceFrame ); // = osg::Matrixd::inverse( _referenceFrame );
        }      

        /**
         * Accesses the shared resource cache where filters can store data.
         */
        ResourceCache* resourceCache() { return _resourceCache.get(); }

        /**
         * Hints to the OSG optimizer. Filters that use this context can explicity
         * ask to include or exclude optimizer options via this mechanism.
         */
        OptimizerHints& optimizerHints() { return _optimizerHints; }

        std::string toString() const; // 转换为一个字符串

        /** Gets the DB Options associated with the context's session */
        const osgDB::Options* getDBOptions() const;

    protected:
        ref_ptr<Session>              _session;
        ref_ptr<const FeatureProfile> _profile;
        bool                               _isGeocentric;
        CVBF_Optional<CVBF_GeoExtent>                _extent;
        osg::Matrixd                       _referenceFrame;
        osg::Matrixd                       _inverseReferenceFrame;
        OptimizerHints                     _optimizerHints;
        ref_ptr<ResourceCache>        _resourceCache;
        FeatureSourceIndex*                _index;
    };
} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FILTER_CONTEXT_H

