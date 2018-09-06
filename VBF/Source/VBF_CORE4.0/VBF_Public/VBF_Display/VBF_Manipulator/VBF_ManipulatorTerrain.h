#ifndef OSGGA_TERRAIN_MANIPULATOR
#define OSGGA_TERRAIN_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorOrbit.h>


namespace osgGA {

// 地形操作器

class OSGGA_EXPORT TerrainManipulator : public OrbitManipulator
{
   typedef OrbitManipulator inherited;

public:

   TerrainManipulator( int flags = DEFAULT_SETTINGS );
   TerrainManipulator( const TerrainManipulator& tm, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

   META_Object( osgGA, TerrainManipulator );


   virtual void setByMatrix( const osg::Matrixd& matrix );

   virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );

   virtual void setNode( osg::IVBF_SGNode* node );



   enum RotationMode
   {
      ELEVATION_AZIM_ROLL,
      ELEVATION_AZIM
   };

   // 设置/获取旋转模式
   virtual void SetRotationMode(RotationMode mode);
   RotationMode GetRotationMode() const;


protected:

   virtual bool performMovementMiddleMouseButton( double eventTimeDelta, double dx, double dy );
   virtual bool performMovementRightMouseButton( double eventTimeDelta, double dx, double dy );

   bool intersect( const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection ) const;
   void clampOrientation();

   osg::Vec3d m_vPreviousUp;
};


}

#endif /* OSGGA_TERRAIN_MANIPULATOR */
