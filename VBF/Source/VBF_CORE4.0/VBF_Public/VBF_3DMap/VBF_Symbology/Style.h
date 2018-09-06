#ifndef OSGEARTHSYMBOLOGY_STYLE_H
#define OSGEARTHSYMBOLOGY_STYLE_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <Types/VBF_Color.h>
//#include <VBF_3DMap/VBF_Symbology/Query.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolInstanceIcon.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolPoint.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolLine.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolPolygon.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolMarker.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolInstanceModel.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolExtrusion.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolAltitude.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolText.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolSkins.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolRender.h>
#include <VBF_3DMap/VBF_Symbology/VBF_ResourceLibrary.h>

#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <vector>

namespace osgEarth { namespace Symbology 
{
	// ���ŵļ��ϣ����򣩣����������κ���Ⱦ�����弰�����Ķ���
    class OSGEARTHSYMBOLOGY_EXPORT Style
    {
    public:
        Style( const std::string& name = "" );
        Style(const CVBF_Config& conf);
        Style(const Style& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL ); 
        virtual ~Style();

        Style& operator = (const Style& rhs);


		// ��ȡ/���÷�������
        const std::string& getName() const { return m_sName; }
        void setName( const std::string& value ) { m_sName = value; }

		// ���������һ���ϲ����µķ��
        Style combineWith( const Style& rhs ) const;

		// ����Ƿ�Ϊ��
        bool empty() const { return _symbols.empty(); }

		// ��ӷ���
        void addSymbol(Symbol* symbol);
        void add(Symbol* symbol) { addSymbol(symbol); }

		// �Ƴ�����
        bool removeSymbol (Symbol* symbol);

        // ͨ�������Ƴ�һ������
        template<typename T>
        bool remove()
        {
            Symbol* s = get<T>();
            return s ? removeSymbol(s) : false;
        }

        // ͨ�����ͻ�ȡһ�����ţ���ȡ��һ����
        template<typename T>
        T* getSymbol()
        {
            for (SymbolList::const_iterator it = _symbols.begin(); it != _symbols.end(); ++it)
            {
                Symbol* symbol = (*it).get();
                T* s = dynamic_cast<T*>(symbol);
                if (s)
                    return s;
            }
            return 0L;
        }
        template<typename T> T* get() { return getSymbol<T>(); } // alias

        // �Ƿ��������ģ�����͵ķ���
        template<typename T> bool has() { return get<T>() != 0L; }
        template<typename T> bool has() const { return get<T>() != 0L; }

        template<typename T>
        const T* getSymbol() const
        {
            for (SymbolList::const_iterator it = _symbols.begin(); it != _symbols.end(); ++it)
            {
                Symbol* symbol = (*it).get();
                const T* s = dynamic_cast<const T*>(symbol);
                if (s)
                    return s;
            }
            return 0L;
        }
        template<typename T> const T* get() const { return getSymbol<T>(); } // alias

        // ��ȡ����һ�����򴴽��������ڣ�����ģ�����͵ķ���
        template<typename T>
        T* getOrCreateSymbol()
        {
            T* sym = getSymbol<T>();
            if ( !sym )
            {
                sym = new T();
                addSymbol( sym );
            }
            return sym;
        }

        template<typename T> T* getOrCreate() { return getOrCreateSymbol<T>(); } // alias


        virtual CVBF_Config getConfig( bool keepOrigType =true ) const;
        void mergeConfig( const CVBF_Config& conf );

        void fromSLD(const CVBF_Config&);
        
    protected:
        std::string                 m_sName;
        SymbolList                  _symbols;
        std::string                 _origType;
        std::string                 _origData;
        CVBF_Optional<URI>          _uri;
    };

    typedef std::vector<Style>           StyleList;
    typedef std::map<std::string, Style> StyleMap;

} } // namespace osgEarth::Symbology


#endif // OSGEARTHSYMBOLOGY_STYLE_H
