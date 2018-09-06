#include "AC_FilterSTObject.h"


AC_FilterSTObject::AC_FilterSTObject()
{

}

AC_FilterSTObject::~AC_FilterSTObject()
{

}

string AC_FilterSTObject::filterName()
{
	return "Filter_Basic";
}

vector<CVBF_STObject*> AC_FilterSTObject::filter( vector<CVBF_STObject*> source, bool bTimeRegarded /*= true*/ )
{
	vector<CVBF_STObject*> result;
	if(bTimeRegarded){
		vector<CVBF_STObject*>::iterator iter = source.begin();
		while(iter != source.end()){
			//原则上对象特征值得生命周期范围不得超过对象本身的生命周期范围，可先对对象本身的生命周期范围进行过滤
			if((*iter)->GetBeginTime() <= m_dCurrentTime && m_dCurrentTime <= (*iter)->GetEndTime()){
				CVBF_STObject* pTempObject = (*iter)->Clone();
				//过滤属性
				CVBF_STObjectAttrs& attrs = pTempObject->Attrs();
				for(int i=0; i<attrs.Size(); i++){
					CVBF_STObjectAttr* pAttr = attrs.GetAt(i);
					if(pAttr->GetTime() > m_dCurrentTime){
						attrs.Remove(pAttr);
					}
				}
				//过滤位置

				//过滤形态
				CVBF_STObjectForms& forms = pTempObject->Forms();
				for(int i=0; i<forms.Size(); i++){
					CVBF_STObjectForm* pForm = forms.GetAt(i);
					if(pForm->GetTime() > m_dCurrentTime){
						forms.Remove(pForm);
					}
				}

				result.push_back(pTempObject);
			}
			iter++;
		}
	}else{
		return source;
	}

	return result;
}
