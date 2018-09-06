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

// Json脚本
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
        OSG_NOTICE << "json文件打开失败：" << sFn.toStdString() << std::endl;
        return;
    }
    QTextStream inStream(&file);
    QString jstrScript = inStream.readAll();
    file.close();

    ExecuteScript(pIMainCtrl, jstrScript.toStdString());
}


//  测试：Common组件中的模型




// 添加属性：飞行尾迹
void Test_ExecuteScriptAddAttrTrailLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddAttrTrailLine.json");
}
// 添加属性：坐标系统
void Test_ExecuteScriptAddAttrCoordSys(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Common/AddAttrCoordSys.json");
}

// 添加过程：按路径移动
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

// 测试：Shape组件中的模型
// 添加Shape模型：圆柱
void Test_ExecuteScriptAddShapeCylinder(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCylinder.json");
}
// 添加Shape模型：圆锥
void Test_ExecuteScriptAddShapeCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCone.json");
}
// 添加Shape模型：立方体
void Test_ExecuteScriptAddShapeCube(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeCube.json");
}
// 添加Shape模型：球面
void Test_ExecuteScriptAddShapeDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeDome.json");
}
// 添加Shape模型：地心球面
void Test_ExecuteScriptAddShapeDomeAccordWithEarth(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeDomeAccordWithEarth.json");
}
// 添加Shape模型：弧面视景体
void Test_ExecuteScriptAddShapeFrustumDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeFrustumDome.json");
}
// 添加Shape模型：平面视景体
void Test_ExecuteScriptAddShapeFrustumFlat(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeFrustumFlat.json");
}
// 添加Shape模型：二维点
void Test_ExecuteScriptAddShapePoint2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapePoint2D.json");
}
// 添加Shape模型：三维点
void Test_ExecuteScriptAddShapePoint3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapePoint3D.json");
}
// 添加Shape模型：回转面
void Test_ExecuteScriptAddShapeRevoSurface(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRevoSurface.json");
}
// 添加Shape模型：扇面
void Test_ExecuteScriptAddShapeSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeSector.json");
}
// 添加Shape模型：球面
void Test_ExecuteScriptAddShapeSphere(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeSphere.json");
}
// 添加Shape模型：半球面
void Test_ExecuteScriptAddShapeHemiSphere(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeHemiSphere.json");
}
// 添加Shape模型：四面体
void Test_ExecuteScriptAddShapeTetrahedron(IVBF_MainCtrl* pIMainCtrl) 
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeTetrahedron.json");
}
// 添加Shape模型：圆环
void Test_ExecuteScriptAddShapeTorus(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeTorus.json");
}
// 添加Shape模型：二维椭圆
void Test_ExecuteScriptAddShapeEllipse2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeEllipse2D.json");
}
// 添加Shape模型：三维椭圆
void Test_ExecuteScriptAddShapeEllipse3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeEllipse3D.json");
}
// 添加Shape模型：二维圆弧
void Test_ExecuteScriptAddShapeArc2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeArc2D.json");
}
// 添加Shape模型：三维圆弧
void Test_ExecuteScriptAddShapeArc3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeArc3D.json");
}
// 添加Shape模型：二维矩形
void Test_ExecuteScriptAddShapeRect2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRect2D.json");
}
// 添加Shape模型：三维矩形
void Test_ExecuteScriptAddShapeRect3D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddShapeRect3D.json");
}

// 测试：Shape组件中的属性
// 添加Shape属性：姿态球
void Test_ExecuteScriptAddAttrSphereAttitude(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddAttrSphereAttitude.json");
}
// 修改Shape属性：姿态球
void Test_ExecuteScriptUpdateAttrSphereAttitude(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/UpdateAttrSphereAttitude.json");
}
// 添加Shape属性：与地球求交
void Test_ExecuteScriptAddAttrIntersect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Shape/AddAttrIntersect.json");
}
// 添加Shape属性：开始求交
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

// 测试：ElecMag组件中的模型
// 添加电磁模型：波束
void Test_ExecuteScriptAddBeam(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddBeam.json");
}
// 添加电磁模型：链接线
void Test_ExecuteScriptAddLinkLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkLine.json");
}
// 添加电磁模型：二维链接线
void Test_ExecuteScriptAddLink2D(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLink2D.json");
}
// 添加电磁模型：双向二维链接线
void Test_ExecuteScriptAddLink2DDualWork(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLink2DDualWork.json");
}
// 添加电磁模型：流星线链接
void Test_ExecuteScriptAddLinkMeteor(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkMeteor.json");
}
// 添加电磁模型：环状链接
void Test_ExecuteScriptAddLinkRing(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddLinkRing.json");
}
// 添加电磁模型：雷达波瓣组（圆锥形）
void Test_ExecuteScriptAddRadarLobeCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddRadarLobeCone.json");
}
// 添加电磁模型：目指雷达
void Test_ExecuteScriptAddSensorAC(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorAC.json");
}
// 添加电磁模型：圆锥形传感器
void Test_ExecuteScriptAddSensorCone(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorCone.json");
}
// 添加电磁模型：球面形传感器
void Test_ExecuteScriptAddSensorDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorDome.json");
}
// 添加电磁模型：防空雷达(圆顶形)
void Test_ExecuteScriptAddSensorFKDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorFKDome.json");
}
// 添加电磁模型：防空雷达(矩形)
void Test_ExecuteScriptAddSensorFKRect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorFKRect.json");
}
// 添加电磁模型：红外雷达
void Test_ExecuteScriptAddSensorInfrared(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorInfrared.json");
}
// 添加电磁模型：相控阵雷达
void Test_ExecuteScriptAddSensorPA(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPA.json");
}
// 添加电磁模型：P波段传感器
void Test_ExecuteScriptAddSensorPDome(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPDome.json");
}

// 添加电磁模型：P波段传感器（扇形）
void Test_ExecuteScriptAddSensorPSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorPSector.json");
}
// 添加电磁模型：预警机雷达
void Test_ExecuteScriptAddSensorRadarAEW(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarAEW.json");
}

// 添加电磁模型：地面雷达
void Test_ExecuteScriptAddSensorRadarGround(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarGround.json");
}
// 添加电磁模型：雷达干扰
void Test_ExecuteScriptAddSensorRadarJammed(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarJammed.json");
}
// 添加电磁模型：天波雷达
void Test_ExecuteScriptAddSensorRadarSky(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarSky.json");
}
// 添加电磁模型：天波雷达
void Test_ExecuteScriptAddSensorRadarSkyEx(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRadarSkyEx.json");
}
// 添加电磁模型：矩形传感器
void Test_ExecuteScriptAddSensorRect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorRect.json");
}
// 添加电磁模型：扇形传感器
void Test_ExecuteScriptAddSensorSector(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorSector.json");
}
// 添加电磁模型：攻击波
void Test_ExecuteScriptAddThreatWave(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddThreatWave.json");
}
// 添加电磁模型：探测
void Test_ExecuteScriptAddSensorDetectObjs(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddSensorDetectObjs.json");
}
// 删除探测属性
void Test_ExecuteScriptDeleteAttrDetect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/DeleteAttrDetect.json");
}
// 测试：ElecMag组件中的属性
void Test_ExecuteScriptAddAttrPowerMap(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddAttrPowerMap.json");
}
void Test_ExecuteScriptAddAttrDetect(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "ElecMag/AddAttrDetect.json");
}

// 测试：Aviation组件中的模型
// 添加航空模型：航线
void Test_ExecuteScriptAddAirLine(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirLine.json");
}
// 添加航空模型：弧形空域
void Test_ExecuteScriptAddAirSpaceArc(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpaceArc.json");
}
// 添加航空模型：圆形空域
void Test_ExecuteScriptAddAirSpaceCircle(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpaceCircle.json");
}
// 添加航空模型：线型空域
void Test_ExecuteScriptAddAirSpacePolyline(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddAirSpacePolyline.json");
}
// 添加航空模型：箔条云
void Test_ExecuteScriptAddChaff(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddChaff.json");
}
//添加航空模型：赤道面
void Test_ExecuteScriptAddEquatorPlane(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddEquatorPlane.json");
}
// 添加航空模型：地理椭球
void Test_ExecuteScriptAddGeoEllip(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Aviation/AddGeoEllip.json");
}
// 添加航空模型：地球光影
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

// 计算距离
void Test_ExecuteScriptCalDist(IVBF_MainCtrl* pIMainCtrl)
{
    VBF_ExecuteScriptFile(pIMainCtrl, "Calculate/CalDist.json");
}

// 脚本注册函数 

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
