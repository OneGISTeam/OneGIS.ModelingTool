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

#ifndef OSG_IO_UTILS
#define OSG_IO_UTILS 1

#include <ostream>
#include <istream>

#include <Types/Vec4d>
#include <Types/Vec4ub>
#include <Types/Vec2b>
#include <Types/Vec3b>
#include <Types/Vec4b>
#include <Types/Vec2s>
#include <Types/Vec3s>
#include <Types/Vec4s>
#include <Types/VBF_Matrixf.h>
#include <Types/VBF_Matrixd.h>
#include <Types/VBF_Plane.h>

namespace osg {


//////////////////////////////////////////////////////////////////////////
// Vec2f streaming operators
inline std::ostream& operator << (std::ostream& output, const Vec2f& vec)
{
    output << vec._v[0] << " " << vec._v[1];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec2f& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec2d steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec2d& vec)
{
    output << vec._v[0] << " " << vec._v[1];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec2d& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec3f steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec3f& vec)
{
    output << vec._v[0] << " "
           << vec._v[1] << " "
           << vec._v[2];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec3f& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1] >> std::ws >> vec._v[2];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Vec3d steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec3d& vec)
{
    output << vec._v[0] << " "
           << vec._v[1] << " "
           << vec._v[2];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec3d& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1] >> std::ws >> vec._v[2];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Vec3f steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec4f& vec)
{
    output  << vec._v[0] << " "
            << vec._v[1] << " "
            << vec._v[2] << " "
            << vec._v[3];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec4f& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws
          >> vec._v[3];
    return input;
}



//////////////////////////////////////////////////////////////////////////
// Vec4d steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec4d& vec)
{
    output << vec._v[0] << " "
           << vec._v[1] << " "
           << vec._v[2] << " "
           << vec._v[3];
    return output;     // to enable cascading
}
inline std::istream& operator >> (std::istream& input, Vec4d& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws
          >> vec._v[3];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Vec2b steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec2b& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec2b& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec3b steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec3b& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1] << " "
           << (int)vec._v[2];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec3b& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1] >> std::ws >> vec._v[2];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec4b steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec4b& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1] << " "
           << (int)vec._v[2] << " "
           << (int)vec._v[3];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec4b& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws 
          >> vec._v[3];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Vec2s steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec2s& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec2s& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec3s steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec3s& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1] << " "
           << (int)vec._v[2];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec3s& vec)
{
    input >> vec._v[0] >> std::ws >> vec._v[1] >> std::ws >> vec._v[2];
    return input;
}

//////////////////////////////////////////////////////////////////////////
// Vec4s steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec4s& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1] << " "
           << (int)vec._v[2] << " "
           << (int)vec._v[3];
    return output; // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec4s& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws
          >> vec._v[3];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Matrixf steaming operators.
inline std::ostream& operator<< (std::ostream& os, const Matrixf& m )
{
    os << "{"<<std::endl;
    for(int row=0; row<4; ++row) {
        os << "\t";
        for(int col=0; col<4; ++col)
            os << m(row,col) << " ";
        os << std::endl;
    }
    os << "}" << std::endl;
    return os;
}


//////////////////////////////////////////////////////////////////////////
// Matrixd steaming operators.
inline std::ostream& operator<< (std::ostream& os, const Matrixd& m )
{
    os << "{"<<std::endl;
    for(int row=0; row<4; ++row) {
        os << "\t";
        for(int col=0; col<4; ++col)
            os << m(row,col) << " ";
        os << std::endl;
    }
    os << "}" << std::endl;
    return os;
}

//////////////////////////////////////////////////////////////////////////
// Vec4ub steaming operators.
inline std::ostream& operator << (std::ostream& output, const Vec4ub& vec)
{
    output << (int)vec._v[0] << " "
           << (int)vec._v[1] << " "
           << (int)vec._v[2] << " "
           << (int)vec._v[3];
    return output;         // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Vec4ub& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws
          >> vec._v[3];
    return input;
}


//////////////////////////////////////////////////////////////////////////
// Quat steaming operators.
inline std::ostream& operator << (std::ostream& output, const Quat& vec)
{
    output << vec._v[0] << " "
       << vec._v[1] << " "
       << vec._v[2] << " "
       << vec._v[3];
    return output;     // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Quat& vec)
{
    input >> vec._v[0] >> std::ws
          >> vec._v[1] >> std::ws
          >> vec._v[2] >> std::ws
          >> vec._v[3];
    return input;
}



//////////////////////////////////////////////////////////////////////////
// Plane steaming operators.
inline std::ostream& operator << (std::ostream& output, const Plane& pl)
{
    output << pl[0] << " "
           << pl[1] << " "
           << pl[2] << " "
           << pl[3];
    return output;         // to enable cascading
}

inline std::istream& operator >> (std::istream& input, Plane& vec)
{
    input >> vec[0] >> std::ws
          >> vec[1] >> std::ws
          >> vec[2] >> std::ws
          >> vec[3];
    return input;
}

}    // end of namespace osg
#endif
