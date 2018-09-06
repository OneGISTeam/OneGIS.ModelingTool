#ifndef ROCMILIMARK_DATADEF
#define ROCMILIMARK_DATADEF


#include <VBF_STL.h>
#include <math.h>
#include <Types/Vec2i.h>
#include <Types/Vec3d>
#include <VBF_Macros.h>


using namespace std;

#ifdef _MSC_VER
	#pragma warning(disable: 4006 4183 4101 4305 4786 4088)
#endif

#ifndef _WINGDI_
	#define RGB(r,g,b)			((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	#define GetRValue(rgb)      ((BYTE)(rgb))
	#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
	#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
#endif


//--------------------------------------------------------------
// ����ṹ�壺VBF_SYMBOLCLASS_INFO
// �ṹ���������������������Ļ�����Ϣ
//--------------------------------------------------------------
typedef struct _tagVBFSymbolClassInfo
{
	unsigned int	nID;		// ��������
    string			strName;	// ����������
} VBF_SYMBOLCLASS_INFO;



#endif
