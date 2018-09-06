#ifndef OSGUTIL_KEYSWITCMATRIXMANIPULATOR
#define OSGUTIL_KEYSWITCMATRIXMANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>

namespace osgGA{

class ::IVBF_GUIActionAdapter;

// �����л���������ͨ�������л����ֲ�����
class OSGGA_EXPORT KeySwitchMatrixManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
    public:
        typedef std::pair<std::string, ref_ptr<IVBF_CameraManipulator> > NamedManipulator;
        typedef std::map<int, NamedManipulator> KeyManipMap;

        virtual const char* className() const { return "KeySwitchMatrixManipulator"; }

        // ���һ��������.key����ֵ��name�����������ƣ�cm��������
        void addMatrixManipulator(int key, std::string name, IVBF_CameraManipulator* cm);

        // ���һ�����������Զ��ͼ��̰󶨣��󶨵ļ�Ϊ'1'+ǰ���Ѿ�ע��Ĳ���������
        void addNumberedMatrixManipulator(IVBF_CameraManipulator* cm);

        // ��ȡ�������ĸ���
        unsigned int getNumMatrixManipulators() const { return _manips.size(); }

        // ��˳��ѡ�������
        void selectMatrixManipulator(unsigned int num);

        // ��ȡ�ò��������������в��������б�
        KeyManipMap& getKeyManipMap() { return _manips; }
        const KeyManipMap& getKeyManipMap() const { return _manips; }

        // ��ȡ��ǰ����Ĳ�����
        IVBF_CameraManipulator* getCurrentMatrixManipulator() { return _current.get(); }
        const IVBF_CameraManipulator* getCurrentMatrixManipulator() const { return _current.get(); }


        // ����˳���ȡ������
        IVBF_CameraManipulator* getMatrixManipulatorWithIndex(unsigned int key);
        const IVBF_CameraManipulator* getMatrixManipulatorWithIndex(unsigned int key) const;

        // ���ݼ�ֵ��ȡ������
        IVBF_CameraManipulator* getMatrixManipulatorWithKey(unsigned int key);
        const IVBF_CameraManipulator* getMatrixManipulatorWithKey(unsigned int key) const;

        // ����IVBF_CameraManipulator����

        // ����/��ȡ"����ϵ�ص�"���ûص����߲������ϡ�����������
        virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb);

        // ͨ������/��������ò�����
        virtual void setByMatrix(const osg::Matrixd& matrix) { _current->setByMatrix(matrix); }
        virtual void setByInverseMatrix(const osg::Matrixd& matrix) { _current->setByInverseMatrix(matrix); }

        // ��ȡ�������ľ���/�����
        virtual osg::Matrixd getMatrix() const { return _current->getMatrix(); }
        virtual osg::Matrixd getInverseMatrix() const { return _current->getInverseMatrix(); }

        // �ռ��ںϾ��룬����˫Ŀ����,������ӿ�
        virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return _current->getFusionDistanceMode(); }
        virtual float getFusionDistanceValue() const { return _current->getFusionDistanceValue(); }


        // ��ڵ���صĺ�������Щ��������Ҫ������٣�����Щ����Ҫ��,������ӿ�
        virtual void setNode(osg::IVBF_SGNode* n);
        virtual const osg::IVBF_SGNode* getNode() const        { return _current->getNode(); }
        virtual osg::IVBF_SGNode* getNode()                    { return _current->getNode(); }

        // ��Ĭ��λ����صĺ���,������ӿ�
        virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false);
        virtual void setAutoComputeHomePosition(bool flag);
        virtual void computeHomePosition();
        virtual void home(const GUIEventAdapter& ee,::IVBF_GUIActionAdapter& aa);

        virtual void init(const GUIEventAdapter& ee,::IVBF_GUIActionAdapter& aa) { if (_current.valid()) _current->init(ee,aa); }
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);

        // ��ȡ�ò��������ͼ��̵��÷�
        virtual void GetUsage(::ApplicationUsage& usage) const;

    private:

        KeyManipMap _manips;

        ref_ptr<IVBF_CameraManipulator> _current;
};

}

#endif
