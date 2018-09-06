/**************************************************************************************************
* @file ManipulatorUtil.h
* @note �����볡���������Լ����������صĺ�������Щ����������һЩ�����Ĳ�����
* @author l00008
* @data 2014-07-07
**************************************************************************************************/
#ifndef MANIPULATOR_UTIL_H
#define MANIPULATOR_UTIL_H

#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
//#include <osgViewer/View>
//#include <osgGA/KeySwitchMatrixManipulator>
#include <VBF_Aux/VBF_MapAux/FreeEarthManipulator.h>
#include <VBF_Aux/VBF_MapAux/FirstPersonManipulator.h>
#include <VBF_Aux/VBF_MapAux/FeLockNodeManipulator.h>

#include <VBF_Display/VBF_Manipulator/VBF_ManipulatorKeySwitchMatrix.h>
#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>

namespace FeKit
{

//!! �ĵ� IVBF_3DMainCtrl
	///������������
    class VBF_MAPAUX_EXPORT CManipulatorManager : public osgGA::KeySwitchMatrixManipulator
	{
	public:
        enum ManiTypes
        {
            FreeEarth = 0,
            FirstPerson,
            FeLock
        };

        explicit CManipulatorManager(IVBF_3DMainCtrl* pMainCtrl);
		virtual ~CManipulatorManager();

    public:
        void SetViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 );

        void AddFreeEarthMainpulator();
        void AddFirstPersonManipulator();
        void AddFeLockManipulator();

        FeKit::FreeEarthManipulator* GetFreeEarthManipulator();
        FeKit::FirstPersonManipulator* GetFirstPersonManipulator();
        FeKit::FeLockNodeManipulator* GetFeLockManipulator();

        void ActiveFreeEarthManipulator();
        void ActiveFirstPersonManipulator();
        void ActiveFeLockManipulator();

		/// �����л������� w00024
        virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

    protected:
        bool ChangedFeLockType();
    private:
        IVBF_3DMainCtrl* m_op3dMainCtrl;
        ref_ptr<FeUtil::CRenderContext> m_opRenderContext;
        ManiTypes m_curTypes;
	};

} 


#endif //MANIPULATOR_UTIL_H
