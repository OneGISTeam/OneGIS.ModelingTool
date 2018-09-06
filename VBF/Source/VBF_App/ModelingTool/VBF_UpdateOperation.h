//***************************************************************************************
// FileName��VBF_UpdateOperation.h
// Function��Ӧ�ó���ʹ�õĻص������ڲ���ģ�Ͷ�����
// Author:
// Date:     2013-11-14
//***************************************************************************************

#ifndef __VBF_UPDATE_OPERATION_H__
#define __VBF_UPDATE_OPERATION_H__

#include <VBF_Engine/VBF_SceneGraph/OperationThread>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Plot/IVBF_3DPlot.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Base/VBF_Timer.h>
#include <VBF_Common/VBF_Math/VBF_DE405.h>
#include <VBF_Common/VBF_Math/IVBF_SrsDefine.h>
#include <VBF_OS.h>

class CVBF_LoadThread;
class IVBF_MarkModelMesh;
class IVBF_MarkModelRaster;

class VBF_DLL_LOCAL CVBF_UpdateOperation : public osg::Operation
{
public:
    CVBF_UpdateOperation(const std::string& name, IVBF_3DMainCtrl* p3DMainCtrl);
    virtual ~CVBF_UpdateOperation();

    virtual void operator()(osg::CVBF_Object* pObject);

    // ɾ������ģ��
    void Clear();

private:

    IVBF_MarkModelMesh*   CreateMarkMesh(const std::string& strMarkID, std::string strModelFileName);
    IVBF_MarkModelRaster* CreateMarkRaster(const std::string& strMarkID);

    void UpdateSituMark();

private:
    IVBF_3DMainCtrl*        m_pI3DMainCtrl;
    IVBF_3DPlot*            m_pI3DPlot;
    CVBF_LoadThread*        m_pThread;

    // ��̬���������ڵı�ͼ�ĵ�
    observer_ptr<IVBF_3DPlotDoc>    m_pIDoc;

    // ��ʱ��
    CVBF_Timer              m_Timer;
    double                  m_dDeltaTime;   // ��ȡһ�����ݵ�ʱ��������λ���룩

    // ��¼����ʱ��
    CVBF_Timer              m_TimerSim;
};


#include <queue>

class CVBF_StepOperation : public osg::Operation
{
public:
    CVBF_StepOperation(const std::string& name, IVBF_MarkModelPoint* pIMark, const std::vector<osg::Vec3d>& vGeo, double dTimeInterval)
        : osg::Operation(name, true), m_pIMark(pIMark), m_dTimeInterval(dTimeInterval)
    {
        for(unsigned int i=0; i<vGeo.size(); i++)
        {
            m_qGeo.push( vGeo[i] );
        }

        // ��ʼ��ʱ
        m_Timer.setStartTick();
    }

    virtual ~CVBF_StepOperation() {}

    virtual void operator()(osg::CVBF_Object* pObject)
    {
        // ÿ��������ȡһ������
        double dDeltaTime = m_Timer.time_s();
        if(dDeltaTime >= m_dTimeInterval)
        {
            if(!m_qGeo.empty())
            {
                if(m_pIMark.valid()) m_pIMark->StepGeoPos( m_qGeo.front(), 0, 0, 0 );
                m_qGeo.pop();
            }

            // ���¿�ʼ��ʱ
            m_Timer.setStartTick();
        }
    }

private:
    observer_ptr<IVBF_MarkModelPoint>   m_pIMark;   // �غ����˶���ģ��

    std::queue<osg::Vec3d>      m_qGeo;             // Ԥ������
    double                      m_dTimeInterval;    // ÿ��������ȡһ������
    CVBF_Timer                  m_Timer;            // ��ʱ��
};

// ���ڲ��Դ�����̽��Ļص����Ա����������任�йص����ݣ�����ͨ�ߡ�Ŀ��̽��ȣ�
class CVBF_DetectOperation : public osg::Operation
{
public:
    CVBF_DetectOperation(const std::string& name) :
        osg::Operation(name, true)
    {
        m_vOffsetSensor = osg::Vec3d(0, 0, 0);
        m_vOffsetDetect = osg::Vec3d(0, 0, 0);
    }

    // ����/���/ɾ��ģ��
    void SetSensorMark(IVBF_MarkModel* pIMark)  { m_pISensorMark = pIMark; }            // ���������ڵ�ģ��
    void AddDetectMark(IVBF_MarkModel* pIMark)  { m_vDetectMarks.push_back(pIMark); }   // ��̽���ģ��
    void ClearDetectMarks()                     { m_vDetectMarks.clear(); }             // ������б�̽���ģ��

    // ����ģ��ÿ֡���˶�ƫ����
    void SetSensorMarkOffset(osg::Vec3d vOffset)    { m_vOffsetSensor = vOffset; }
    void SetDetectMarkOffset(osg::Vec3d vOffset)    { m_vOffsetDetect = vOffset; }

    // ÿ֡����
    virtual void operator()(osg::CVBF_Object* pObject)
    {
        // ���´��������ڵ�ģ��
        if(m_pISensorMark.valid())
        {
            m_pISensorMark->SetGeoPos(m_pISensorMark->GetGeoPos() + m_vOffsetSensor);
        }

        // ���±�̽���ģ��
        for(unsigned int i=0; i<m_vDetectMarks.size(); i++)
        {
            observer_ptr<IVBF_MarkModel>& pIDetectMark = m_vDetectMarks[i];
            if(!pIDetectMark.valid()) continue;

            osg::Vec3d vGeoPos = pIDetectMark->GetGeoPos() + m_vOffsetDetect;

            if(pIDetectMark->IsPointMarkModel())
            {
                IVBF_MarkModelPoint* pIMarkPoint = (IVBF_MarkModelPoint*)pIDetectMark.get();
                pIMarkPoint->SetGeoPos(vGeoPos);
            }
        }
    }

private:
    observer_ptr<IVBF_MarkModel>    m_pISensorMark;  // ���������ڵ�ģ��
    std::vector< observer_ptr<IVBF_MarkModel> > m_vDetectMarks; // ���б�̽���ģ��

    // ÿ֡�˶�ƫ����
    osg::Vec3d          m_vOffsetSensor;
    osg::Vec3d          m_vOffsetDetect;
};

#include <VBF_3DCom/IVBF_SpaceEnv.h>
#include <VBF_3DCom/IVBF_SpaceObject.h>
#include <VBF_3DCom/IVBF_3DSky.h>
#include <VBF_Common/VBF_Math/VBF_TimeConverter.h>

class CVBF_UpdateEpochOperation : public osg::Operation
{
public:
    CVBF_UpdateEpochOperation(IVBF_MainCtrl* pIMainCtrl): osg::Operation("Update Epoch", true)
    {
        m_bEnable = true;
        m_eWorldSRS = ECEF;
        m_matIdentity.identity();

        if(pIMainCtrl==NULL) return;
        IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
        if(pI3DMainCtrl==NULL) return;

        m_pISpaceEnv = (IVBF_SpaceEnv*)pIMainCtrl->QueryInterface(VBF_INTERFACE_SPACEENV);
        m_pISky = (IVBF_3DSky*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DSKY, NULL);
        m_opSpaceObjectManager = (IVBF_SpaceObjectManager*)pIMainCtrl->QueryInterface(VBF_INTERFACE_SPACEOBJECT);
        m_opI3DPlot = (IVBF_3DPlot*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);

        if(m_pISpaceEnv) m_pISpaceEnv->SetEpoch(2012,1,1,12,0,0);

        m_pEarthNode = dynamic_cast<MatrixTransform*>(pI3DMainCtrl->GetEarthNode());

    }
    virtual ~CVBF_UpdateEpochOperation(){}

    virtual void operator()(osg::CVBF_Object* pObject)
    {
        if(m_bEnable==false) return;

        // ��������ʱ��
        IVBF_SimulationTimer* pISimulationTimer = VBF_GetSimulationTimer();
        double dEpochUTC = pISimulationTimer->GetDDayTimeCurrent();
        if(m_pISpaceEnv) m_pISpaceEnv->SetEpoch(dEpochUTC);

        if(m_pISky)
        {
            int year,month,day,hour,minute;
            double second;
            CVF_TimeConverter::convertJDtoDT(dEpochUTC,year,month,day,hour,minute,second);
            m_pISky->SetDateTime(year, month, day, hour+ minute/60.0+ second/3600.0);
        }

        if(m_opSpaceObjectManager.valid())m_opSpaceObjectManager->UpdateTimer(dEpochUTC);

        if(m_pISpaceEnv==false) return;

        // ������ת���󣨴Ӿֲ�����ϵ�������õ���ECEF���ռ�Ŀ���õ��ǵ���J2000���任����������ϵ��
        const osg::Matrix& matRotEcef2J2000 = m_pISpaceEnv->getEarthRotation();
        osg::Matrix matRotJ20002Ecef = Matrix::inverse(matRotEcef2J2000);

        if(m_eWorldSRS==ECEF)
        {
            if(m_pEarthNode) m_pEarthNode->setMatrix(m_matIdentity);
            if(m_pISpaceEnv) m_pISpaceEnv->setMatrix(matRotJ20002Ecef);
        }
        else if(m_eWorldSRS==J2000)
        {
            if(m_pEarthNode) m_pEarthNode->setMatrix(matRotEcef2J2000);
            if(m_pISpaceEnv) m_pISpaceEnv->setMatrix(m_matIdentity);
        }
        else if(m_eWorldSRS==MCF)
        {
            const osg::Matrix& matRotMcf2J2000 = m_pISpaceEnv->getRotation(Space::Moon);
            osg::Matrix matRotJ20002Mcf = Matrix::inverse(matRotMcf2J2000);

            if(m_pEarthNode) m_pEarthNode->setMatrix(matRotEcef2J2000*matRotJ20002Mcf);
            if(m_pISpaceEnv) m_pISpaceEnv->setMatrix(matRotJ20002Mcf);
        }
        else if(m_eWorldSRS==ECEM)
        {
            osg::Matrix matRotEcem2J2000 = VBF_J2000toEarthMoon(dEpochUTC-2400000.5);
            osg::Matrix matRotJ20002Ecem = Matrix::inverse(matRotEcem2J2000);

            if(m_pEarthNode) m_pEarthNode->setMatrix(matRotEcef2J2000*matRotJ20002Ecem);
            if(m_pISpaceEnv) m_pISpaceEnv->setMatrix(matRotJ20002Ecem);
        }

        if(m_opI3DPlot.valid()) m_opI3DPlot->UpdateEciMatrix(dEpochUTC,matRotJ20002Ecef);// ���ͼ�����ڵ������й�

    }

    void Enable(bool bEnable) { m_bEnable= bEnable; }
    void SetWorldSys(EVBF_SRS eSrs) { m_eWorldSRS = eSrs; }

private:
    IVBF_SpaceEnv* m_pISpaceEnv;
    observer_ptr<IVBF_SpaceObjectManager> m_opSpaceObjectManager;
    MatrixTransform* m_pEarthNode;
    observer_ptr<IVBF_3DPlot> m_opI3DPlot;
    IVBF_3DSky* m_pISky;

    bool m_bEnable;
    EVBF_SRS m_eWorldSRS;
    Matrix m_matIdentity;

};
#endif
