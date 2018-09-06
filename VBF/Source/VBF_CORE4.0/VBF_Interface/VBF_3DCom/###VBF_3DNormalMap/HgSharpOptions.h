/**************************************************************************************************
* @file HgSharpOptions.h
* @note Gis��������
* @author c00005
* @data 2013-12-20
**************************************************************************************************/
#ifndef HG_SHARP_OPTIONS_H
#define HG_SHARP_OPTIONS_H

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <Types/VBF_Optional.h>

#include "export.h"

namespace FePlugin
{
    using namespace osgEarth;

    /**
    * @class HgGISOptions
    * @brief Gis��������
    * @note Gis��������̳���TileSourceOptions�����д洢����Ƭ�ĸ�ʽ��URL�Լ�����·��
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CHgSharpOptions : public CVBF_OptionsDriverSourceTile
    {
    public:
        /**  
        * @brief ���캯��
        * @note �������Ĺ��캯��  
        * @param opt [in] ����ȫ�ֵ�Options�����ڹ��챾�����
        * @return ��
        */
        CHgSharpOptions( const CVBF_OptionsDriverSourceTile& opt = CVBF_OptionsDriverSourceTile() );

        /**  
        * @brief ���캯��
        * @note �������캯��  
        * @param rhs [in] CHgSharpOptions��Ķ������ã�������ʼ�����б�����ֵ
        * @return ��
        */
        CHgSharpOptions( const CHgSharpOptions& rhs );

        /**  
        * @brief ��������
        * @note ����������
        * @return ��
        */
        virtual ~CHgSharpOptions();

    public:
        /**  
        * @note �����ļ�·��
        */
        CVBF_Optional<URI>& GetUrl() { return m_urlPath; }

        /**  
        * @note �����ļ�·�������Ҳ����޸�
        */
        const CVBF_Optional<URI>& GetUrl() const { return m_urlPath; }

        /**  
        * @note ���ر������
        */
        CVBF_Optional<std::string>& GetToken() { return m_strToken; }

        /**  
        * @note ���ر�����������Ҳ����޸�
        */
        const CVBF_Optional<std::string>& GetToken() const { return m_strToken; }

        /**  
        * @note ���ظ�ʽ
        */
        CVBF_Optional<std::string>& GetFormat() { return m_strFormat; }

        /**  
        * @note ���ظ�ʽ�����Ҳ����޸�
        */
        const CVBF_Optional<std::string>& GetFormat() const { return m_strFormat; }

        /**  
        * @note ���ػ���·��
        */
        CVBF_Optional<std::string>& GetCacheUrl() { return m_strCachePath; }

        /**  
        * @note ���ػ���·�������Ҳ����޸�
        */
        const CVBF_Optional<std::string>& GetCacheUrl() const { return m_strCachePath; }

    public:
        /**  
        * @brief ��ȡconf�е���Ϣ
        * @note ��ȡconf�е���Ϣ
        * @return Config ���ص���������һ���config��Ϣ
        */
        CVBF_Config GetConfig() const;

        /**  
        * @brief �ı�conf�е���Ϣ
        * @note �ı�conf�е���Ϣ�����ı䱾���д洢����Ϣ
        * @param conf [in] ����Ҫ���ı��conf����
        * @return ��
        */
        void MergeConfig( const CVBF_Config& conf );

        /**  
        * @brief ��conf��ȡ������Ϣ
        * @note �Ӵ����conf�л�ȡ��������Ϣ
        * @param conf [in] ������ȡ���е�������Ϣ
        * @return ��
        */
        void FromConfig( const CVBF_Config& conf );

    private:
        ///�洢�ļ�·����url
        CVBF_Optional<URI>         m_urlPath;
        ///�洢��ȫ���
        CVBF_Optional<std::string> m_strToken;
        ///�洢��ʽ
        CVBF_Optional<std::string> m_strFormat;
        ///����·��
        CVBF_Optional<std::string> m_strCachePath;
    };

}

#endif 


