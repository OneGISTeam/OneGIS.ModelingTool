#ifndef OSGEARTH_COLOR_FILTER_H
#define OSGEARTH_COLOR_FILTER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <vector>


namespace osgEarth
{
	// ��ɫ��������һ����������ɫ��������ͼ����after texturing but before lighting��
    class ColorFilter : public ::CVBF_Referenced
    {
    protected:
        ColorFilter() { }
    public:
		// ���Զ������ɫ���ϵ��õĺ�����
		// �ú���������signature: void function(in int slot, inout vec4 color)
        // ƥ���signatureʧ�ܽ�������ɫ���������
        virtual std::string getEntryPointFunctionName() const =0;

		// ��״̬���ϰ�װuniforms���������Ҫ����������
        virtual void install( osg::StateSet* pStateSet ) const =0;

		// ���л�Ϊ������
        virtual CVBF_Config getConfig() const { return CVBF_Config(); }
    };

	// ��ɫ������������˳��ִ��
    typedef std::vector< ref_ptr<ColorFilter> > ColorFilterChain;


	// ��ɫ��������ע����
    class OSGEARTH_EXPORT ColorFilterRegistry
    {
    public:
        static ColorFilterRegistry* instance();

    public:
        // ���������ļ���������ɫ����������������һ�������ɹ����ܷ���true
        bool readChain(const CVBF_Config& conf, ColorFilterChain& out_chain);

        // ������ɫ��������,���л��������ļ���������һ���ɹ����ܷ���true
        bool writeChain(const ColorFilterChain& chain, CVBF_Config& out_config);

        // ���һ����ɫ������
        void add( const std::string& key, class IVBF_ColorFilterFactory* factory );

    public:
        ColorFilterRegistry();
        virtual ~ColorFilterRegistry();

        // Ϊ��֧�ִ��л����������ظú���
        virtual CVBF_Config getConfig() const;

    private:
        typedef std::map<std::string, class IVBF_ColorFilterFactory*> FactoryMap;
        FactoryMap _factories;
        ColorFilter* createOne(const CVBF_Config& conf) const;
    };

    // �ӿ��࣬���ڸ��������ļ�����һ��ColorFilter��ʵ��(��OSGEARTH_REGISTER_COLORFILTER�����)
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

    // ����ע����ɫ�������ĺ�
#define OSGEARTH_REGISTER_COLORFILTER( KEY, CLASSNAME ) \
    static osgEarth::ColorFilterRegistrationProxy< CLASSNAME > s_osgEarthColorFilterRegistrationProxy##KEY( #KEY )

}
#endif // OSGEARTH_IMAGE_FILTER_H
