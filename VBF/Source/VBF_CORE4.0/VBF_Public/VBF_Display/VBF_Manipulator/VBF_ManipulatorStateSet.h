#ifndef OSGGA_STATESET_MANIPULATOR
#define OSGGA_STATESET_MANIPULATOR 1

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>

#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrPolygonMode.h>


namespace osgGA {

// 状态集操作，不完善
class OSGGA_EXPORT StateSetManipulator : public GUIEventHandler
{
public:

        StateSetManipulator(osg::StateSet* stateset=0);

        virtual const char* className() const { return "StateSetManipulator"; }

        // 设置/获取关联的状态集
        virtual void setStateSet(osg::StateSet*);
        virtual osg::StateSet * getStateSet();
        virtual const osg::StateSet * getStateSet() const;
        
        virtual bool handle(const GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us);        

        // 获取该操作器鼠标和键盘的用法
        virtual void GetUsage(::ApplicationUsage& usage) const;
        
        void setMaximumNumOfTextureUnits(unsigned int i) { _maxNumOfTextureUnits = i; }
        unsigned int getMaximumNumOfTextureUnits() const { return _maxNumOfTextureUnits; }
        
        void setBackfaceEnabled(bool newbackface);
        bool getBackfaceEnabled() const {return _backface;};

        void setLightingEnabled(bool newlighting);
        bool getLightingEnabled() const {return _lighting;};

        void setTextureEnabled(bool newtexture);
        bool getTextureEnabled() const {return _texture;};

        void setPolygonMode(osg::PolygonMode::Mode newpolygonmode);
        osg::PolygonMode::Mode getPolygonMode() const;
        
        void cyclePolygonMode();


        void setKeyEventToggleBackfaceCulling(int key) { _keyEventToggleBackfaceCulling = key; }
        int getKeyEventToggleBackfaceCulling() const { return _keyEventToggleBackfaceCulling; }

        void setKeyEventToggleLighting(int key) { _keyEventToggleLighting = key; }
        int getKeyEventToggleLighting() const { return _keyEventToggleLighting; }

        void setKeyEventToggleTexturing(int key) { _keyEventToggleTexturing = key; }
        int getKeyEventToggleTexturing() const { return _keyEventToggleTexturing; }

        void setKeyEventCyclePolygonMode(int key) { _keyEventCyclePolygonMode = key; }
        int getKeyEventCyclePolygonMode() const { return _keyEventCyclePolygonMode; }

protected:

        virtual ~StateSetManipulator();

        void clone();

        ref_ptr<osg::StateSet> _stateset;

        bool _initialized;
        bool _backface;
        bool _lighting;
        bool _texture;
        unsigned int _maxNumOfTextureUnits;
        
        int _keyEventToggleBackfaceCulling;
        int _keyEventToggleLighting;
        int _keyEventToggleTexturing;
        int _keyEventCyclePolygonMode;

        osg::PolygonMode* getOrCreatePolygonMode();
};

}

#endif
