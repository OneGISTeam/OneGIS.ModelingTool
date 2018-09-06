#ifndef OSG_TexGenNode
#define OSG_TexGenNode 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexGen.h>

namespace osg {

class IVBF_SGNodeGroupTexGen : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupTexGen(){}
	IVBF_SGNodeGroupTexGen(const IVBF_SGNodeGroupTexGen& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupTexGen(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}

	enum ReferenceFrame
	{
		RELATIVE_RF,
		ABSOLUTE_RF
	};

	
	virtual void setReferenceFrame(ReferenceFrame rf)=0;
	virtual ReferenceFrame getReferenceFrame() const =0;

	/** Set the texture unit that this TexGenNode is associated with.*/
	virtual void setTextureUnit(unsigned int textureUnit)=0;

	virtual unsigned int getTextureUnit() const =0;

	/** Set the TexGen. */
	virtual void setTexGen(TexGen* texgen)=0;
	virtual  TexGen* getTexGen() =0;
	virtual  const TexGen* getTexGen() const =0;

};

/** IVBF_SGNode for defining the position of TexGen in the scene. */
class OSG_EXPORT TexGenNode : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupTexGen>
{

    public:

        TexGenNode();
        TexGenNode(TexGen* texgen);

        TexGenNode(const TexGenNode& tgb, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, TexGenNode);
    
       
        
        /** Set the TexGenNode's ReferenceFrame, either to be relative to its
          * parent reference frame. */
        void setReferenceFrame(ReferenceFrame rf);
        
        /** Get the TexGenNode's ReferenceFrame.*/
        ReferenceFrame getReferenceFrame() const { return _referenceFrame; }

        /** Set the texture unit that this TexGenNode is associated with.*/
        void setTextureUnit(unsigned int textureUnit) { _textureUnit = textureUnit; }

        unsigned int getTextureUnit() const { return _textureUnit; }

        /** Set the TexGen. */
        void setTexGen(TexGen* texgen);
        
        /** Get the TexGen. */
        inline TexGen* getTexGen() { return _texgen.get(); }

        /** Get the const TexGen. */
        inline const TexGen* getTexGen() const { return _texgen.get(); }

        /** Set whether to use a mutex to ensure ref() and unref() are thread safe.*/
        virtual void setThreadSafeRefUnref(bool threadSafe);

    protected:

        virtual ~TexGenNode();

        unsigned int _textureUnit;
        ref_ptr<TexGen> _texgen;

        ReferenceFrame                  _referenceFrame;
};

}

#endif
