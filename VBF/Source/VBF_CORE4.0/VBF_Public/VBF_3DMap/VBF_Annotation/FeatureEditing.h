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

#ifndef OSGEARTHANNO_FEATURE_EDITING_H
#define OSGEARTHANNO_FEATURE_EDITING_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Features/VBF_SourceFeatureList.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Viewer/VBF_View.h>

namespace osgEarth { namespace Annotation {

    /**
     * AddPointHandler is a GUIEventHandler that allows you to append points to a Feature's Geometry
     */
    struct OSGEARTHANNO_EXPORT AddPointHandler : public osgGA::GUIEventHandler 
    {
    public:
        /**
         * Constructs a new AddPointHandler
         * @param feature
         *      The Feature to edit
         * @param source
         *      The FeatureSource that the Feature belongs to
         * @param mapSRS
         *      The srs of the CVBF_Map
         */
        AddPointHandler(osgEarth::Features::Feature* feature, osgEarth::Features::FeatureSource* source, const CVBF_SpatialReference* mapSRS);

        bool handle( const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa );

        /**
         * Sets the mouse button used for adding new points
         */
        void setMouseButton( osgGA::GUIEventAdapter::MouseButtonMask mouseButton);

        /**
         * Gets the mouse button used for adding new points
         */
        osgGA::GUIEventAdapter::MouseButtonMask getMouseButton() const;

        void setIntersectionMask( osg::IVBF_SGNode::NodeMask intersectionMask ) { _intersectionMask = intersectionMask; }
        osg::IVBF_SGNode::NodeMask getIntersectionMask() const { return _intersectionMask;}


    private:
        bool addPoint( float x, float y, CVBF_View* view );

        osgGA::GUIEventAdapter::MouseButtonMask _mouseButton;
        bool _mouseDown;
        bool _firstMove;
        ref_ptr< osgEarth::Features::FeatureSource > _source;
        ref_ptr< osgEarth::Features::Feature > _feature;
        ref_ptr<const CVBF_SpatialReference> _mapSRS;
        osg::IVBF_SGNode::NodeMask _intersectionMask;
    };

    
    /**
     * Node you can add to your scene graph to edit the verts of a Feature's Geometry
     */
    class OSGEARTHANNO_EXPORT FeatureEditor : public osg::CVBF_SGNodeGroup
    {
    public:
         /**
         * Constructs a new FeatureEditor
         * @param feature
         *      The Feature to edit
         * @param source
         *      The FeatureSource that the Feature belongs to
         * @param mapNode
         *      The CVBFO_SGNodeMap that is being displayed
         */
        FeatureEditor( osgEarth::Features::Feature* feature, osgEarth::Features::FeatureSource* source, CVBFO_SGNodeMap* mapNode );

        /**
         *Gets the color of the draggers when they are selected
         */
        const osg::Vec4f& getPickColor() const;

        /**
         *Sets the color of the draggers when they are selected
         */
        void setPickColor( const osg::Vec4f& pickColor );

        /**
         *Gets the color of the draggers
         */
        const osg::Vec4f& getColor() const;

        /**
         *Sets the color of the draggers
         */
        void setColor( const osg::Vec4f& color );


        /**
         *Gets the dragger size
         */
        float getSize() const;

        /**
         *Sets the dragger size
         */
        void setSize( float size );


    protected:
        void init();

        osg::Vec4f _pickColor;
        osg::Vec4f _color;
        float _size;

        ref_ptr< osgEarth::Features::Feature > _feature;
        ref_ptr< osgEarth::Features::FeatureSource > _source;
        ref_ptr< CVBFO_SGNodeMap > _mapNode;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTHANNO_FEATURE_EDITING_H
