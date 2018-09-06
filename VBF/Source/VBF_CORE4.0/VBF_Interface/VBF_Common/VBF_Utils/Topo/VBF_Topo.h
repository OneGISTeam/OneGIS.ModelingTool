#ifndef __VBF_TOPO_H__
#define __VBF_TOPO_H__

#include "MathBase.h"
#include "VBF_Array.h"
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>


//�������ݽṹ
typedef struct NodeInf
{
	NodeInf()
	{
		no = 0;
		pt = CPoint(0,0);
	}
	NodeInf& operator=(const NodeInf& p)
	{
		no = p.no;
		pt = p.pt;
		aIdxLines = p.aIdxLines;
		return *this;
	}

	int    no;                  //���
	CPoint pt;                  //�ڵ�����
	CVBF_Array<int> aIdxLines ; //����������Ļ��α�����ݼ�

}NODEINF;//���ε����ݽṹ
class  CVBF_TpLine
{
public:
	CVBF_TpLine()
	{
		no        = 0;
		nNodeFrom = 0;
		nNodeTo   = 0;
		nAreaL    = 0;
		nAreaR    = 0;
		dQI       = 0.0;
		nLeftArc  = 0;
		nRightArc = 0;
		nUsed     = 0;
	}
    CVBF_TpLine operator=(const CVBF_TpLine& p)
	{
		no        = p.no;
		nNodeFrom = p.nNodeFrom;
		nNodeTo   = p.nNodeTo;
		nAreaL    = p.nAreaL;
		nAreaR    = p.nAreaR;
		aPts      = p.aPts;
		dQI       = p.dQI;
		
		nLeftArc  = p.nLeftArc;
		nRightArc = p.nRightArc;
		nUsed     = p.nUsed;

		aOldNo    = p.aOldNo;
		return *this;
	}
	int no ;       //���α��
	int nNodeFrom ;//�׽��
	int nNodeTo ;  //β���
	int nAreaL ;   //�����
	int nAreaR ;   //�����
	
	int nLeftArc;   //�������������еĺ�������
	int nRightArc;  //�������Ҷ�����еĺ�������
	int nUsed;      //�û��α�ʹ�õĴ���

	CVBF_Array<CPoint> aPts ; //���εĵ㼯
	double dQI;
	CVBF_Array<int> aOldNo ; 
};



//������ε����ݽṹ
class  CVBF_TpPolygon
{
public:
	CVBF_TpPolygon()
	{
//		no    =  0;
		nType     = -1;
		dAreaSize = 0.0;
		rBound = CRect(0,0,0,0);
	}
    CVBF_TpPolygon operator=(const CVBF_TpPolygon& p)
	{
		nType     = p.nType;
		aIdxLines = p.aIdxLines;
		dAreaSize = p.dAreaSize;
		rBound    = p.rBound;
		return *this;
	}
//	int no ;                     //����α��
	CVBF_Array<int> aIdxLines ; //�������Ļ��μ���������εı��ֵΪ����˵���������//��������꼯����ȡֵ 
	short  nType ;                //����ε����ͣ�1��߽�,0�ڱ߽�
	double dAreaSize;
	CRect  rBound;
};


//���϶���ε����ݽṹ
class  CVBF_TpPolygons
{
public:
	CVBF_TpPolygons()
	{
		no = 0;
		pt = CPoint(0,0);
	}
    CVBF_TpPolygons operator=(const CVBF_TpPolygons& p)
	{
		no        = p.no;
		pt        = p.pt;
		aPolygon  = p.aPolygon;
		return *this;
	}
	int    no ;          //����α��
	CPoint pt ;          //�ڵ�
	CVBF_Array<CVBF_TpPolygon> aPolygon ;
};

//ÿ������ÿ���ߵ����ݽṹ
typedef struct block_line_inf
{
	block_line_inf()
	{
		no    = 0;
		begin = 0;
		end   = 0;
	}
    block_line_inf operator=(const block_line_inf& p)
	{
		no    = p.no;
		begin = p.begin;
		end   = p.end;
		return *this;
	}
	int  no;    //���
	int  begin; //������
	int  end;
}BLKLINEINF;

//ÿ��������ݽṹ
typedef struct block_inf_topo
{
	CVBF_Array<BLKLINEINF> m_aLines;
	CVBF_Array<int> m_aNodes;
	~block_inf_topo()
	{
		m_aLines.RemoveAll();
		m_aNodes.RemoveAll();
	}
	block_inf_topo& operator=(const block_inf_topo& p)
	{
		m_aLines = p.m_aLines;
		m_aNodes = p.m_aNodes;

		return *this;
	}
}BLKINFTOPO;

//��������ݽṹ
typedef struct IntersectPtInf
{
	IntersectPtInf()
	{
		pt         = CPoint(0,0);
		nLineNo    = 0;
		nPosInLine = 0;
		nLengthToHead = 0;
	}
	CPoint pt;        //��������
	int    nLineNo;   //���������ߵı��
	int    nPosInLine;//���������ϵ�λ�ã�ǰһ�����ţ�
	int    nLengthToHead;
        bool operator==( IntersectPtInf& t )
	{
		return ( nLineNo == t.nLineNo && nPosInLine == t.nPosInLine && pt == t.pt && nLengthToHead==t.nLengthToHead) ;
	}

}INTERSECTPTINF;



class VBF_UTILS_EXPORT CVBF_Topo
{
public:
	CVBF_Topo();
	virtual ~CVBF_Topo();
	void BulidLineTopo();
	void BulidAreaTopo();
	//��ʼ��
	void Init(int x0,int y0,int x1,int y1,
			  int nExtendLimit,int nNodeMatchLimit,int nShortLineLimit,
                          bool bCutLine,bool bLinkLine, int numBlks = 64 );
	//��������
        void AddBoundLine(bool bDevideBlk = TRUE);
        void AddLine(CVBF_Array<CPoint>& aPt,int no,bool bDevideBlk = TRUE);


private:

        bool m_bCutLine  ;
        bool m_bLinkLine ;
	
	//���ཻ����
	void CutIntersectEachOther();
	//���ཻ
	void PolylinesInterset(BLKLINEINF &LineInf1,BLKLINEINF &LineInf2,int num);
	//���뽻�㼯
	void AddToISP(BLKLINEINF &LineInf,CPoint& pt,int i);
	//�ӳ��˵�
	void ExtendHTPoint();
	void ExtendHTPoint(CPoint& pt,int noLine);


	//���
	void BuildNode();
	void BuildArcNodeR();
	void BuildArcAreaR();

	//���
	void RemoveAll();

	//�ڵ�ƥ��
	void NodeMatch();
	void MatchPerNode(int noNode,int nr,int nc);
        bool IsOnSamePolyLine(CVBF_Array<int> &aNodeIdx,int no,int& posSameLine);
	int  PtInWhichGrid(CPoint& pt);
	
	//�ֿ飬Ϊ�˶����ͽڵ�ƥ��
        void DevideBlock(CVBF_TpLine& GeoTpLine,bool bAdd = TRUE);
	void RidLineFromBlk(int nBlockNo,int no);
	

	//�ڵ����±��
	void NodeReNo();

	//׷����
	void BuildArea();
	void SortArc();
	void BulidRightArea(int noLine);
        bool BulidLRArea(int noLine,bool bRigthArea);
        int  GetNextArc(int noLine,bool bRightArea,int noNode);
	void SingleLineClosed();
	void CalAreaSize();
	void BuildPolygons();
        bool PolyInPoly(CVBF_TpPolygon& Poly1,CVBF_TpPolygon& polyT2);
	void BuildInnerPt();

	
        bool m_bInit;//�ж��Ƿ��ʼ��

	int m_nMaxLineNo;
	int m_numBlks;
	double m_dXGrid,m_dYGrid;

	//�߷ֿ飬���ڶ���;�ڵ�ֿ飬���ڽڵ�ƥ��
	CVBF_Array<BLKINFTOPO> m_aBlk;
public:
	//������
	CVBF_Array<CVBF_TpLine> m_aLines;
	//�ڵ��(��ʼ��ʱ��¼���еĶ˵㣻�ڵ�ƥ����������ڼ�¼��ڵ�)
	CVBF_Array<NodeInf> m_aNodes;
	//ƥ���ڵ��
	CVBF_Array<NodeInf> m_aMNodes;
	//�����
	CVBF_Array<INTERSECTPTINF> m_aISPTable;
	//����
	CVBF_Array<CVBF_TpPolygon> m_aPolygon;
	//������
	CVBF_Array<CVBF_TpPolygons> m_aPolygons;
private:
	//�޲�
	int m_nExtendLimit;   //�˵��ӳ��޲�
	int m_nNodeMatchLimit;//�ڵ�ƥ���޲�
	int m_nShortLineLimit;//ȥ�����ߵ��޲�

	//���ݷ�Χ
	int m_x0,m_y0,m_x1,m_y1;

};
#endif // !defined(AFX_DTIS_TOPO_H__61C9991B_770E_4088_B0DE_127D6D1166E5__INCLUDED_)
