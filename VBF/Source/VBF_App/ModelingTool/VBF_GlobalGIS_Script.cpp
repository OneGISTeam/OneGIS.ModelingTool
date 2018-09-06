#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Display/IVBF_3DDisplay.h>
#include <VBF_Plot/IVBF_3DPlot.h>

#include <VBF_Common/VBF_Utils/VBF_JsonUtils.h>
#include <VBF_Common/VBF_Utils/VBF_Config.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>
#include <VBF_Aux/VBF_MapAux/VBF_EarthMath.h>
#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorAnimationPath.h>
#include <VBF_3DCom/IVBF_3DPerform.h>
#include <VBF_Common/VBF_Math/VBF_TimeConverter.h>

//#include "UWB/IndoorPositioning.h"

#include "VBF_FunctionRegister.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>


#include <VBF_3DCom/IVBF_3DApplication.h>

// Json�ű�
std::string ExecuteScript(IVBF_MainCtrl* pIMainCtrl, std::string jstrScript)
{
    if(pIMainCtrl==NULL) return "";

    IVBF_3DApplication* pI3DApplication = (IVBF_3DApplication*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DAPPLICATION);
    if(NULL==pI3DApplication) return "";

    QTextStream inStream(jstrScript.c_str());
    QString strJstrScript = inStream.readAll();

    return pI3DApplication->ExecuteScript(strJstrScript.toStdString());

}

extern std::string g_sDataPath;

void VBF_ExecuteScriptFile(IVBF_MainCtrl* pIMainCtrl,std::string sFilename)
{
    if(pIMainCtrl==NULL) return; 

    freopen ("CON", "w", stdout);

    QString sFn = g_sDataPath.c_str();
    sFn += "/Script/";
    sFn += sFilename.c_str();

    QFile file(sFn);
    if (!file.open(QFile::ReadOnly))
    {
        OSG_NOTICE << "json�ļ���ʧ�ܣ�" << sFn.toStdString() << std::endl;
        return;
    }
    QTextStream inStream(&file);
    QString jstrScript = inStream.readAll();
    file.close();

    ExecuteScript(pIMainCtrl, jstrScript.toStdString());
}


//  ���ԣ�Common����е�ģ��




// ������ԣ�����β��
void Test_ExecuteScriptAddAttrTrailLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddAttrTrailLine.json");
}
// ������ԣ�����ϵͳ
void Test_ExecuteScriptAddAttrCoordSys(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddAttrCoordSys.json");
}

// ��ӹ��̣���·���ƶ�
void Test_ExecuteScriptAddProcessMove(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddProcessMove.json");
}
void Test_ExecuteScriptDeleteProcessMove(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/DeleteProcessMove.json");
}
void Test_ExecuteScriptAddProcessMoveCurrent(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddProcessMoveCurrent.json");
}
void Test_ExecuteScriptAddProcessMoveSix(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddProcessMoveSix.json");
}
void Test_ExecuteScriptAddProcessExplosion(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddProcessExplosion.json");
}

// ���ԣ�Shape����е�ģ��
// ���Shapeģ�ͣ�Բ��
void Test_ExecuteScriptAddShapeCylinder(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCylinder.json");
}
// ���Shapeģ�ͣ�Բ׶
void Test_ExecuteScriptAddShapeCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCone.json");
}
// ���Shapeģ�ͣ�������
void Test_ExecuteScriptAddShapeCube(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCube.json");
}
// ���Shapeģ�ͣ�����
void Test_ExecuteScriptAddShapeDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeDome.json");
}
// ���Shapeģ�ͣ���������
void Test_ExecuteScriptAddShapeDomeAccordWithEarth(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeDomeAccordWithEarth.json");
}
// ���Shapeģ�ͣ������Ӿ���
void Test_ExecuteScriptAddShapeFrustumDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeFrustumDome.json");
}
// ���Shapeģ�ͣ�ƽ���Ӿ���
void Test_ExecuteScriptAddShapeFrustumFlat(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeFrustumFlat.json");
}
// ���Shapeģ�ͣ���ά��
void Test_ExecuteScriptAddShapePoint2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapePoint2D.json");
}
// ���Shapeģ�ͣ���ά��
void Test_ExecuteScriptAddShapePoint3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapePoint3D.json");
}
// ���Shapeģ�ͣ���ת��
void Test_ExecuteScriptAddShapeRevoSurface(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRevoSurface.json");
}
// ���Shapeģ�ͣ�����
void Test_ExecuteScriptAddShapeSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeSector.json");
}
// ���Shapeģ�ͣ�����
void Test_ExecuteScriptAddShapeSphere(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeSphere.json");
}
// ���Shapeģ�ͣ�������
void Test_ExecuteScriptAddShapeHemiSphere(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeHemiSphere.json");
}
// ���Shapeģ�ͣ�������
void Test_ExecuteScriptAddShapeTetrahedron(IVBF_MainCtrl* pIMainCtrl) 
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeTetrahedron.json");
}
// ���Shapeģ�ͣ�Բ��
void Test_ExecuteScriptAddShapeTorus(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeTorus.json");
}
// ���Shapeģ�ͣ���ά��Բ
void Test_ExecuteScriptAddShapeEllipse2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeEllipse2D.json");
}
// ���Shapeģ�ͣ���ά��Բ
void Test_ExecuteScriptAddShapeEllipse3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeEllipse3D.json");
}
// ���Shapeģ�ͣ���άԲ��
void Test_ExecuteScriptAddShapeArc2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeArc2D.json");
}
// ���Shapeģ�ͣ���άԲ��
void Test_ExecuteScriptAddShapeArc3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeArc3D.json");
}
// ���Shapeģ�ͣ���ά����
void Test_ExecuteScriptAddShapeRect2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRect2D.json");
}
// ���Shapeģ�ͣ���ά����
void Test_ExecuteScriptAddShapeRect3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRect3D.json");
}

// ���ԣ�Shape����е�����
// ���Shape���ԣ���̬��
void Test_ExecuteScriptAddAttrSphereAttitude(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddAttrSphereAttitude.json");
}
// �޸�Shape���ԣ���̬��
void Test_ExecuteScriptUpdateAttrSphereAttitude(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/UpdateAttrSphereAttitude.json");
}
// ���Shape���ԣ��������
void Test_ExecuteScriptAddAttrIntersect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddAttrIntersect.json");
}
// ���Shape���ԣ���ʼ��
void Test_ExecuteScriptUpdateAttrIntersectBegin(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/UpdateAttrIntersectBegin.json");
}
void Test_ExecuteScriptUpdateAttrIntersectEnd(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/UpdateAttrIntersectEnd.json");
}
void Test_ExecuteScriptUpdateAttrIntersectClear(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/UpdateAttrIntersectClear.json");
}

// ���ԣ�ElecMag����е�ģ��
// ��ӵ��ģ�ͣ�����
void Test_ExecuteScriptAddBeam(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddBeam.json");
}
// ��ӵ��ģ�ͣ�������
void Test_ExecuteScriptAddLinkLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkLine.json");
}
// ��ӵ��ģ�ͣ���ά������
void Test_ExecuteScriptAddLink2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLink2D.json");
}
// ��ӵ��ģ�ͣ�˫���ά������
void Test_ExecuteScriptAddLink2DDualWork(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLink2DDualWork.json");
}
// ��ӵ��ģ�ͣ�����������
void Test_ExecuteScriptAddLinkMeteor(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkMeteor.json");
}
// ��ӵ��ģ�ͣ���״����
void Test_ExecuteScriptAddLinkRing(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkRing.json");
}
// ��ӵ��ģ�ͣ��״ﲨ���飨Բ׶�Σ�
void Test_ExecuteScriptAddRadarLobeCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddRadarLobeCone.json");
}
// ��ӵ��ģ�ͣ�Ŀָ�״�
void Test_ExecuteScriptAddSensorAC(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorAC.json");
}
// ��ӵ��ģ�ͣ�Բ׶�δ�����
void Test_ExecuteScriptAddSensorCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorCone.json");
}
// ��ӵ��ģ�ͣ������δ�����
void Test_ExecuteScriptAddSensorDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorDome.json");
}
// ��ӵ��ģ�ͣ������״�(Բ����)
void Test_ExecuteScriptAddSensorFKDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorFKDome.json");
}
// ��ӵ��ģ�ͣ������״�(����)
void Test_ExecuteScriptAddSensorFKRect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorFKRect.json");
}
// ��ӵ��ģ�ͣ������״�
void Test_ExecuteScriptAddSensorInfrared(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorInfrared.json");
}
// ��ӵ��ģ�ͣ�������״�
void Test_ExecuteScriptAddSensorPA(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPA.json");
}
// ��ӵ��ģ�ͣ�P���δ�����
void Test_ExecuteScriptAddSensorPDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPDome.json");
}

// ��ӵ��ģ�ͣ�P���δ����������Σ�
void Test_ExecuteScriptAddSensorPSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPSector.json");
}
// ��ӵ��ģ�ͣ�Ԥ�����״�
void Test_ExecuteScriptAddSensorRadarAEW(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarAEW.json");
}

// ��ӵ��ģ�ͣ������״�
void Test_ExecuteScriptAddSensorRadarGround(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarGround.json");
}
// ��ӵ��ģ�ͣ��״����
void Test_ExecuteScriptAddSensorRadarJammed(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarJammed.json");
}
// ��ӵ��ģ�ͣ��첨�״�
void Test_ExecuteScriptAddSensorRadarSky(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarSky.json");
}
// ��ӵ��ģ�ͣ��첨�״�
void Test_ExecuteScriptAddSensorRadarSkyEx(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarSkyEx.json");
}
// ��ӵ��ģ�ͣ����δ�����
void Test_ExecuteScriptAddSensorRect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRect.json");
}
// ��ӵ��ģ�ͣ����δ�����
void Test_ExecuteScriptAddSensorSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorSector.json");
}
// ��ӵ��ģ�ͣ�������
void Test_ExecuteScriptAddThreatWave(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddThreatWave.json");
}
// ��ӵ��ģ�ͣ�̽��
void Test_ExecuteScriptAddSensorDetectObjs(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorDetectObjs.json");
}
// ɾ��̽������
void Test_ExecuteScriptDeleteAttrDetect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/DeleteAttrDetect.json");
}
// ���ԣ�ElecMag����е�����
void Test_ExecuteScriptAddAttrPowerMap(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddAttrPowerMap.json");
}
void Test_ExecuteScriptAddAttrDetect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddAttrDetect.json");
}

// ���ԣ�Aviation����е�ģ��
// ��Ӻ���ģ�ͣ�����
void Test_ExecuteScriptAddAirLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirLine.json");
}
// ��Ӻ���ģ�ͣ����ο���
void Test_ExecuteScriptAddAirSpaceArc(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpaceArc.json");
}
// ��Ӻ���ģ�ͣ�Բ�ο���
void Test_ExecuteScriptAddAirSpaceCircle(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpaceCircle.json");
}
// ��Ӻ���ģ�ͣ����Ϳ���
void Test_ExecuteScriptAddAirSpacePolyline(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpacePolyline.json");
}
// ��Ӻ���ģ�ͣ�������
void Test_ExecuteScriptAddChaff(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddChaff.json");
}
//��Ӻ���ģ�ͣ������
void Test_ExecuteScriptAddEquatorPlane(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddEquatorPlane.json");
}
// ��Ӻ���ģ�ͣ���������
void Test_ExecuteScriptAddGeoEllip(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddGeoEllip.json");
}
// ��Ӻ���ģ�ͣ������Ӱ
void Test_ExecuteScriptAddSphereLight(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddSphereLight.json");
}


void Test_ExecuteScriptAddJBPoint_DKY(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "JB_DKY/AddJBPoint.json");
}
void Test_ExecuteScriptAddJBPoint_DTIS(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "JB_DTIS/AddJBPoint.json");
}
void Test_ExecuteScriptAddJBArrowSingle_DTIS(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "JB_DTIS/AddJBArrowSingle.json");
}

// �������
void Test_ExecuteScriptCalDist(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Calculate/CalDist.json");
}

// �ű�ע�ắ�� 

VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrTrailLine)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrCoordSys)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddProcessMove)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptDeleteProcessMove)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddProcessMoveCurrent)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddProcessMoveSix)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddProcessExplosion)

VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeCylinder)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeCone)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeCube)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeDome)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeDomeAccordWithEarth)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeFrustumDome)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeFrustumFlat) 
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapePoint2D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapePoint3D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeRevoSurface)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeSector)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeSphere)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeHemiSphere)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeTetrahedron)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeTorus)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeEllipse2D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeEllipse3D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeArc2D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeArc3D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeRect2D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddShapeRect3D)

VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrSphereAttitude) 
VBF_REGISTER_FUNCTION(Test_ExecuteScriptUpdateAttrSphereAttitude) 
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrIntersect)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptUpdateAttrIntersectBegin)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptUpdateAttrIntersectEnd)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptUpdateAttrIntersectClear)

VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddBeam)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddLinkLine)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddLink2D)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddLink2DDualWork)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddLinkMeteor)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddLinkRing)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddRadarLobeCone)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorAC)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorCone)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorDome)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorFKDome)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorFKRect)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorPA)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorInfrared)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorPDome)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorPSector)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRadarAEW)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRadarGround)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRadarJammed)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRadarSky)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRadarSkyEx)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorRect)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorSector)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddThreatWave)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSensorDetectObjs)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptDeleteAttrDetect)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrPowerMap)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAttrDetect)

VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAirLine)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAirSpaceArc)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAirSpaceCircle)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddAirSpacePolyline)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddChaff)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddEquatorPlane)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddGeoEllip)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddSphereLight)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddJBPoint_DKY)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddJBPoint_DTIS)
VBF_REGISTER_FUNCTION(Test_ExecuteScriptAddJBArrowSingle_DTIS)

VBF_REGISTER_FUNCTION(Test_ExecuteScriptCalDist)
