#ifndef __VBF_TOPO_H__
#define __VBF_TOPO_H__

#include "MathBase.h"
#include "VBF_Array.h"
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>


//结点的数据结构
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

	int    no;                  //编号
	CPoint pt;                  //节点坐标
	CVBF_Array<int> aIdxLines ; //结点所关联的弧段编号数据集

}NODEINF;//弧段的数据结构
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
	int no ;       //弧段编号
	int nNodeFrom ;//首结点
	int nNodeTo ;  //尾结点
	int nAreaL ;   //左面号
	int nAreaR ;   //右面号
	
	int nLeftArc;   //弧段在左多边形中的后续弧段
	int nRightArc;  //弧段在右多边形中的后续弧段
	int nUsed;      //该弧段被使用的次数

	CVBF_Array<CPoint> aPts ; //弧段的点集
	double dQI;
	CVBF_Array<int> aOldNo ; 
};



//单多边形的数据结构
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
//	int no ;                     //多边形编号
	CVBF_Array<int> aIdxLines ; //所关联的弧段集，如果弧段的编号值为负，说明弧段组成//多边形坐标集反向取值 
	short  nType ;                //多边形的类型，1外边界,0内边界
	double dAreaSize;
	CRect  rBound;
};


//复合多边形的数据结构
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
	int    no ;          //多边形编号
	CPoint pt ;          //内点
	CVBF_Array<CVBF_TpPolygon> aPolygon ;
};

//每个块中每条线的数据结构
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
	int  no;    //编号
	int  begin; //本块中
	int  end;
}BLKLINEINF;

//每个块的数据结构
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

//交点的数据结构
typedef struct IntersectPtInf
{
	IntersectPtInf()
	{
		pt         = CPoint(0,0);
		nLineNo    = 0;
		nPosInLine = 0;
		nLengthToHead = 0;
	}
	CPoint pt;        //交点坐标
	int    nLineNo;   //交点所在线的编号
	int    nPosInLine;//交点在线上的位置（前一点的序号）
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
	//初始化
	void Init(int x0,int y0,int x1,int y1,
			  int nExtendLimit,int nNodeMatchLimit,int nShortLineLimit,
                          bool bCutLine,bool bLinkLine, int numBlks = 64 );
	//输入数据
        void AddBoundLine(bool bDevideBlk = TRUE);
        void AddLine(CVBF_Array<CPoint>& aPt,int no,bool bDevideBlk = TRUE);


private:

        bool m_bCutLine  ;
        bool m_bLinkLine ;
	
	//互相交处理
	void CutIntersectEachOther();
	//线相交
	void PolylinesInterset(BLKLINEINF &LineInf1,BLKLINEINF &LineInf2,int num);
	//加入交点集
	void AddToISP(BLKLINEINF &LineInf,CPoint& pt,int i);
	//延长端点
	void ExtendHTPoint();
	void ExtendHTPoint(CPoint& pt,int noLine);


	//结果
	void BuildNode();
	void BuildArcNodeR();
	void BuildArcAreaR();

	//输出
	void RemoveAll();

	//节点匹配
	void NodeMatch();
	void MatchPerNode(int noNode,int nr,int nc);
        bool IsOnSamePolyLine(CVBF_Array<int> &aNodeIdx,int no,int& posSameLine);
	int  PtInWhichGrid(CPoint& pt);
	
	//分块，为了断链和节点匹配
        void DevideBlock(CVBF_TpLine& GeoTpLine,bool bAdd = TRUE);
	void RidLineFromBlk(int nBlockNo,int no);
	

	//节点重新编号
	void NodeReNo();

	//追踪面
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

	
        bool m_bInit;//判断是否初始化

	int m_nMaxLineNo;
	int m_numBlks;
	double m_dXGrid,m_dYGrid;

	//线分块，用于断链;节点分块，用于节点匹配
	CVBF_Array<BLKINFTOPO> m_aBlk;
public:
	//线数组
	CVBF_Array<CVBF_TpLine> m_aLines;
	//节点表(初始化时记录所有的端点；节点匹配结束后，用于记录真节点)
	CVBF_Array<NodeInf> m_aNodes;
	//匹配后节点表
	CVBF_Array<NodeInf> m_aMNodes;
	//交点表
	CVBF_Array<INTERSECTPTINF> m_aISPTable;
	//单面
	CVBF_Array<CVBF_TpPolygon> m_aPolygon;
	//复合面
	CVBF_Array<CVBF_TpPolygons> m_aPolygons;
private:
	//限差
	int m_nExtendLimit;   //端点延长限差
	int m_nNodeMatchLimit;//节点匹配限差
	int m_nShortLineLimit;//去除短线的限差

	//数据范围
	int m_x0,m_y0,m_x1,m_y1;

};
#endif // !defined(AFX_DTIS_TOPO_H__61C9991B_770E_4088_B0DE_127D6D1166E5__INCLUDED_)
