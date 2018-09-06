//***************************************************************************************
// FileName��IVBF_MapLayer.h
// Function��ͼ��
// Author:
// Date:
//***************************************************************************************
#ifndef __IVBF_MAP_LAYER_H__
#define __IVBF_MAP_LAYER_H__

#include <VBF_Base/VBF_Referenced.h>
#include <string>

// ͼ������֪ͨ���ݱ仯
class IVBF_LayerObserver : public CVBF_Referenced
{
public:
    explicit IVBF_LayerObserver(bool threadSafeRefUnref): CVBF_Referenced(threadSafeRefUnref) { }
    virtual ~IVBF_LayerObserver() { }

    virtual void Dirty( )=0;
};

class IVBF_MapLayer : public ::CVBF_Referenced
{
public: 	
    virtual ~IVBF_MapLayer() {}

public:
    // ͼ���Ψһ��ʶ
    virtual int getUID() const = 0;

    // ��ȡͼ����
    virtual const std::string& getName() const  = 0;

    virtual bool getEnabled() const = 0;

    // �Ƿ���ƣ�����Ӧ�ã���ͼ��
    virtual void setVisible( bool value ) = 0;
    virtual bool getVisible() const = 0;

    virtual void Dirty() = 0;

    virtual void AddObserver(IVBF_LayerObserver* pLayerObserver)=0;
    virtual void RemoveObserver(IVBF_LayerObserver* pLayerObserver)=0;

};

#endif





















