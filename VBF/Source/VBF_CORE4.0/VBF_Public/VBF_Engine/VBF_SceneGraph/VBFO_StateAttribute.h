#ifndef OSG_STATEATTRIBUTE
#define OSG_STATEATTRIBUTE 1

#include <VBF_Engine/VBF_SceneGraph/Export>
#//include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/StateAttributeCallback>
#include <VBF_Engine/VBF_SceneGraph/Shader>
#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>

#include <typeinfo>
#include <utility>
#include <vector>

// define for the GL_EXT_secondary_color extension, GL_COLOR_SUM is OpenGL
// mode to be used to enable and disable the second color.
#ifndef GL_COLOR_SUM
#define GL_COLOR_SUM    0x8458
#endif

namespace osg {


// forward declare NodeVisitor, State & StateSet

class State;
class ShaderComposer;
class StateSet;
class Texture;


#define META_StateAttribute(library,name,type) \
        virtual osg::CVBF_Object* cloneType() const { return new name(); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; } \
        virtual const char* className() const { return #name; } \
        virtual Type getType() const { return type; }

/** COMPARE_StateAttribute_Types macro is a helper for implementing the StateAtribute::compare(..) method.*/
#define COMPARE_StateAttribute_Types(TYPE,rhs_attribute) \
            if (this==&rhs_attribute) return 0;\
            const std::type_info* type_lhs = &typeid(*this);\
            const std::type_info* type_rhs = &typeid(rhs_attribute);\
            if (type_lhs->before(*type_rhs)) return -1;\
            if (*type_lhs != *type_rhs) return 1;\
            const TYPE& rhs = static_cast<const TYPE&>(rhs_attribute);


/** COMPARE_StateAttribute_Parameter macro is a helper for implementing the StatateAtribute::compare(..) method.
  * Macro assumes that variable rhs has been correctly defined by preceding code
  * macro.*/
#define COMPARE_StateAttribute_Parameter(parameter) \
        if (parameter<rhs.parameter) return -1; \
        if (rhs.parameter<parameter) return 1;


/** Base class for state attributes.
*/     
class OSG_EXPORT StateAttribute : public CVBF_Object
{
    public :

        typedef GLenum          GLMode;        // ģʽ������ glEnable/glDisable(mode)		
        typedef unsigned int    GLModeValue;   // ����ָ��ģʽ��enabled (ON)��disabled (OFF)��������ָ��ģʽ�Ӹ��ڵ㵽�ӽڵ��override��Ϊ
        typedef unsigned int    OverrideValue; // ����ָ��StateAttributes��������Ϊ

		/** ������GLModeValues��OverrideValues��
		    ����GLModeValuesʱ�����е�ֵ�����壻 ����StateAttributeʱ��OverrideValue��OFF��OVERRIDE��INHERIT������
		    ��StateSet::setAttributeAndModes(..)��GLModeValue��OverrideValueͬʱʹ�ã������������ */
        enum Values
        {
            OFF          = 0x0, // GLMode and Override is disabled
            ON           = 0x1, // GLMode is enabled��Override is disabled
            OVERRIDE     = 0x2, // �����ӽڵ㶼���̳���һ���Ի�ģʽ���ӽڵ�����ǵĸ�����Ч��
			PROTECTED    = 0x4, // ��OVERRIDE��һ�����⣬��������ΪPROTECTED����Ⱦ���Ի�ģʽ�������ܸ��ڵ��Ӱ��            
            INHERIT      = 0x8  // ǿ���ӽڵ�̳и��ڵ����Ⱦ״̬��Ч�����ӽڵ����Ⱦ״̬����������ø��ڵ��״̬���
        };
        
        /** Type identifier to differentiate between different state types. */
        // typedef unsigned int Type;


        // StateAttribute::Type���ڱ�ʶStateAttribute��ͬ������
        enum Type
        {
            TEXTURE,
            
            POLYGONMODE,
            POLYGONOFFSET,
            MATERIAL,
            ALPHAFUNC,
            ANTIALIAS,
            COLORTABLE,
            CULLFACE,
            FOG,
            FRONTFACE,
            
            LIGHT,

            POINT,
            LINEWIDTH,
            LINESTIPPLE,
            POLYGONSTIPPLE,
            SHADEMODEL,
            TEXENV,
            TEXENVFILTER,
            TEXGEN,
            TEXMAT,
            LIGHTMODEL,
            BLENDFUNC,
            BLENDEQUATION,
            LOGICOP,
            STENCIL,
            COLORMASK,
            DEPTH,
            VIEWPORT,
            SCISSOR,
            BLENDCOLOR,
            MULTISAMPLE,
            CLIPPLANE,
            COLORMATRIX,
            VERTEXPROGRAM,
            FRAGMENTPROGRAM,
            POINTSPRITE,
            PROGRAM,
            CLAMPCOLOR,
            HINT,

            /// osgFX namespace
            VALIDATOR,
            VIEWMATRIXEXTRACTOR,
            
            /// osgNV namespace
            OSGNV_PARAMETER_BLOCK,

            // osgNVExt namespace
            OSGNVEXT_TEXTURE_SHADER,
            OSGNVEXT_VERTEX_PROGRAM,
            OSGNVEXT_REGISTER_COMBINERS,

            /// osgNVCg namespace
            OSGNVCG_PROGRAM,

            // osgNVSlang namespace
            OSGNVSLANG_PROGRAM,

            // osgNVParse
            OSGNVPARSE_PROGRAM_PARSER,

            UNIFORMBUFFERBINDING,
            TRANSFORMFEEDBACKBUFFERBINDING
        };
        
        /** Simple pairing between an attribute type and the member within that attribute type group.*/
        typedef std::pair<Type,unsigned int> TypeMemberPair;

        StateAttribute();     
        StateAttribute(const StateAttribute& sa,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
        

		// ����/��������
        virtual CVBF_Object* cloneType() const = 0;
        virtual CVBF_Object* clone(const CopyOp&) const = 0;

        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const StateAttribute*>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "StateAttribute"; }
        

		// �൱��dynamic_cast<>�����ٶȸ���
        virtual Texture* asTexture() { return 0; }
        virtual const Texture* asTexture() const { return 0; }

		// ��ȡ״̬����������ͱ�ʶ
        virtual Type getType() const = 0;

        /** Return the member identifier within the attribute's class type. Used for light number/clip plane number etc.*/
        virtual unsigned int getMember() const { return 0; }

        /** Return the TypeMemberPair that uniquely identifies this type member.*/
        inline TypeMemberPair getTypeMemberPair() const { return TypeMemberPair(getType(),getMember()); }

  		// �ж��Ƿ�������״̬����
        virtual bool isTextureAttribute() const { return false; }

        // ״̬���ԱȽ� Return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs
        virtual int compare(const StateAttribute& sa) const = 0;
        
        bool operator <  (const StateAttribute& rhs) const { return compare(rhs)<0; }
        bool operator == (const StateAttribute& rhs) const { return compare(rhs)==0; }
        bool operator != (const StateAttribute& rhs) const { return compare(rhs)!=0; }

        
        /** A vector of osg::StateSet pointers which is used to store the parent(s) of this StateAttribute.*/
        typedef std::vector<StateSet*> ParentList;

        /** Get the parent list of this StateAttribute. */
        inline const ParentList& getParents() const { return _parents; }

        inline StateSet* getParent(unsigned int i)  { return _parents[i]; }
        /**
         * Get a single const parent of this StateAttribute.
         * @param i index of the parent to get.
         * @return the parent i.
         */
        inline const StateSet* getParent(unsigned int i) const  { return _parents[i]; }

        /**
         * Get the number of parents of this StateAttribute.
         * @return the number of parents of this StateAttribute.
         */
        inline unsigned int getNumParents() const { return static_cast<unsigned int>(_parents.size()); }

        void setShaderComponent(ShaderComponent* sc) { _shaderComponent = sc; }
        ShaderComponent* getShaderComponent() { return _shaderComponent.get(); }
        const ShaderComponent* getShaderComponent() const { return _shaderComponent.get(); }

        struct ModeUsage
        {
            virtual ~ModeUsage() {}
            virtual void usesMode(GLMode mode) = 0;
            virtual void usesTextureMode(GLMode mode) = 0;
        };

        /** Return the modes associated with this StateAttribute.*/        
        virtual bool getModeUsage(ModeUsage&) const
        {
            // default to no GLMode's associated with use of the StateAttribute.
            return false;
        }
        
        /** Check the modes associated with this StateAttribute are supported by current OpenGL drivers,
          * and if not set the associated mode in osg::State to be black listed/invalid.
          * Return true if all associated modes are valid.*/
        virtual bool checkValidityOfAssociatedModes(osg::State&) const
        {
            // default to no black listed GLMode's associated with use of the StateAttribute.
            return true;
        }

        // provide callback for backwards compatibility.
        typedef osg::StateAttributeCallback Callback;

        /** Set the UpdateCallback which allows users to attach customize the updating of an object during the update traversal.*/
        void setUpdateCallback(StateAttributeCallback* uc);
        StateAttributeCallback* getUpdateCallback() { return _updateCallback.get(); }
        const StateAttributeCallback* getUpdateCallback() const { return _updateCallback.get(); }


        // ����/��ȡEventCallback�������û����¼�������ʱ���Զ���
        void setEventCallback(StateAttributeCallback* ec);
        StateAttributeCallback* getEventCallback() { return _eventCallback.get(); }
        const StateAttributeCallback* getEventCallback() const { return _eventCallback.get(); }

    
        /** apply the OpenGL state attributes. 
          * The render info for the current OpenGL context is passed
          * in to allow the StateAttribute to obtain details on the
          * the current context and state.
          */
        virtual void apply(State&) const {}

        // ���غ���
        virtual void compileGLObjects(State&) const {}
        virtual void resizeGLObjectBuffers(unsigned int /*maxSize*/) {}
        virtual void releaseGLObjects(State* =0) const {}


    protected:
    
        virtual ~StateAttribute() {}// IE���ܴ���

        void addParent(osg::StateSet* object);
        void removeParent(osg::StateSet* object);

        ParentList _parents;
        friend class osg::StateSet;

        ref_ptr<ShaderComponent>          _shaderComponent;

        ref_ptr<StateAttributeCallback>   _updateCallback;
        ref_ptr<StateAttributeCallback>   _eventCallback;
};

}

#endif
