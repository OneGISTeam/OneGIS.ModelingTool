/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2013 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#ifndef OSGEARTH_ANNO_IMAGE_OVERLAY_H
#define OSGEARTH_ANNO_IMAGE_OVERLAY_H

#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>

namespace osgEarth { namespace Annotation
{
    using namespace osgEarth;

    class OSGEARTHANNO_EXPORT ImageOverlay : public AnnotationNode
    {
    public:
        META_AnnotationNode(VBF_Annotation, ImageOverlay);
        
        enum ControlPoint
        {
            CONTROLPOINT_CENTER,
            CONTROLPOINT_LOWER_LEFT,
            CONTROLPOINT_LOWER_RIGHT,
            CONTROLPOINT_UPPER_LEFT,
            CONTROLPOINT_UPPER_RIGHT
        };
        

        ImageOverlay(CVBFO_SGNodeMap* mapNode, osg::Image* image = NULL);
        ImageOverlay(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* dbOptions);
        virtual ~ImageOverlay() { }

        void setCorners(const osg::Vec2d& lowerLeft, const osg::Vec2d& lowerRight, 
                        const osg::Vec2d& upperLeft, const osg::Vec2d& upperRight);

        void setLowerLeft(double lon_deg, double lat_deg);
        const osg::Vec2d& getLowerLeft() const { return _lowerLeft; }

        void setLowerRight(double lon_deg, double lat_deg);
        const osg::Vec2d& getLowerRight() const { return _lowerRight;}

        void setUpperLeft(double lon_deg, double lat_deg);
        const osg::Vec2d& getUpperLeft() const { return _upperLeft; }

        void setUpperRight(double lon_deg, double lat_deg);
        const osg::Vec2d& getUpperRight() const { return _upperRight;}

        osg::Vec2d getCenter() const;
        void setCenter(double lon_deg, double lat_deg);

        osg::Vec2d getControlPoint(ControlPoint controlPoint);
        void setControlPoint(ControlPoint controlPoint, double lon_deg, double lat_deg, bool singleVert=false);

        struct ImageOverlayCallback : public ::CVBF_Referenced
        {
            virtual void onOverlayChanged() {};
            virtual ~ImageOverlayCallback() { }
        };

        typedef std::list< ref_ptr<ImageOverlayCallback> > CallbackList;

        void addCallback( ImageOverlayCallback* callback );
        void removeCallback( ImageOverlayCallback* callback );


        osgEarth::Bounds getBounds() const;
        void setBounds(const osgEarth::Bounds& bounds);

        void setBoundsAndRotation(const osgEarth::Bounds& bounds, const Angular& rotation);

        osg::Image* getImage() const;
        void setImage( osg::Image* image );

        // 设置图像所对应的纹理，避免重复创建完全相同的纹理（杜莹添加：2014-10-16）
        void SetTexture(osg::Texture2D* pTexture);

        osg::Texture::FilterMode getMinFilter() const;
        void setMinFilter( osg::Texture::FilterMode filter );

        osg::Texture::FilterMode getMagFilter() const;
        void setMagFilter( osg::Texture::FilterMode filter );

        void setNorth(double value_deg);
        void setSouth(double value_deg);
        void setEast(double value_deg);
        void setWest(double value_deg);

        float getAlpha() const;
        void setAlpha(float alpha);

        void dirty();

        bool getDraped() const;
        void setDraped( bool draped );
        
        /** Serialize the contents of this node */
        CVBF_Config getConfig() const;

    public: // AnnotationNode
        
        virtual void reclamp( const CVBF_TileKey& key, osg::IVBF_SGNode* tile, const CVBF_Terrain* );

    public: // MapNodeObserver

        virtual void setMapNode( CVBFO_SGNodeMap* mapNode );

    public: // osg::Node

        virtual void traverse(osg::NodeVisitor& nv);
        
    private:
        void fireCallback(ImageOverlay::ControlPoint point, const osg::Vec2d& location);

        void postCTOR();
        void init();
        void clampLatitudes();

        void clampMesh( osg::IVBF_SGNode* terrainModel );

        void updateFilters();

		// 魏勇增加，DirtyAlpha（更新m_bDirtyAlpha）2012-4-30 15:29:56
		void DirtyAlpha();

		// 魏勇增加，UpdateAlpha（只增加更新纹理的alpha值，其他不变）2012-4-30 15:29:52
		void UpdateAlpha();


        osg::Vec2d _lowerLeft;
        osg::Vec2d _lowerRight;
        osg::Vec2d _upperRight;
        osg::Vec2d _upperLeft;
        osg::Polytope _boundingPolytope;        
        ref_ptr< osg::Image > _image;
        bool m_bDirty;
        OpenThreads::Mutex _mutex;

		osg::IVBF_SGNodeGroupTransformMatrix* _transform;
        //osg::Texture* _texture;
        ref_ptr<osg::Texture> _texture;

	//	osg::IVBF_SGNodeGeometry* _geode;
	//	osg::Geometry* _geometry;

		// 魏勇修改，改为智能指针 2012-4-30 15:30:02
		// 试图解决ImageOverlay的内存泄露问题
        ref_ptr<osg::Geometry>				_geometry;
		ref_ptr<osg::IVBF_SGNodeGeometry>	_geode;
        bool								m_bDirtyAlpha;

		// GGR:魏勇增加，记录color数组
		ref_ptr<osg::Vec4Array> m_piColorArray;
        
        CallbackList _callbacks;

        CVBF_Optional<URI>		_imageURI;
        CVBF_Optional<float>	_alpha;
        CVBF_Optional<osg::Texture::FilterMode> _minFilter;
        CVBF_Optional<osg::Texture::FilterMode> _magFilter;

        ImageOverlay() { }
        ImageOverlay(const ImageOverlay&, const osg::CopyOp&) { }
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_IMAGE_OVERLAY_H

