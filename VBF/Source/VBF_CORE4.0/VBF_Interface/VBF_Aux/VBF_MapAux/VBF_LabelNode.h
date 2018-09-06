//***************************************************************************************
// FileName：VBF_LabelNode.h
// Function：对LabelNode进行的扩展，使其支持中文
// Author:   杜莹
// Date:     2012-03-23
//***************************************************************************************

#ifndef __VBF_LABEL_NODE_H__
#define __VBF_LABEL_NODE_H__

#include <VBF_Aux/VBF_MapAux/VBF_MapAuxExport.h>
#include <VBF_3DMap/VBF_Annotation/LabelNode.h>

using namespace osg;
using namespace osgEarth;
using namespace osgEarth::Annotation;


class VBF_MAPAUX_EXPORT CVBF_LabelNode : public LabelNode
{
public:
	CVBF_LabelNode(CVBFO_SGNodeMap* mapNode, const TextSymbol* symbol);
	virtual ~CVBF_LabelNode() {}

	void setText(const char* szText);
	void setDrawMode(unsigned int mode);
	bool SetTextSymbol(const TextSymbol* pSymbol);
};


#endif
