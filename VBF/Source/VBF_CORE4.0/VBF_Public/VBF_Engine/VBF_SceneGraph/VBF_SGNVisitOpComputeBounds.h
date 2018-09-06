/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef OSG_COMPUTEBOUNDSVISITOR
#define OSG_COMPUTEBOUNDSVISITOR 1

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <Types/VBF_BoundingBox.h>
#include <Types/VBF_Polytope.h>

namespace osg {

class OSG_EXPORT ComputeBoundsVisitor : public osg::NodeVisitor
{
public:

    ComputeBoundsVisitor(TraversalMode traversalMode = TRAVERSE_ALL_CHILDREN);
    
    META_NodeVisitor("osg","ComputeBoundsVisitor")

    virtual void reset();
    
    osg::BoundingBox& getBoundingBox() { return _bb; }

    void getPolytope(osg::Polytope& polytope, float margin=0.1) const;
        
    void getBase(osg::Polytope& polytope, float margin=0.1) const;
    
    void apply(osg::IVBF_SGNode& node);
    
    void apply(osg::IVBF_SGNodeGroupTransform& transform);
    
    void apply(osg::IVBF_SGNodeGeometry& geode);
    
    inline void pushMatrix(osg::Matrix& matrix) { _matrixStack.push_back(matrix); }
    
    inline void popMatrix() { _matrixStack.pop_back(); }

    void applyDrawable(osg::Drawable* drawable);
    
protected:
    
    typedef std::vector<osg::Matrix> MatrixStack;

    MatrixStack         _matrixStack;
    osg::BoundingBox    _bb;
};

}

#endif
