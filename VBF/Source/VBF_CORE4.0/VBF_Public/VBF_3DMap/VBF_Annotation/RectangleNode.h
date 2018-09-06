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

#ifndef OSGEARTH_ANNOTATION_RECTANGLE_NODE_H
#define OSGEARTH_ANNOTATION_RECTANGLE_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    /**
     * Rectangle annotation.
     */
    class OSGEARTHANNO_EXPORT RectangleNode : public LocalizedNode
    {
    public:
        enum Corner
        {
            CORNER_LOWER_LEFT,
            CORNER_LOWER_RIGHT,
            CORNER_UPPER_LEFT,
            CORNER_UPPER_RIGHT
        };

        META_AnnotationNode( VBF_Annotation, RectangleNode );

        /**
         * Constructs a new rectangle annotation.
         *
         * @param mapNode     CVBF_Map on which the rectangle will appear
         * @param position    Location of the annotation, in map coordinates
         * @param width       Rectangle width
         * @param height      Rectangle height
         * @param style       Style defining how the annotation will look
         * @param draped      Whether to "drape" the annotation down on to the terrain         
         */
        RectangleNode(
            CVBFO_SGNodeMap*          mapNode,
            const GeoPoint&   position,
            const Linear&     width,
            const Linear&     height,
            const Style&      style );

        virtual ~RectangleNode() { }

        /**
         * Gets the width of this rectangle
         */
        const Linear& getWidth() const;

        /**
         * Gets the height of this rectangle
         */
        const Linear& getHeight() const;

        /**
         * Sets the width of this rectangle
         * @param width The width of the rectangle
         */
        void setWidth( const Linear& width );

        /**
         * Sets the height of this rectangle
         * @param height   The height of the rectangle
         */
        void setHeight( const Linear& height );

        /**
         * Sets the size of the rectangle
         * @param width         The width of the rectangle
         * @param height        The height of the rectangle
         */
        void setSize( const Linear& width, const Linear& height);

        /**
         * Gets the style
         */
        const Style& getStyle() const;

        /**
         * Sets the style
         */
        void setStyle( const Style& style );        

        GeoPoint getUpperLeft() const;
        void setUpperLeft( const GeoPoint& upperLeft );

        GeoPoint getUpperRight() const;
        void setUpperRight( const GeoPoint& upperRight );

        GeoPoint getLowerLeft() const;
        void setLowerLeft( const GeoPoint& lowerLeft );

        GeoPoint getLowerRight() const;
        void setLowerRight( const GeoPoint& lowerRight );

        GeoPoint getCorner( Corner corner ) const;
        void setCorner( Corner corner, const GeoPoint& location);

    public:

        RectangleNode(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* options);
        virtual CVBF_Config getConfig() const;
        
    protected: // LocalizedNode

        virtual osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _xform.get(); }

    private:
        RectangleNode() { }
        RectangleNode(const RectangleNode& rhs, const osg::CopyOp& op) { }

        void rebuild();

        Style  _style;
        Linear _width;
        Linear _height;

        ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNOTATION_RECTANGLE_NODE_H
