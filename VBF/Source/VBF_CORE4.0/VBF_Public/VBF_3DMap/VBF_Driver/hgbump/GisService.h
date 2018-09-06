/**************************************************************************************************
* @file GisService.h
* @note �ṩGis������Ϣ,��Ҫ���ڶ�ȡ�����ļ��е�������Ϣ�Լ�����URL
* @author c00005
* @data 2013-12-20
**************************************************************************************************/
#ifndef CGisService_H
#define CGisService_H

#include <list>
#include <VBF_3DMap/VBF_Terrain/VBF_Profile.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>

#include "export.h"
#include "Extent.h"
#include "HgSharpOptions.h"


using namespace osgEarth;

namespace FePlugin
{
    class VBF_3DNormalMap_EXPORT CTileInfo
    {
    public:
        /**  
        * @brief Ĭ�ϵĹ��캯��
        * @note Ĭ�ϵĹ��캯��
        * @return ��
        */
        CTileInfo();

        /**  
        * @brief ���캯��
        * @note ���в����Ĺ��캯��  
        * @param tile_size [in] ����Ӱ����Ƭ�Ĵ�С
        * @param format [in] ����Ӱ����Ƭ���ļ���ʽ
        * @param min_level [in] ��С����ʾ����
        * @param max_level [in] ������ʾ����
        * @param _num_tiles_wide [in] �������Ƭ����Ŀ
        * @param _num_tiles_high [in] �������Ƭ����Ŀ
        * @return ��
        */
        CTileInfo( int tile_size, const std::string& format, int min_level, int max_level,
            int _num_tiles_wide, int _num_tiles_high );

        /**  
        * @brief ���캯��
        * @note �������캯��  
        * @param rhs [in] ���ڳ�ʼ�������
        * @return ��
        */
        CTileInfo( const CTileInfo& rhs );

        /**  
        * @brief ��ֵ����
        * @note ��ֵ����  
        * @param rhs [in] CTileInfo��Ķ������ã�������ʼ�����б�����ֵ
        * @return ��
        */
        CTileInfo & operator= (const CTileInfo &other);

        /**  
        * @note ���ظ�CTileInfo�Ƿ���Ч
        */
        virtual bool IsValid() const;

        /**  
        * @note ���ظ�Ӱ����Ƭ�Ĵ�С
        */
        virtual int GetTileSize() const;

        /**  
        * @note ���ظ�Ӱ����Ƭ�ļ��ĸ�ʽ
        */
        virtual const std::string& GetFormat() const;

        /**  
        * @note ���ظ�Ӱ����Ƭ����С��Lod����
        */
        virtual int GetMinLevel() const;

        /**  
        * @note ���ظ�Ӱ����Ƭ������Lod����
        */
        virtual int GetMaxLevel() const;

        /**  
        * @note ���ظýṹ�������Ƭ����
        */
        virtual int GetNumTilesWide() const;

        /**
        * @note ���ظýṹ�������Ƭ����
        */
        virtual int GetNumTilesHigh() const;

    private:
        ///Ӱ����Ƭ�ļ��ĸ�ʽ
        std::string m_strFormat;
        ///Ӱ����Ƭ�ļ��Ĵ�С
        int m_nTileSize;
        ///Ӱ����Ƭ�ļ���ʾ����С�������
        int m_nMinLevel, m_nMaxLevel;
        ///�Ƿ���Ч
        bool m_bIsValid;
        ///�������Ƭ����
        int m_nNumTilesWide;
        ///�������Ƭ����
        int m_nNumTilesHigh;
    };

    /**
    * @class GisService
    * @brief Gis����Ľӿ�
    * @note Gis����Ľӿ�,���Ե��ø�Gis����Ƭ����Ϣ����ȡ�����ļ�����Ϣ������URL
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CGisService
    {
    public:

        /**  
        * @brief ���캯��
        * @note Ĭ�Ϲ��캯��
        * @return ��
        */
        CGisService(void);

        /**  
        * @brief ���캯��
        * @note ���в����Ĺ��캯��  
        * @param bIsValid [in] �Ƿ��ʼ���ɹ�
        * @param uriUri [in] �����ļ���uri
        * @param pProfile [in] ��Gis�����profile
        * @param strErrorMsg [in] ������Ϣ
        * @param plistLayers [in] Gis�����ͼ���б�
        * @param bTiled [in] �Ƿ��ʼ������Ƭ��Ϣ
        * @param tileInfo [in] �洢��Ƭ��Ϣ
        * @param strType [in] Gis�������Ƭ�Ĵ洢�ṹ���л����л���������
        * @return ��
        */
        CGisService( bool bIsValid, URI uriUri, const CVBF_Profile * pProfile, std::string strErrorMsg,
            bool bTiled, CTileInfo tileInfo, std::string strType );

        /**  
        * @brief ���캯��
        * @note �������캯��  
        * @param rhs [in] ��Ķ�������,���ڳ�ʼ�������
        * @return ��
        */
        CGisService( const CGisService& rhs );

        /**  
        * @brief ��ֵ����
        * @note ��ֵ����  
        * @param rhs [in] ��Ķ������ã�������ʼ�����б�����ֵ
        * @return ��
        */
        CGisService & operator= (const CGisService &other);

        /**  
        * @brief ��ʼ������
        * @note ��ʼ����Gis���񣬸��ݸ���URI�е������ļ�������Ҫ�õ������ö�ȡ����������
        * @param uri [in] ����Ҫ��ȡ�������ļ���uri
        * @param options [in] 
        * @return bool �����Ƿ��ȡ������Ϣ�Ƿ����
        */
        virtual bool Init( const URI& uri, const osgDB::Options* options =0L );

        /**  
          * @brief ��ȡ�ļ���URL
          * @note ͨ�������Key�Լ��ļ�������·����ͨ�������Typeƥ����ʺϵ�URL
          * @param key [in]
          * @param full [in] �ļ��е�·��
          * @return std::string ����ƴ�Ӻ��URL
        */
        virtual std::string ConstructUrl(const CVBF_TileKey& key, const CHgSharpOptions& options ) const;
        
        /**  
        * @brief ���ͼƬ�Ƿ���Ч
        * @note ͼƬ�����ڱ߽紦���ĸ��ǻ�������һ�����к�ɫ����ͼƬȫ�ڣ�Ϊ��Ч
        * @return ��Ч��Ϊtrue, ����Ϊfalse
        */
        virtual bool CheckBlackImage(osg::Image* image);
        
        /**  
        * @note ���ظ����Ƿ��ʼ���ɹ�
        */
        virtual bool IsValid() const;

        /**
        * @note �����ڶ�ȡ�����ļ�ʱ����Ƭ����Ϣ�Ƿ��ȡ�ɹ�
        */
        virtual bool IsTiled() const;

        /**  
        * @note set���ܺ�����������ʱ���ô�����Ϣ  
        */
        bool SetError( const std::string& );

        /**
        * @note ��������ʼ��ʧ�ܣ��򷵻ش�����Ϣ
        */
        virtual const std::string& GetError() const;

        /**  
        * @note ���ظ�gis������ص�profile��Ϣ
        */
        virtual const CVBF_Profile* GetProfile() const;

        /**  
        * @note ���ظ�gis�������Ƭ����Ϣ�����ɱ��޸�
        */
        virtual const CTileInfo& GetTileInfo() const;

        /**  
        * @note ���ظ�gis�������֯�ṹ����
        */
        virtual std::string GetTileType() const;

        /**  
        * @note �����Ƿ���ͼƬ
        */
        virtual std::string GetStrCheck() const; 
    private:
        ///�Ƿ��ʼ���ɹ�
        bool m_bIsValid;
        ///���洫��������ļ���uri
        URI m_uriUri;
        ///��Gis�����profile
        ref_ptr<const CVBF_Profile> m_rpProfile;
        ///������Ϣ
        std::string m_strErrorMsg;
        ///�Ƿ��ʼ������Ƭ��Ϣ
        bool m_bTiled;
        ///�洢��Ƭ��Ϣ
        CTileInfo m_tileInfo;
        ///��Gis�������Ƭ�Ĵ洢�ṹ���л����л���������
        std::string m_strType;
        ///�ж��Ƿ��ͼƬ���м�⣬����Ŀ���������ȫ�ڵ�ͼƬ������Ϊ��Ч��һ�㲻��Ҫ���
        std::string m_strCheck;
    };
}

#endif
