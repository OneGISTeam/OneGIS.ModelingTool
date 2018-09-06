#ifndef OSG_LIGHT
#define OSG_LIGHT 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>
#include <Types/Vec3>
#include <Types/Vec4>

#ifndef GL_LIGHT0
    #define GL_LIGHT0 0x4000
    #define GL_LIGHT1 0x4001
    #define GL_LIGHT2 0x4002
    #define GL_LIGHT3 0x4003
    #define GL_LIGHT4 0x4004
    #define GL_LIGHT5 0x4005
    #define GL_LIGHT6 0x4006
    #define GL_LIGHT7 0x4007
#endif

#ifndef GL_LIGHTING
    #define GL_LIGHTING 0x0B50
#endif



namespace osg {

// 封装了OpenGL的glLight() 功能
class OSG_EXPORT Light : public StateAttribute
{
    public :
        Light();
        Light(unsigned int lightnum);
		// IE可能错误
        Light(const Light& light,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(light,copyop),
            _lightnum(light._lightnum),
            _ambient(light._ambient),
            _diffuse(light._diffuse),
            _specular(light._specular),
            _position(light._position),
            _direction(light._direction),
            _constant_attenuation(light._constant_attenuation),
            _linear_attenuation(light._linear_attenuation),
            _quadratic_attenuation(light._quadratic_attenuation),
            _spot_exponent(light._spot_exponent),
            _spot_cutoff(light._spot_cutoff) {}
        
        virtual osg::CVBF_Object* cloneType() const { return new Light(_lightnum); }
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new Light(*this,copyop); }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const Light *>(obj)!=NULL; }
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Light"; }
        virtual Type getType() const { return LIGHT; }

        /** Return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs. */
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Parameter macros below.
            COMPARE_StateAttribute_Types(Light,sa)

            // compare each parameter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_lightnum)
            COMPARE_StateAttribute_Parameter(_ambient)
            COMPARE_StateAttribute_Parameter(_diffuse)
            COMPARE_StateAttribute_Parameter(_specular)
            COMPARE_StateAttribute_Parameter(_position)
            COMPARE_StateAttribute_Parameter(_direction)
            COMPARE_StateAttribute_Parameter(_constant_attenuation)
            COMPARE_StateAttribute_Parameter(_linear_attenuation)
            COMPARE_StateAttribute_Parameter(_quadratic_attenuation)
            COMPARE_StateAttribute_Parameter(_spot_exponent)
            COMPARE_StateAttribute_Parameter(_spot_cutoff)

            return 0; // passed all the above comparison macros, must be equal.
        }

        virtual unsigned int getMember() const { return _lightnum; }

        virtual bool getModeUsage(StateAttribute::ModeUsage& usage) const
        {
            usage.usesMode(GL_LIGHT0+_lightnum);
            return true;
        }
        
        
		// 设置/获取操作OpenGL哪个光源（Set which OpenGL light to operate on）
        void setLightNum(int num);
        int getLightNum() const { return _lightnum; }

		// 设置/获取环境光颜色
        inline void setAmbient( const Vec4& ambient ) { _ambient = ambient; }
        inline const Vec4& getAmbient() const { return _ambient; }

		// 设置/获取漫反射光颜色
        inline void setDiffuse( const Vec4& diffuse ) { _diffuse = diffuse; }
        inline const Vec4& getDiffuse() const { return _diffuse; }

        // 设置/获取镜面光颜色
        inline void setSpecular( const Vec4& specular ) { _specular = specular; }
        inline const Vec4& getSpecular() const { return _specular; }
   
		// 设置/获取光源位置
        inline void setPosition( const Vec4& position ) { _position = position; }  
        inline const Vec4& getPosition() const { return _position; }

        // 设置/获取光源方向   
        inline void setDirection( const Vec3& direction ) { _direction = direction; }   
        inline const Vec3& getDirection() const { return _direction; }

		// 设置/获取光的常量衰减值
        inline void setConstantAttenuation( float constant_attenuation )     { _constant_attenuation = constant_attenuation; }
        inline float getConstantAttenuation() const { return _constant_attenuation; }

        // 设置/获取光的线性衰减值
        inline void setLinearAttenuation ( float linear_attenuation )        { _linear_attenuation = linear_attenuation; }
        inline float getLinearAttenuation () const { return _linear_attenuation; }

		// 设置/获取光的两次方衰减值
        inline void setQuadraticAttenuation ( float quadratic_attenuation )  { _quadratic_attenuation = quadratic_attenuation; }
        inline float getQuadraticAttenuation()  const { return _quadratic_attenuation; }

        // 设置/获取光的指数衰减值
        inline void setSpotExponent( float spot_exponent )                   { _spot_exponent = spot_exponent; }
        inline float getSpotExponent() const { return _spot_exponent; }

        /** Set the spot cutoff of the light. */
        inline void setSpotCutoff( float spot_cutoff )                       { _spot_cutoff = spot_cutoff; }
        inline float getSpotCutoff() const                                   { return _spot_cutoff; }

		// 捕获当前OpenGL状态的光源设置，并保存到this
        void captureLightState();

        /** Apply the light's state to the OpenGL state machine. */
        virtual void apply(State& state) const;

    protected :
    
        virtual ~Light();

        /** Initialize the light's settings with some decent defaults. */
        void init();

        int _lightnum;                           // OpenGL light number

        Vec4 _ambient;                           // r, g, b, w
        Vec4 _diffuse;                           // r, g, b, w
        Vec4 _specular;                          // r, g, b, w
        Vec4 _position;                          // x, y, z, w
        Vec3 _direction;                         // x, y, z
        float _constant_attenuation;             // constant
        float _linear_attenuation;               // linear
        float _quadratic_attenuation;            // quadratic
        float _spot_exponent;                    // exponent
        float _spot_cutoff;                      // spread
};

}

#endif
