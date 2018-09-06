//**********************************************************************************
// FileName：VBF_SGDrawableSet.h
// Function：Drawable集合，继承自osg::Drawable，适用于绘制海量线状模型
//           可向集合中添加多个Drawable，避免多个Drawable导致的效率低下问题
// Author:
// Date:     2015-12-04
//**********************************************************************************

#ifndef __VBF_SG_DRAWABLE_SET_H__
#define __VBF_SG_DRAWABLE_SET_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>


class VBF_GLAUX_EXPORT CVBF_SGDrawableSet : public osg::Drawable
{
public:
    CVBF_SGDrawableSet();
    CVBF_SGDrawableSet(const CVBF_SGDrawableSet& render, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) :osg::Drawable(render, copyop) {}

    // 重载osg::Object的方法
    virtual bool isSameKindAs(const CVBF_Object* obj) const   { return dynamic_cast<const CVBF_SGDrawableSet*>(obj) != NULL; }

    virtual const char* libraryName() const { return "VBF"; }
    virtual const char* className() const { return "CVBF_SGDrawableSet"; }
    virtual CVBF_Object* cloneType() const { return new CVBF_SGDrawableSet(); }
    virtual CVBF_Object* clone(const osg::CopyOp& copyop) const { return new CVBF_SGDrawableSet(*this, copyop); }

    // 覆盖osg::Drawable的方法
    virtual void drawImplementation(osg::RenderInfo& renderInfo) const;

    // 向集合中添加一个Drawable，返回该Drawable在集合中的序号（从0开始）
    int AddDrawable(osg::Drawable* pDrawable);

    // 获取已经添加的Drawable信息，参数nIndex表示Drawable在整个集合中的序号
    int  GetNumDrawables()  { return m_vDrawables.size(); }
    osg::Drawable* GetDrawable(int nIndex)  { return (nIndex>=0 && nIndex<m_vDrawables.size())? m_vDrawables[nIndex] : NULL; }

    // 设置整个集合是否可见
    void SetVisible(bool bVisible);
    bool IsVisible() { return m_bVisible; }

    // 设置/获取集合中某个Drawable是否可见，参数nIndex表示Drawable在整个集合中的序号
    void SetDrawableVisible(int nIndex, bool bVisible);
    void SetDrawableVisible(osg::Drawable* pDrawable, bool bVisible);

    // 获取集合中某个Drawable是否可见
    bool IsDrawableVisible(int nIndex)   { return (nIndex>=0 && nIndex<m_vDrawableVisible.size())? m_vDrawableVisible[nIndex] : false; }
    bool IsDrawableVisible(osg::Drawable* pDrawable);

protected:
    virtual ~CVBF_SGDrawableSet() {}

protected:
    bool        m_bVisible; // 整个集合是否可见

    // 集合中的所有Drawable
    std::vector< ref_ptr<osg::Drawable> >   m_vDrawables;
    std::vector<bool>                       m_vDrawableVisible; // 每个Drawable的可见性，与m_vDrawables必须一一对应
};

#endif
