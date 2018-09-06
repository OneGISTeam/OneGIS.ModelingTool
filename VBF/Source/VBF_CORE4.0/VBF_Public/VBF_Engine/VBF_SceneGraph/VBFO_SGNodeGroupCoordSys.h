#ifndef OSG_COORDINATESYSTEMNODE
#define OSG_COORDINATESYSTEMNODE 1


#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <Types/VBF_Matrixd.h>



namespace osg
{



/** CoordinateFrame encapsulates the orientation of east, north and up.*/ 
typedef Matrixd CoordinateFrame;


/** CoordinateSystem encapsulate the coordinate system that is associated with objects in a scene.
    For an overview of common earth bases coordinate systems see http://www.colorado.edu/geography/gcraft/notes/coordsys/coordsys_f.html */
class OSG_EXPORT CVBF_SGNodeGroupCoordSys : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupCoordSys>
{
    public:
        CVBF_SGNodeGroupCoordSys();
        CVBF_SGNodeGroupCoordSys(const std::string& format, const std::string& cs);
        CVBF_SGNodeGroupCoordSys(const CVBF_SGNodeGroupCoordSys&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osg,CVBF_SGNodeGroupCoordSys);
        
        
        // 设置坐标系统节点，通过另一个坐标系统的格式、坐标系统字符换和椭球模型
        void set(const CVBF_SGNodeGroupCoordSys& csn);
          
        // 设置格式，通常为WKT, PROJ4, USGS等
        void setFormat(const std::string& format);
        const std::string& getFormat() const;

        void setCoordinateSystem(const std::string& cs);
        const std::string& getCoordinateSystem() const;
                
        void setEllipsoidModel(EllipsoidModel* ellipsode);
        EllipsoidModel* getEllipsoidModel() ;
        const EllipsoidModel* getEllipsoidModel() const;
        
        // 计算给定点的局部坐标框架
        CoordinateFrame computeLocalCoordinateFrame(const Vec3d& position) const;
        
        // 计算给定点的的UP向量（局部坐标系）
        osg::Vec3d computeLocalUpVector(const Vec3d& position) const;

    protected:

        virtual ~CVBF_SGNodeGroupCoordSys();
                
        std::string             _format;
        std::string             _cs;
        ref_ptr<EllipsoidModel> _ellipsoidModel;

};




}
#endif
