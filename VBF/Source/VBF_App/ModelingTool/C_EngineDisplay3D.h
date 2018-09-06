#pragma once
#include "IC_EngineDisplay.h"
#include "VBF_Plot/IVBF_3DPlotDoc.h"

/*
 * @brief 三维显示引擎，负责三维场景的显示
 */
class C_EngineDisplay3D: public IC_EngineDisplay
{
public:
	C_EngineDisplay3D(void);
	~C_EngineDisplay3D(void);

	/*
	 * @brief 获取3D标图文档接口，标图文档负责管理标图的图层
	 * @return IVBF_3DPlotDoc* 三维标图文档接口指针
	 */
	IVBF_3DPlotDoc* get3DPlotDoc() {return m_p3DPlotDoc;}

	/*
	 * @breif 根据对象创建显示符号
	 * @param pObject 对象指针
	 */
	virtual void createSymbolFromObject(CVBF_STObject* pObject);

	/*
	 * @breif 根据对象移除显示符号
	 * @param pObject 对象指针
	 */
	virtual void removeSymbolOfObject(CVBF_STObject* pObject);

	/*
	 * @breif 根据对象关系创建显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void createSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif 根据对象关系移除显示符号
	 * @param pRelation 对象关系指针
	 */
	virtual void removeSymbolFromRelation(CVBF_STObjectRelation* pRelation);

	/*
	 * @breif 获得显示引擎的类型
	 * @param sting 显示引擎的类型
	 */
	virtual string type();

	/*
	 * @breif 清空所有显示符号
	 */
	virtual void clear();

private:
	IVBF_3DPlotDoc* m_p3DPlotDoc;
};

