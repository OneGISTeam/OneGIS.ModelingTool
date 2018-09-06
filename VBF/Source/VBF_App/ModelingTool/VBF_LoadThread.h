#ifndef __VBF_LOAD_THREAD_H__
#define __VBF_LOAD_THREAD_H__


#include <vector>
#include <list>
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <OpenThreads/Thread>
#include <stdio.h>
#include <string.h>



// ���ýṹ����뷽ʽ��1�ֽڶ���
#include <pshpack1.h>

//--------------------------------------------------------------------
// ��Ө���(2010-01-04)�����ڻ�ȡ̬������
//--------------------------------------------------------------------
typedef struct _tagVBFSituData
{
    char			szLayerName[64];
    char			szMarkID[64];
    char			szMarkCode[64];
    char			szLabel[64];
    bool			bVisible;
    UINT			nATT;
    osg::Vec3d		vPosGeo;
    float			fRotateX;
    float			fRotateY;
    float			fRotateZ;

    _tagVBFSituData()
    {
        szLayerName[0]  = '\0';
        szMarkID[0]		= '\0';
        szMarkCode[0]	= '\0';
        szLabel[0]		= '\0';
        bVisible		= false;
        nATT			= 1;
        vPosGeo			= osg::Vec3d(0,0,0);
        fRotateX		= 0.0f;
        fRotateY		= 0.0f;
        fRotateZ		= 0.0f;
    }

    _tagVBFSituData& operator=(const _tagVBFSituData& src)
    {
        strcpy(szLayerName, src.szLayerName);
        strcpy(szMarkID,    src.szMarkID);
        strcpy(szMarkCode,  src.szMarkCode);
        strcpy(szLabel,     src.szLabel);

        bVisible	= src.bVisible;
        nATT		= src.nATT;
        vPosGeo		= src.vPosGeo;
        fRotateX	= src.fRotateX;
        fRotateY	= src.fRotateY;
        fRotateZ	= src.fRotateZ;

        return *this;
    }

    void Read(FILE* fp)
    {
        fread(szLayerName,  sizeof(szLayerName),	1, fp);
        fread(szMarkID,		sizeof(szMarkID),		1, fp);
        fread(szMarkCode,	sizeof(szMarkCode),		1, fp);
        fread(szLabel,		sizeof(szLabel),		1, fp);
        unsigned int bVisibleT;

        fread(&bVisibleT,	sizeof(unsigned int),	1, fp);
        bVisible = bVisibleT;

        fread(&nATT,		sizeof(UINT),			1, fp);
        fread(&vPosGeo,		sizeof(osg::Vec3d),		1, fp);
        fread(&fRotateX,	sizeof(float),			1, fp);
        fread(&fRotateY,	sizeof(float),			1, fp);
        fread(&fRotateZ,	sizeof(float),			1, fp);
    }

}VBF_SITUDATA;

// ע�⣺ȡ���ֽڶ��������
#include <poppack.h>


class CVBF_LoadThread : public OpenThreads::Thread
{
public:
    CVBF_LoadThread();

    // ��ȡ��һ����ȡ������
    bool GetNextData(VBF_SITUDATA& data);

private:
    virtual void run();

    // ��ȡ̬���ļ��е���һ��ģ������
    void LoadNextMark();

private:
    bool                    m_bDone;  // �߳��Ƿ��Ѿ���ֹ
    OpenThreads::Mutex      m_mutex;

    typedef std::list<VBF_SITUDATA> CSubList;

    // ̬���ļ�
    FILE*                   m_fp;           // ̬�������ļ�
    int                     m_nSizeSub;     // ÿ���ֶ����ݵ�ģ�͸���
    std::list< CSubList >   m_vDataPrev;    // ��ǰ��ȡ�ķֶ�����
    CSubList                m_vDataCurr;    // ��ǰ���ڶ�ȡ�ķֶ�����
};


#endif
