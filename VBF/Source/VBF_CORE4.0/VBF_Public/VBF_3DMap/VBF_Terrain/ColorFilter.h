#ifndef OSGEARTH_COLOR_FILTER_H
#define OSGEARTH_COLOR_FILTER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <vector>


namespace osgEarth
{
	// 颜色过滤器是一个内联的着色器，用于图像处理（after texturing but before lighting）
    class ColorFilter : public ::CVBF_Referenced
    {
    protected:
        ColorFilter() { }
    public:
		// 在自定义的着色器上调用的函数名
		// 该函数必须有signature: void function(in int slot, inout vec4 color)
        // 匹配该signature失败将导致着色器编译错误
        virtual std::string getEntryPointFunctionName() const =0;

		// 在状态集上安装uniforms或过滤器需要的其他东西
        virtual void install( osg::StateSet* pStateSet ) const =0;

		// 串行化为配置项
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }
    };

	// 颜色过滤器链，按顺序执行
    typedef std::vector< ref_ptr<ColorFilter> > ColorFilterChain;


	// 颜色过滤器的注册器
    class OSGEARTH_EXPORT ColorFilterRegistry
    {
    public:
        static ColorFilterRegistry* instance();

    public:
        // 根据配置文件，创建颜色过滤器链，至少有一个创建成功才能返回true
        bool readChain(const CVBF_Config& conf, ColorFilterChain& out_chain);

        // 根据颜色过滤器链,串行化到配置文件，至少有一个成功才能返回true
        bool writeChain(const ColorFilterChain& chain, CVBF_Config& out_config);

        // 添加一个颜色过滤器
        void add( const std::string& key, class IVBF_ColorFilterFactory* factory );

    public:
        ColorFilterRegistry();
        virtual ~ColorFilterRegistry();

        // 为了支持串行化，必须重载该函数
        virtual CVBF_Config getConfig() const;

    private:
        typedef std::map<std::string, class IVBF_ColorFilterFactory*> FactoryMap;
        FactoryMap _factories;
        ColorFilter* createOne(const CVBF_Config& conf) const;
    };

    // 接口类，用于根据配置文件创建一个ColorFilter的实例(被OSGEARTH_REGISTER_COLORFILTER宏调用)
    class IVBF_ColorFilterFactory
	{
    public:
        virtual ColorFilter* create(const CVBF_Config& conf) const =0;
        virtual ~IVBF_ColorFilterFactory() { }
    };

    // internal: proxy class used by the registraion macro
    template<typename T>
    struct ColorFilterRegistrationProxy : public IVBF_ColorFilterFactory
	{
        ColorFilterRegistrationProxy(const std::string& key) 
		{ 
			ColorFilterRegistry::instance()->add(key, this); 
		}
        ColorFilter* create(const CVBF_Config& conf) const { return new T(conf); }
    };

    // 用于注册颜色过滤器的宏
#define OSGEARTH_REGISTER_COLORFILTER( KEY, CLASSNAME ) \
    static osgEarth::ColorFilterRegistrationProxy< CLASSNAME > s_osgEarthColorFilterRegistrationProxy##KEY( #KEY )

}
#endif // OSGEARTH_IMAGE_FILTER_H
