//***************************************************************************************
// FileName��IVBF_Map.h
// Function����ͼ
// Author:
// Date:
//***************************************************************************************
#ifndef __IVBF_MAP_H__
#define __IVBF_MAP_H__

#include <VBF_3DMap/VBF_Terrain/IVBF_MapLayer.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>

class IVBF_Map : public ::CVBF_Referenced
{
public:
    IVBF_Map():CVBF_Referenced ( true ) { }
    virtual ~IVBF_Map() {}
public:
    virtual int getNumImageLayers() const=0;// ��ȡӰ��ͼ�������

    virtual IVBF_MapLayer* getImageLayerByName( const std::string& name ) const=0;// ͨ�����ֻ�ȡӰ��ͼ��
    virtual IVBF_MapLayer* getImageLayerByUID( int layerUID ) const=0;// ͨ��ID��ȡӰ��ͼ��
    virtual IVBF_MapLayer* getImageLayerAt( int index ) const=0;// ͨ��������ȡӰ��ͼ��


    virtual int getNumModelLayers() const=0;// ͨ��������ȡģ��ͼ��
    virtual IVBF_MapLayer* getModelLayerByName( const std::string& name ) const=0;// ͨ�����ֻ�ȡģ��ͼ��
    virtual IVBF_MapLayer* getModelLayerByUID( int layerUID ) const=0;// ͨ��ID��ȡģ��ͼ��
    virtual IVBF_MapLayer* getModelLayerAt( int index ) const=0;// ͨ��������ȡģ��ͼ��

    virtual int getNumElevationLayers() const=0;// ͨ��������ȡ�߳�ͼ��
    virtual IVBF_MapLayer* getElevationLayerByName( const std::string& name ) const=0;// ͨ�����ֻ�ȡ�߳�ͼ��
    virtual IVBF_MapLayer* getElevationLayerByUID( int layerUID ) const=0;// ͨ��ID��ȡ�߳�ͼ��
    virtual IVBF_MapLayer* getElevationLayerAt( int index ) const=0;// ͨ��������ȡ�߳�ͼ��

    virtual bool AddModelLayer(const std::string& strFileName)=0;// �������ļ����ģ��ͼ�㣨��earthһ�£�
    virtual void RemoveModelLayer(const std::string& name)=0;
    virtual void AddModelLayers(const CVBF_Config& conf)=0;// �������ļ����ʸ��ͼ�㣨��earthһ�£�
    virtual void AddModelLayer(const CVBF_Config& conf)=0;// �������ļ����ʸ��ͼ�㣨��earthһ�£�

    virtual bool AddImageLayer(const std::string& strFileName)=0;// �������ļ����ͼ��ͼ�㣨��earthһ�£�
    virtual void RemoveImageLayer(const std::string& name)=0;
    virtual void AddImageLayers(const CVBF_Config& conf)=0;// �������ļ����ͼ��ͼ�㣨��earthһ�£�
    virtual void AddImageLayer(const CVBF_Config& conf)=0;// �������ļ����ͼ��ͼ�㣨��earthһ�£�

    virtual bool AddElevationLayer(const std::string& strFileName)=0;// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�
    virtual void RemoveElevationLayer(const std::string& name)=0;
    virtual void AddElevationLayers(const CVBF_Config& conf)=0;// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�
    virtual void AddElevationLayer(const CVBF_Config& conf)=0;// �������ļ���Ӹ߳�ͼ�㣨��earthһ�£�

};

#endif





















