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
#ifndef OSGEARTH_ANNO_IMAGE_OVERLAY_EDITOR_H
#define OSGEARTH_ANNO_IMAGE_OVERLAY_EDITOR_H

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_3DMap/VBF_Annotation/ImageOverlay.h>
#include <VBF_3DMap/VBF_Terrain/Draggers.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>

namespace osgEarth { namespace Annotation
{
    class OSGEARTHANNO_EXPORT ImageOverlayEditor : public osg::CVBF_SGNodeGroup
    {
    public:
        typedef std::map< ImageOverlay::ControlPoint, ref_ptr< Dragger > >  ControlPointDraggerMap;

        ImageOverlayEditor(ImageOverlay* overlay);

        ControlPointDraggerMap& getDraggers() { return _draggers; }

        ImageOverlay* getOverlay() { return _overlay.get();}

        void updateDraggers();

    protected:

        virtual ~ImageOverlayEditor();
        void addDragger( ImageOverlay::ControlPoint controlPoint );

        ref_ptr< ImageOverlay > _overlay;
        ref_ptr< ImageOverlay::ImageOverlayCallback > _overlayCallback;
        ControlPointDraggerMap _draggers;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_IMAGE_OVERLAY_EDITOR_H

