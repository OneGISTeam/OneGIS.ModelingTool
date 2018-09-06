/**************************************************************************************************
* @file HgSharpTileSource.h
* @note ��дӰ���ļ�
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
    * @brief ��дӰ��Ļ���
    * @note �̳���TileSource���������һ��Ӱ��Ķ�д�����
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CHgSharpTileSource : public CVBFO_SourceTile
    {
    public:
        /**  
        * @brief ���캯��
        * @note �в����Ĺ��캯��
        * @param options [in] ���ڳ�ʼ�������е�options
        * @return ��
        */
        CHgSharpTileSource( const CVBF_OptionsDriverSourceTile& options );

        /**  
        * @brief ��ʼ��
        * @note ��дTileSource�ĳ�ʼ�����������ڴ�Ӱ��������ļ��ж�ȡ������  
        * @param dbOptions [in] �������TerrainLayer�е����������ʼ��ʹ��
        * @return ����ֵ���ڱ���Ƿ��Ѿ���ʼ�����
        */
        virtual Status initialize( const osgDB::Options* dbOptions );
        

        /**  
        * @brief ����Ӱ��
        * @note ���ݴ����TileKye���ֱ�������������С��е���Ϣ����ȡӰ���ļ�����д���෽��
        * @param key [in] ͨ��key�������������С��У��Ӷ�ƴ�ճ�Ӱ���ļ�����λ��
        * @param progress [in/out/inout]
        * @return osg::Image* ���ص���Ӱ���ļ���ָ��
        */
        virtual osg::Image* createImage(const CVBF_TileKey& key, ProgressCallback* progress);

        /**  
        * @brief �����߳�
        * @note ���ݴ������key�����̣߳���д���෽��
        * @param key [in] 
        * @param progress [in]
        * @return HeightField�Ŀ�ָ��
        */
        virtual osg::HeightField* createHeightField( const CVBF_TileKey& key, ProgressCallback* progress);

        /**  
        * @brief ��ȡ��չ��Ϣ
        * @note ��ȡ��Ӱ���ļ��ĸ�ʽ����д���෽��
        * @return std::string ���ص���Ӱ���ļ��ĸ�ʽ
        */
        virtual std::string getExtension() const;
        
        /**  
        * @brief ��ȡTile�����ص�
        * @note ��ȡӰ���Tile�����������ص�
        * @return int���ͣ����ص���Ӱ���Tile�����������ص�
        */
        virtual int getPixelsPerTile() const;

    protected:
        //�洢������
        ref_ptr<osgDB::Options> m_hgDbOptions;
        //���ڴ��HgGis����������Ϣ
        const CHgSharpOptions m_hgOptions;
        //�洢profile��optional���ڴ�������ʼ����ȷ������Ŀ�ܣ�
        CVBF_Optional<CVBF_OptionsProfile> m_profileConf;
        //GisService�������
        CGisService m_hgGisService;
    };
}

#endif //HG_SHARP_TILE_SOURCE_H
