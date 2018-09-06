#ifndef OSG_OCCLUDERNODE
#define OSG_OCCLUDERNODE 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupOccluder.h>
namespace osg {


class OSG_EXPORT OccluderNode : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupOccluder>
{
    public :        
        OccluderNode();
        OccluderNode(const OccluderNode&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, OccluderNode);
        
        // ����/��ȡ͹ƽ���ڵ���          
        void setOccluder(ConvexPlanarOccluder* occluder) { _occluder = occluder; }
        ConvexPlanarOccluder* getOccluder() { return _occluder.get(); }
        const ConvexPlanarOccluder* getOccluder() const { return _occluder.get(); }

        // ���غ����������Χ��
        virtual BoundingSphere computeBound() const;

    protected :
    
        virtual ~OccluderNode() {}// IE���ܴ���
        
        ref_ptr<ConvexPlanarOccluder>   _occluder;
};

}

#endif
