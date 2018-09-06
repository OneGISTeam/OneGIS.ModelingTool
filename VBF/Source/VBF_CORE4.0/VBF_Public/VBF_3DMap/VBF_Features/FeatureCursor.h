#ifndef OSGEARTHFEATURES_FEATURE_CURSOR_H
#define OSGEARTHFEATURES_FEATURE_CURSOR_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Features/VBF_FeatureFilter.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>

namespace osgEarth { namespace Features
{   
    using namespace osgEarth;

	// Feature�α꣺����Feature���ϵĵ������ü���������FeatureStore�ϲ�ѯ�Ľ��
    class OSGEARTHFEATURES_EXPORT FeatureCursor : public ::CVBF_Referenced
    {
    public:
        virtual bool hasMore() const =0;
        virtual Feature* nextFeature() =0;
    public:
        void fill( FeatureList& output );

        virtual ~FeatureCursor() { }
    };


	// һ���򵥵�Feature�α��ʵ�֣����ڴ��б�������
    class OSGEARTHFEATURES_EXPORT FeatureListCursor : public FeatureCursor
    {
    public:
        FeatureListCursor( const FeatureList& input, bool cloneFeatures =false );      
        virtual ~FeatureListCursor() { }

        virtual bool hasMore() const;
        virtual Feature* nextFeature();

    protected:
        FeatureList           _features;
        FeatureList::iterator _iter;
        bool                  _clone;
    };


    class OSGEARTHFEATURES_EXPORT GeometryFeatureCursor : public FeatureCursor
    {
    public:
        GeometryFeatureCursor( Symbology::Geometry* geom );
        GeometryFeatureCursor( Symbology::Geometry* geom, const FeatureProfile* fp, const FeatureFilterList& filters );
        virtual ~GeometryFeatureCursor() { }
        virtual bool hasMore() const;
        virtual Feature* nextFeature();
    protected:
        ref_ptr<Symbology::Geometry> _geom;
        ref_ptr<const FeatureProfile> _featureProfile;
        const FeatureFilterList _filters;
        ref_ptr<Feature> _lastFeature;
    };

} } // namespace osgEarth::Features

#endif // OSGEARTHFEATURES_FEATURE_CURSOR_H

