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
			//ԭ���϶�������ֵ���������ڷ�Χ���ó�����������������ڷ�Χ�����ȶԶ�������������ڷ�Χ���й���
			if((*iter)->GetBeginTime() <= m_dCurrentTime && m_dCurrentTime <= (*iter)->GetEndTime()){
				CVBF_STObject* pTempObject = (*iter)->Clone();
				//��������
				CVBF_STObjectAttrs& attrs = pTempObject->Attrs();
				for(int i=0; i<attrs.Size(); i++){
					CVBF_STObjectAttr* pAttr = attrs.GetAt(i);
					if(pAttr->GetTime() > m_dCurrentTime){
						attrs.Remove(pAttr);
					}
				}
				//����λ��

				//������̬
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
