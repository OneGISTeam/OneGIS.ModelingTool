#ifndef OSGUTIL_KEYSWITCMATRIXMANIPULATOR
#define OSGUTIL_KEYSWITCMATRIXMANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>

namespace osgGA{

class ::IVBF_GUIActionAdapter;

// 键盘切换操作器：通过键盘切换各种操作器
class OSGGA_EXPORT KeySwitchMatrixManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:
        typedef std::pair<std::string, ref_ptr<IVBF_CameraManipulator> > NamedManipulator;
        typedef std::map<int, NamedManipulator> KeyManipMap;

        virtual const char* className() const { return "KeySwitchMatrixManipulator"; }

        // 添加一个操作器.key：键值；name：操作器名称；cm：操作器
        void addMatrixManipulator(int key, std::string name, IVBF_CameraManipulator* cm);

        // 添加一个操作器，自动和键盘绑定（绑定的键为'1'+前面已经注册的操作器数）
        void addNumberedMatrixManipulator(IVBF_CameraManipulator* cm);

        // 获取操作器的个数
        unsigned int getNumMatrixManipulators() const { return _manips.size(); }

        // 按顺序选择操作器
        void selectMatrixManipulator(unsigned int num);

        // 获取该操作器关联的所有操作器的列表
        KeyManipMap& getKeyManipMap() { return _manips; }
        const KeyManipMap& getKeyManipMap() const { return _manips; }

        // 获取当前激活的操作器
        IVBF_CameraManipulator* getCurrentMatrixManipulator() { return _current.get(); }
        const IVBF_CameraManipulator* getCurrentMatrixManipulator() const { return _current.get(); }


        // 根据顺序获取操作器
        IVBF_CameraManipulator* getMatrixManipulatorWithIndex(unsigned int key);
        const IVBF_CameraManipulator* getMatrixManipulatorWithIndex(unsigned int key) const;

        // 根据键值获取操作器
        IVBF_CameraManipulator* getMatrixManipulatorWithKey(unsigned int key);
        const IVBF_CameraManipulator* getMatrixManipulatorWithKey(unsigned int key) const;

        // 重载IVBF_CameraManipulator函数

        // 设置/获取"坐标系回调"，该回调告诉操作器上、东、北方向
        virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb);

        // 通过矩阵/逆矩阵设置操作器
        virtual void setByMatrix(const osg::Matrixd& matrix) { _current->setByMatrix(matrix); }
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { _current->setByInverseMatrix(matrix); }

        // 获取操作器的矩阵/逆矩阵
        virtual osg::Matrixd getMatrix() const { return _current->getMatrix(); }
        virtual osg::Matrixd getInverseMatrix() const { return _current->getInverseMatrix(); }

        // 空间融合距离，用于双目立体,含义见接口
        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return _current->getFusionDistanceMode(); }
        virtual float getFusionDistanceValue() const { return _current->getFusionDistanceValue(); }


        // 与节点相关的函数（有些操作器需要（如跟踪），有些不需要）,含义见接口
        virtual void setNode(osg::IVBF_SGNode* n);
        virtual const osg::IVBF_SGNode* getNode() const        { return _current->getNode(); }
        virtual osg::IVBF_SGNode* getNode()                    { return _current->getNode(); }

        // 与默认位置相关的函数,含义见接口
        virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false);
        virtual void setAutoComputeHomePosition(bool flag);
        virtual void computeHomePosition();
        virtual void home(const GUIEventAdapter& ee,::IVBF_GUIActionAdapter& aa);

        virtual void init(const GUIEventAdapter& ee,::IVBF_GUIActionAdapter& aa) { if (_current.valid()) _current->init(ee,aa); }
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        // 获取该操作器鼠标和键盘的用法
        virtual void GetUsage(::ApplicationUsage& usage) const;

    private:

        KeyManipMap _manips;

        ref_ptr<IVBF_CameraManipulator> _current;
};

}

#endif
