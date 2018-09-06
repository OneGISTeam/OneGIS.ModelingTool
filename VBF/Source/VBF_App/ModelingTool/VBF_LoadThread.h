#ifndef __VBF_LOAD_THREAD_H__
#define __VBF_LOAD_THREAD_H__


#include <vector>
#include <list>
#include <VBF_Macros.h>
#include <Types/Vec3d>
#include <OpenThreads/Thread>
#include <stdio.h>
#include <string.h>



// 设置结构体对齐方式：1字节对齐
#include <pshpack1.h>

//--------------------------------------------------------------------
// 杜莹添加(2010-01-04)：用于获取态势数据
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

// 注意：取消字节对齐的设置
#include <poppack.h>


class CVBF_LoadThread : public OpenThreads::Thread
{
public:
    CVBF_LoadThread();

    // 获取下一个读取的数据
    bool GetNextData(VBF_SITUDATA& data);

private:
    virtual void run();

    // 读取态势文件中的下一个模型数据
    void LoadNextMark();

private:
    bool                    m_bDone;  // 线程是否已经终止
    OpenThreads::Mutex      m_mutex;

    typedef std::list<VBF_SITUDATA> CSubList;

    // 态势文件
    FILE*                   m_fp;           // 态势数据文件
    int                     m_nSizeSub;     // 每个分段数据的模型个数
    std::list< CSubList >   m_vDataPrev;    // 以前读取的分段数据
    CSubList                m_vDataCurr;    // 当前正在读取的分段数据
};


#endif
