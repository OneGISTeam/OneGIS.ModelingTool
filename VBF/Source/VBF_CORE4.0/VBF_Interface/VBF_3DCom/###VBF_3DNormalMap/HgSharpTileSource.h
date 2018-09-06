/**************************************************************************************************
* @file HgSharpTileSource.h
* @note 读写影像文件
* @author c00005
* @data 2013-12-19
**************************************************************************************************/
#ifndef HG_SHARP_TILE_SOURCE_H
#define HG_SHARP_TILE_SOURCE_H

#include <sstream>
#include <iomanip>
#include <algorithm>

#include <VBF_Base/VBF_Notify.h>
#include <VBF_Common/VBF_Utils/VBF_FileNameUtils.h>
#include <VBF_Common/VBF_Utils/VBF_FileUtils.h>
#include <VBF_3DMap/VBF_Terrain/Registry.h>
#include <VBF_Engine/VBF_SGDB/ReadFile>
#include <VBF_Engine/VBF_SGDB/WriteFile>

#include <VBF_3DMap/VBF_Terrain/VBF_SourceTile.h>
#include <VBF_3DMap/VBF_Terrain/URI.h>
#include <VBF_3DMap/VBF_Terrain/Progress.h>

#include <Types/VBF_Optional.h>

#include "export.h"
#include "GisService.h"
#include "HgSharpOptions.h"


namespace FePlugin
{
    using namespace osgEarth;
    /**
    * @class CHgSharpTileSource
    * @brief 读写影像的基类
    * @note 继承于TileSource，是特殊的一种影像的读写插件。
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CHgSharpTileSource : public CVBFO_SourceTile
    {
    public:
        /**  
        * @brief 构造函数
        * @note 有参数的构造函数
        * @param options [in] 用于初始化本类中的options
        * @return 无
        */
        CHgSharpTileSource( const CVBF_OptionsDriverSourceTile& options );

        /**  
        * @brief 初始化
        * @note 重写TileSource的初始化方法，用于从影像的配置文件中读取配置项  
        * @param dbOptions [in] 传入的是TerrainLayer中的配置项，供初始化使用
        * @return 返回值用于标记是否已经初始化完成
        */
        virtual Status initialize( const osgDB::Options* dbOptions );
        

        /**  
        * @brief 创建影像
        * @note 根据传入的TileKye，分别解析出级数、行、列等信息，读取影像文件，重写父类方法
        * @param key [in] 通过key解析出级数、行、列，从而拼凑出影像文件所在位置
        * @param progress [in/out/inout]
        * @return osg::Image* 返回的是影像文件的指针
        */
        virtual osg::Image* createImage(const CVBF_TileKey& key, ProgressCallback* progress);

        /**  
        * @brief 创建高程
        * @note 根据传入参数key创建高程，重写父类方法
        * @param key [in] 
        * @param progress [in]
        * @return HeightField的空指针
        */
        virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, ProgressCallback* progress);

        /**  
        * @brief 获取扩展信息
        * @note 获取到影像文件的格式，重写父类方法
        * @return std::string 返回的是影像文件的格式
        */
        virtual std::string getExtension() const;
        
        /**  
        * @brief 获取Tile的像素点
        * @note 获取影像的Tile所包含的像素点
        * @return int类型，返回的是影像的Tile所包含的像素点
        */
        virtual int getPixelsPerTile() const;

    protected:
        //存储配置项
        ref_ptr<osgDB::Options> m_hgDbOptions;
        //用于存放HgGis的配置项信息
        const CHgSharpOptions m_hgOptions;
        //存储profile（optional用于处理对象初始化不确定问题的框架）
        CVBF_Optional<CVBF_OptionsProfile> m_profileConf;
        //GisService的类对象
        CGisService m_hgGisService;
    };
}

#endif //HG_SHARP_TILE_SOURCE_H
