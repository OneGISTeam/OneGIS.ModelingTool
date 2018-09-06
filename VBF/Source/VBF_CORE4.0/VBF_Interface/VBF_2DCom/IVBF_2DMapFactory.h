//***************************************************************************************
// FileName��IVBF_2DMap.h
// Function��
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_2DMAP_FACTORY_H__
#define __IVBF_2DMAP_FACTORY_H__

#include <VBF_2DCom/IVBF_2DMap.h>

// ����������ID��
const char VBF_COMPONENT_2DMAP[]  = "Component: 2DMap";

// ����ģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_2DMAP[]  = "��ά��ͼ�ӿ�";


class IVBF_2DMapFactory
{
protected:
    virtual ~IVBF_2DMapFactory() {}

public:	
    virtual IVBF_2DMap* Create2DMap(std::string sMapName,int nX,int nY,int nWidth,int nHeight,const std::string& sMapFile)=0;
    virtual IVBF_2DMap* Find2DMap(std::string& sMapName)=0;
    virtual void Remove2DMap(std::string& sMapName)=0;
    virtual void RemoveAll2DMap()=0;
};


#endif
