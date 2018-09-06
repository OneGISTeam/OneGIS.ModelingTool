/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2004 Robert Osfield 
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

#ifndef OSG_OBJECT_MATRIXD
#define OSG_OBJECT_MATRIXD 1

#include <VBF_Common/VBF_Math/VBF_Export.h>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3d>
#include <Types/Vec4d>
#include <Types/VBF_Quat.h>
#include <Types/VBF_Matrixd.h>

namespace osg {


class RefMatrixd : public CVBF_Object, public Matrixd
{
    public:
    
        RefMatrixd():CVBF_Object(false), Matrixd() {}
        RefMatrixd( const Matrixd& other) : CVBF_Object(false), Matrixd(other) {}
        RefMatrixd( const Matrixf& other) : CVBF_Object(false), Matrixd(other) {}
        RefMatrixd( const RefMatrixd& other) : CVBF_Object(other), Matrixd(other) {}
        explicit RefMatrixd( Matrixd::value_type const * const def ):CVBF_Object(false), Matrixd(def) {}
        RefMatrixd( Matrixd::value_type a00, Matrixd::value_type a01, Matrixd::value_type a02, Matrixd::value_type a03,
            Matrixd::value_type a10, Matrixd::value_type a11, Matrixd::value_type a12, Matrixd::value_type a13,
            Matrixd::value_type a20, Matrixd::value_type a21, Matrixd::value_type a22, Matrixd::value_type a23,
            Matrixd::value_type a30, Matrixd::value_type a31, Matrixd::value_type a32, Matrixd::value_type a33):
            CVBF_Object(false), 
            Matrixd(a00, a01, a02, a03,
                    a10, a11, a12, a13,
                    a20, a21, a22, a23,
                    a30, a31, a32, a33) {}

        virtual CVBF_Object* cloneType() const { return new RefMatrixd(); } 
        virtual CVBF_Object* clone(const CopyOp&) const { return new RefMatrixd(*this); }
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const RefMatrixd*>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Matrix"; }
        
        
    protected:
    
        virtual ~RefMatrixd() {}
};


} //namespace osg


#endif
