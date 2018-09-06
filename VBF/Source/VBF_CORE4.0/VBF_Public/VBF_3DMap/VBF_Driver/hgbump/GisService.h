/**************************************************************************************************
* @file GisService.h
* @note 提供Gis服务信息,主要用于读取配置文件中的配置信息以及构建URL
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
        * @brief 默认的构造函数
        * @note 默认的构造函数
        * @return 无
        */
        CTileInfo();

        /**  
        * @brief 构造函数
        * @note 带有参数的构造函数  
        * @param tile_size [in] 传入影像瓦片的大小
        * @param format [in] 传入影像瓦片的文件格式
        * @param min_level [in] 最小的显示级别
        * @param max_level [in] 最大的显示级别
        * @param _num_tiles_wide [in] 横向的瓦片的数目
        * @param _num_tiles_high [in] 纵向的瓦片的数目
        * @return 无
        */
        CTileInfo( int tile_size, const std::string& format, int min_level, int max_level,
            int _num_tiles_wide, int _num_tiles_high );

        /**  
        * @brief 构造函数
        * @note 拷贝构造函数  
        * @param rhs [in] 用于初始化类对象
        * @return 无
        */
        CTileInfo( const CTileInfo& rhs );

        /**  
        * @brief 赋值函数
        * @note 赋值函数  
        * @param rhs [in] CTileInfo类的对象引用，用来初始化类中变量的值
        * @return 无
        */
        CTileInfo & operator= (const CTileInfo &other);

        /**  
        * @note 返回该CTileInfo是否有效
        */
        virtual bool IsValid() const;

        /**  
        * @note 返回该影像瓦片的大小
        */
        virtual int GetTileSize() const;

        /**  
        * @note 返回该影像瓦片文件的格式
        */
        virtual const std::string& GetFormat() const;

        /**  
        * @note 返回该影像瓦片的最小的Lod级数
        */
        virtual int GetMinLevel() const;

        /**  
        * @note 返回该影像瓦片的最大的Lod级数
        */
        virtual int GetMaxLevel() const;

        /**  
        * @note 返回该结构横向的瓦片数量
        */
        virtual int GetNumTilesWide() const;

        /**
        * @note 返回该结构纵向的瓦片数量
        */
        virtual int GetNumTilesHigh() const;

    private:
        ///影像瓦片文件的格式
        std::string m_strFormat;
        ///影像瓦片文件的大小
        int m_nTileSize;
        ///影像瓦片文件显示的最小和最大级数
        int m_nMinLevel, m_nMaxLevel;
        ///是否有效
        bool m_bIsValid;
        ///横向的瓦片数量
        int m_nNumTilesWide;
        ///纵向的瓦片数量
        int m_nNumTilesHigh;
    };

    /**
    * @class GisService
    * @brief Gis服务的接口
    * @note Gis服务的接口,可以调用该Gis的瓦片等信息，读取配置文件的信息，构建URL
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CGisService
    {
    public:

        /**  
        * @brief 构造函数
        * @note 默认构造函数
        * @return 无
        */
        CGisService(void);

        /**  
        * @brief 构造函数
        * @note 带有参数的构造函数  
        * @param bIsValid [in] 是否初始化成功
        * @param uriUri [in] 配置文件的uri
        * @param pProfile [in] 本Gis服务的profile
        * @param strErrorMsg [in] 错误信息
        * @param plistLayers [in] Gis服务的图层列表
        * @param bTiled [in] 是否初始化了瓦片信息
        * @param tileInfo [in] 存储瓦片信息
        * @param strType [in] Gis服务的瓦片的存储结构（行或者列或者其他）
        * @return 无
        */
        CGisService( bool bIsValid, URI uriUri, const CVBF_Profile * pProfile, std::string strErrorMsg,
            bool bTiled, CTileInfo tileInfo, std::string strType );

        /**  
        * @brief 构造函数
        * @note 拷贝构造函数  
        * @param rhs [in] 类的对象引用,用于初始化类对象
        * @return 无
        */
        CGisService( const CGisService& rhs );

        /**  
        * @brief 赋值函数
        * @note 赋值函数  
        * @param rhs [in] 类的对象引用，用来初始化类中变量的值
        * @return 无
        */
        CGisService & operator= (const CGisService &other);

        /**  
        * @brief 初始化函数
        * @note 初始化该Gis服务，根据给的URI中的配置文件，将需要用到的配置读取出来并保存
        * @param uri [in] 传入要读取的配置文件的uri
        * @param options [in] 
        * @return bool 返回是否读取配置信息是否完成
        */
        virtual bool Init( const URI& uri, const osgDB::Options* options =0L );

        /**  
          * @brief 获取文件的URL
          * @note 通过传入的Key以及文件的整体路径，通过本类的Type匹配出适合的URL
          * @param key [in]
          * @param full [in] 文件夹的路径
          * @return std::string 返回拼接后的URL
        */
        virtual std::string ConstructUrl(const CVBF_TileKey& key, const CHgSharpOptions& options ) const;
        
        /**  
        * @brief 检测图片是否有效
        * @note 图片若处在边界处，四个角会至少有一个角有黑色，或图片全黑，为无效
        * @return 无效则为true, 否则为false
        */
        virtual bool CheckBlackImage(osg::Image* image);
        
        /**  
        * @note 返回该类是否初始化成功
        */
        virtual bool IsValid() const;

        /**
        * @note 返回在读取配置文件时，瓦片的信息是否读取成功
        */
        virtual bool IsTiled() const;

        /**  
        * @note set功能函数，当出错时设置错误信息  
        */
        bool SetError( const std::string& );

        /**
        * @note 如果该类初始化失败，则返回错误信息
        */
        virtual const std::string& GetError() const;

        /**  
        * @note 返回该gis服务相关的profile信息
        */
        virtual const CVBF_Profile* GetProfile() const;

        /**  
        * @note 返回该gis服务的瓦片的信息并不可被修改
        */
        virtual const CTileInfo& GetTileInfo() const;

        /**  
        * @note 返回该gis服务的组织结构类型
        */
        virtual std::string GetTileType() const;

        /**  
        * @note 返回是否检测图片
        */
        virtual std::string GetStrCheck() const; 
    private:
        ///是否初始化成功
        bool m_bIsValid;
        ///保存传入的配置文件的uri
        URI m_uriUri;
        ///本Gis服务的profile
        ref_ptr<const CVBF_Profile> m_rpProfile;
        ///错误信息
        std::string m_strErrorMsg;
        ///是否初始化了瓦片信息
        bool m_bTiled;
        ///存储瓦片信息
        CTileInfo m_tileInfo;
        ///该Gis服务的瓦片的存储结构（行或者列或者其他）
        std::string m_strType;
        ///判断是否对图片进行检测，检测的目的是如果有全黑的图片，则认为无效。一般不需要检测
        std::string m_strCheck;
    };
}

#endif
