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
        
        
        // ��������ϵͳ�ڵ㣬ͨ����һ������ϵͳ�ĸ�ʽ������ϵͳ�ַ���������ģ��
        void set(const CVBF_SGNodeGroupCoordSys& csn);
          
        // ���ø�ʽ��ͨ��ΪWKT, PROJ4, USGS��
        void setFormat(const std::string& format);
        const std::string& getFormat() const;

        void setCoordinateSystem(const std::string& cs);
        const std::string& getCoordinateSystem() const;
                
        void setEllipsoidModel(EllipsoidModel* ellipsode);
        EllipsoidModel* getEllipsoidModel() ;
        const EllipsoidModel* getEllipsoidModel() const;
        
        // ���������ľֲ�������
        CoordinateFrame computeLocalCoordinateFrame(const Vec3d& position) const;
        
        // ���������ĵ�UP�������ֲ�����ϵ��
        osg::Vec3d computeLocalUpVector(const Vec3d& position) const;

    protected:

        virtual ~CVBF_SGNodeGroupCoordSys();
                
        std::string             _format;
        std::string             _cs;
        ref_ptr<EllipsoidModel> _ellipsoidModel;

};




}
#endif
