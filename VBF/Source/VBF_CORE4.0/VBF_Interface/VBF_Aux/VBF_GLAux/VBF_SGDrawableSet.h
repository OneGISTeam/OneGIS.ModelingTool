//**********************************************************************************
// FileName��VBF_SGDrawableSet.h
// Function��Drawable���ϣ��̳���osg::Drawable�������ڻ��ƺ�����״ģ��
//           ���򼯺�����Ӷ��Drawable��������Drawable���µ�Ч�ʵ�������
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

    // ����osg::Object�ķ���
    virtual bool isSameKindAs(const CVBF_Object* obj) const   { return dynamic_cast<const CVBF_SGDrawableSet*>(obj) != NULL; }

    virtual const char* libraryName() const { return "VBF"; }
    virtual const char* className() const { return "CVBF_SGDrawableSet"; }
    virtual CVBF_Object* cloneType() const { return new CVBF_SGDrawableSet(); }
    virtual CVBF_Object* clone(const osg::CopyOp& copyop) const { return new CVBF_SGDrawableSet(*this, copyop); }

    // ����osg::Drawable�ķ���
    virtual void drawImplementation(osg::RenderInfo& renderInfo) const;

    // �򼯺������һ��Drawable�����ظ�Drawable�ڼ����е���ţ���0��ʼ��
    int AddDrawable(osg::Drawable* pDrawable);

    // ��ȡ�Ѿ���ӵ�Drawable��Ϣ������nIndex��ʾDrawable�����������е����
    int  GetNumDrawables()  { return m_vDrawables.size(); }
    osg::Drawable* GetDrawable(int nIndex)  { return (nIndex>=0 && nIndex<m_vDrawables.size())? m_vDrawables[nIndex] : NULL; }

    // �������������Ƿ�ɼ�
    void SetVisible(bool bVisible);
    bool IsVisible() { return m_bVisible; }

    // ����/��ȡ������ĳ��Drawable�Ƿ�ɼ�������nIndex��ʾDrawable�����������е����
    void SetDrawableVisible(int nIndex, bool bVisible);
    void SetDrawableVisible(osg::Drawable* pDrawable, bool bVisible);

    // ��ȡ������ĳ��Drawable�Ƿ�ɼ�
    bool IsDrawableVisible(int nIndex)   { return (nIndex>=0 && nIndex<m_vDrawableVisible.size())? m_vDrawableVisible[nIndex] : false; }
    bool IsDrawableVisible(osg::Drawable* pDrawable);

protected:
    virtual ~CVBF_SGDrawableSet() {}

protected:
    bool        m_bVisible; // ���������Ƿ�ɼ�

    // �����е�����Drawable
    std::vector< ref_ptr<osg::Drawable> >   m_vDrawables;
    std::vector<bool>                       m_vDrawableVisible; // ÿ��Drawable�Ŀɼ��ԣ���m_vDrawables����һһ��Ӧ
};

#endif
