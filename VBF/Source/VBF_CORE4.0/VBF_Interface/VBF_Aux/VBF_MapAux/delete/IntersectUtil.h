/**************************************************************************************************
* @file FloatUtil.h
* @note 定义了一些浮点型值的比较、溢出等方法
* @author 00008
* @data 2014-4-30
**************************************************************************************************/
#ifndef FE_INTERSECT_MATH_UTIL_H
#define FE_INTERSECT_MATH_UTIL_H

#include <list>
#include <vector>
#include <algorithm>
#include <Types/Vec3d>
#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
//#include <osg/Geode>
#include <VBF_Engine/VBF_SceneGraph/TriangleFunctor>
#include <fstream>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGeometry.h>

//#include <FeUtils/Export.h>

using namespace std;   

///碰撞检测算法，提供各种类型的碰撞检测算法，主要作为操作器的实现支持算法
namespace FeMath
{
        extern bool intersectWithEllipse(double aAxis,double bAxis,double cAxis,osg::Vec3d& p1,osg::Vec3d& p2,osg::Vec3d& out_pt1,osg::Vec3d& out_pt2);

        extern int getLinePanelIntersec(osg::Vec3d linePoint, osg::Vec3d lineVector,osg::Vec3d planePoint,osg::Vec3d planeNor, double& tHit,osg::Vec3d& PHit);

        class aabbox3d
	{
	public:

		aabbox3d(): MinEdge(-1,-1,-1), MaxEdge(1,1,1) {}
		aabbox3d(const osg::Vec3d& min, const osg::Vec3d& max): MinEdge(min), MaxEdge(max) {}
		aabbox3d(const osg::Vec3d& init): MinEdge(init), MaxEdge(init) {}


		inline bool operator==(const aabbox3d& other) const { return (MinEdge == other.MinEdge && other.MaxEdge == MaxEdge);}

		inline bool operator!=(const aabbox3d& other) const { return !(MinEdge == other.MinEdge && other.MaxEdge == MaxEdge);}

		void reset(double x, double y, double z)
		{
			MaxEdge = osg::Vec3d(x,y,z);
			MinEdge = MaxEdge;
		}

		void reset(const aabbox3d& initValue)
		{
			*this = initValue;
		}

		void reset(const osg::Vec3d& initValue)
		{
			MaxEdge = initValue;
			MinEdge = initValue;
		}

		void addInternalPoint(const osg::Vec3d& p)
		{
			addInternalPoint(p.x(), p.y(), p.z());
		}

		void addInternalBox(const aabbox3d& b)
		{
			addInternalPoint(b.MaxEdge);
			addInternalPoint(b.MinEdge);
		}

		void addInternalPoint(double x, double y, double z)
		{
			if (x>MaxEdge.x()) MaxEdge.x() = x;
			if (y>MaxEdge.y()) MaxEdge.y() = y;
			if (z>MaxEdge.z()) MaxEdge.z() = z;

			if (x<MinEdge.x()) MinEdge.x() = x;
			if (y<MinEdge.y()) MinEdge.y() = y;
			if (z<MinEdge.z()) MinEdge.z() = z;
		}

		osg::Vec3d getCenter() const
		{
			return (MinEdge + MaxEdge) / 2;
		}

		osg::Vec3d getExtent() const
		{
			return MaxEdge - MinEdge;
		}

		bool isEmpty() const
		{
			if(MinEdge==MaxEdge) return true;
			else return false;
		}

		void getEdges(osg::Vec3d *edges) const
		{
			const osg::Vec3d middle = getCenter();
			const osg::Vec3d diag = middle - MaxEdge;

			/*
			/3---------/7
			/ |        /|
			/  |       / |
			1---------5   |
			|  /2- - -|- -6
			| /       |  /
			|/        | /
			0---------4/
			*/

			edges[0] = osg::Vec3d(middle.x() + diag.x(), middle.y() + diag.y(), middle.z() + diag.z());
			edges[1] = osg::Vec3d(middle.x() + diag.x(), middle.y() - diag.y(), middle.z() + diag.z());
			edges[2] = osg::Vec3d(middle.x() + diag.x(), middle.y() + diag.y(), middle.z() - diag.z());
			edges[3] = osg::Vec3d(middle.x() + diag.x(), middle.y() - diag.y(), middle.z() - diag.z());
			edges[4] = osg::Vec3d(middle.x() - diag.x(), middle.y() + diag.y(), middle.z() + diag.z());
			edges[5] = osg::Vec3d(middle.x() - diag.x(), middle.y() - diag.y(), middle.z() + diag.z());
			edges[6] = osg::Vec3d(middle.x() - diag.x(), middle.y() + diag.y(), middle.z() - diag.z());
			edges[7] = osg::Vec3d(middle.x() - diag.x(), middle.y() - diag.y(), middle.z() - diag.z());
		}

		bool intersectsWithBox(const aabbox3d& other) const
		{
			return (MinEdge.x() <= other.MaxEdge.x() && MinEdge.y() <= other.MaxEdge.y() && MinEdge.z() <= other.MaxEdge.z() &&
				MaxEdge.x() >= other.MinEdge.x() && MaxEdge.y() >= other.MinEdge.y() && MaxEdge.z() >= other.MinEdge.z());
		}

		bool isPointInside(const osg::Vec3d& p) const
		{
			return (p.x() >= MinEdge.x() && p.x() <= MaxEdge.x() &&
				p.y() >= MinEdge.y() && p.y() <= MaxEdge.y() &&
				p.z() >= MinEdge.z() && p.z() <= MaxEdge.z());
		}


		osg::Vec3d MinEdge;

		osg::Vec3d MaxEdge;
	};

        class plane3d
	{
	public:

		plane3d(): Normal(0,1,0) { recalculateD(osg::Vec3d(0,0,0)); }

		plane3d(const osg::Vec3d& MPoint, const osg::Vec3d& Normal) : Normal(Normal) { recalculateD(MPoint); }

		plane3d(double px, double py, double pz, double nx, double ny, double nz) : Normal(nx, ny, nz) { recalculateD(osg::Vec3d(px, py, pz)); }

		plane3d(const osg::Vec3d& point1, const osg::Vec3d& point2, const osg::Vec3d& point3)
		{ setPlane(point1, point2, point3); }

		plane3d(const osg::Vec3d& normal, const double d) : Normal(normal), D(d) { }

		inline bool operator==(const plane3d& other) const { return (D==other.D&& Normal==other.Normal);}

		inline bool operator!=(const plane3d& other) const { return !(*this == other);}

		void setPlane(const osg::Vec3d& point, const osg::Vec3d& nvector)
		{
			Normal = nvector;
			recalculateD(point);
		}

		void setPlane(const osg::Vec3d& nvect, double d)
		{
			Normal = nvect;
			D = d;
		}

		void setPlane(const osg::Vec3d& point1, const osg::Vec3d& point2, const osg::Vec3d& point3)
		{
			Normal = (point2 - point1) ^ (point3 - point1);
			Normal.normalize();
			recalculateD(point1);
		}

		void recalculateD(const osg::Vec3d& MPoint)
		{
			D = -(MPoint * Normal);
		}

#define	F32_LOWER_EQUAL_0(n)	((n) <= 0.0f)
		bool isFrontFacing(const osg::Vec3d& lookDirection) const
		{
			const double d = Normal * lookDirection;
			return F32_LOWER_EQUAL_0 ( d );
		}

		double getDistanceTo(const osg::Vec3d& point) const
		{
			return point * Normal + D;
		}

		osg::Vec3d Normal;
		double D;
	};

    class   triangle3d
	{
	public:
		triangle3d();
		~triangle3d();
	public:
		osg::Vec3d PointA;
		osg::Vec3d PointB;
		osg::Vec3d PointC;
	public:
		triangle3d(osg::Vec3d pointA,osg::Vec3d pointB,osg::Vec3d pointC);

		bool isTotalInsideBox(const aabbox3d& box) const
		{
			return (box.isPointInside(PointA) &&
				box.isPointInside(PointB) &&
				box.isPointInside(PointC));
		}
		plane3d getPlane() const
		{
			return plane3d(PointA, PointB, PointC);
		}
		bool isOnSameSide(const osg::Vec3d& p1, const osg::Vec3d& p2,
			const osg::Vec3d& a, const osg::Vec3d& b) const
		{
			osg::Vec3d bminusa = b - a;
			osg::Vec3d cp1;
			cp1 = bminusa ^ (p1 - a);
			osg::Vec3d cp2;
			cp2 = bminusa ^ (p2 - a);
			return (cp1 * cp2 >= 0.0f);
		}
		bool isPointInside(const osg::Vec3d& p) const
		{
			return (isOnSameSide(p, PointA, PointB, PointC) &&
				isOnSameSide(p, PointB, PointA, PointC) &&
				isOnSameSide(p, PointC, PointA, PointB));
		}
	};

    class COctreeTriangleSelector
	{
	public:

        struct SOctreeNode
		{
			SOctreeNode()
			{
				for (int i=0; i!=8; ++i)
					Child[i] = 0;
			}

			~SOctreeNode()
			{
				for (int i=0; i!=8; ++i)
					delete Child[i];
			}

                        std::list<triangle3d> Triangles;
			SOctreeNode* Child[8];
			aabbox3d Box;
		};

                struct MyTriangleFunctor
		{
			MyTriangleFunctor()
			{
			}
			void operator () (const osg::Vec3& v1,const osg::Vec3& v2,const osg::Vec3& v3, bool treatVertexDataAsTemporary);

			void set(SOctreeNode* node)
			{
				m_octreeNode = node;
			}

			void set(osg::MatrixList& ml)
			{
				m_matrixList = ml;
			}

			SOctreeNode* m_octreeNode;
			osg::MatrixList m_matrixList;
		};

                struct ModelTriangleFunctor
		{
			ModelTriangleFunctor()
                            :m_isInitBox(false)
			{
			}
			void operator () (const osg::Vec3& v1,const osg::Vec3& v2,const osg::Vec3& v3, bool treatVertexDataAsTemporary);

			void setRootNode(SOctreeNode* node)
			{
				m_octreeNode = node;
			}

			void setWorldMat(osg::Matrix& m)
			{
				m_worldMat = m;
			}

			SOctreeNode* m_octreeNode;
			osg::Matrix m_worldMat;
                        bool m_isInitBox;
		};

		template<class T>
                class DoubleTriangleFunctor : public osg::TriangleFunctor<T>
		{
			virtual void setVertexArray(unsigned int count,const osg::Vec3d* pVertex);
			//virtual void setVertexArray(unsigned int count,const osg::Vec3* vertices);

			virtual void drawArrays(GLenum mode,GLint first,GLsizei count);
			virtual void drawElements(GLenum mode,GLsizei count,const GLubyte* indices);
			virtual void drawElements(GLenum mode,GLsizei count,const GLushort* indices);
			virtual void drawElements(GLenum mode,GLsizei count,const GLuint* indices);

			const osg::Vec3d*         m_vertex3dArrayPtr;
		};

                class MyGeometryVisitor : public osg::NodeVisitor
		{
		public:
			MyGeometryVisitor(DoubleTriangleFunctor<ModelTriangleFunctor>* tf);
                        //virtual void apply(osg::Geometry& geometry);
                        virtual void apply(osg::IVBF_SGNodeGeometry& geometry);
		private:
			DoubleTriangleFunctor<ModelTriangleFunctor>* m_triangleFunctor;
		};

		COctreeTriangleSelector();

		~COctreeTriangleSelector();

		SOctreeNode* Root;

                void ConstructTriangleOctree(std::list<triangle3d> triangles,int minimalPolysPerNode);
                void ConstructTriangleOctree(const osg::IVBF_SGNodeGroup & triangleNode);
		void ConstructTriangleOctree(osg::Drawable* pDrawable);
                bool ConstructTriangleOctree(osg::IVBF_SGNode* n,osg::Matrix sm,int minimalPolysPerNode = 100);
		bool ConstructTriangleOctreeFromFile(std::fstream& fs);
		void ConstructTriangleOctreeFromFileImp(std::fstream& fs,SOctreeNode* node);
		void ConstructOctree(SOctreeNode* node,int minimalPolysPerNode);
		void constructOctree(SOctreeNode* node,int minimalPolysPerNode);
		int GetTriangleCount();
		void GetTrianglesFromOctree(
			SOctreeNode* node, int& trianglesWritten,
			int maximumSize, const aabbox3d& box,
			osg::Matrixd mat, std::list<triangle3d>& triangles);

	protected:
		int TotalTriangleCount;
	};

	const float ROUNDING_ERROR_f32 = 0.000001f;
        class CSceneCollisionManager
	{
	public:
		CSceneCollisionManager(){};
		~CSceneCollisionManager(){};
		struct SCollisionData
		{
			osg::Vec3d eRadius;

			osg::Vec3d R3Velocity;
			osg::Vec3d R3Position;

			osg::Vec3d velocity;
			osg::Vec3d normalizedVelocity;
			osg::Vec3d basePoint;

			bool foundCollision;
			double nearestDistance;
			osg::Vec3d intersectionPoint;

			triangle3d intersectionTriangle;
			double triangleIndex;
			double triangleHits;

			double slidingSpeed;

			COctreeTriangleSelector* selector;
		};

		//#if     !defined(_M_IA64) 
		//		inline double fabsf(__in double _X)
		//		{return ((double)fabs((double)_X)); }
		//#endif

		inline bool iszero(const double a, const double tolerance = ROUNDING_ERROR_f32)
		{
			return fabsf(a) <= tolerance;
		}
		inline const double clamp (const double& value, const double& low, const double& high)
		{
			return min(max(value,low), high);
		}
		inline bool getLowestRoot(double a, double b, double c, double maxR, double* root)
		{
			double determinant = b*b - 4.0f*a*c;

			if (determinant < 0.0f) return false;

			double sqrtD = (double)sqrt(determinant);

			double r1 = (-b - sqrtD) / (2*a);
			double r2 = (-b + sqrtD) / (2*a);

			if (r1 > r2) { double tmp=r2; r2=r1; r1=tmp; }

			if (r1 > 0 && r1 < maxR)
			{
				*root = r1;
				return true;
			}

			if (r2 > 0 && r2 < maxR)
			{
				*root = r2;
				return true;
			}

			return false;
		}
		osg::Vec3d getCollisionResultPosition(
			COctreeTriangleSelector* selector,
			const osg::Vec3d& position, const osg::Vec3d& radius,
			const osg::Vec3d& direction,
			triangle3d& triout,
			osg::Vec3d& hitPosition,
			bool& outFalling,
			double slidingSpeed,
			const osg::Vec3d& gravity,
			bool& foundCollision);
		osg::Vec3d getCollisionResultPositionWithModel(
			COctreeTriangleSelector* selector,
			const osg::Vec3d& position, const osg::Vec3d& radius,
			const osg::Vec3d& direction,
			triangle3d& triout,
			osg::Vec3d& hitPosition,
			bool& outFalling,
			double slidingSpeed,
			const osg::Vec3d& gravity,
			bool& foundCollision);
	private:
		osg::Vec3d collideEllipsoidWithWorld(
			COctreeTriangleSelector* selector,
			const osg::Vec3d& position,
			const osg::Vec3d& radius,  
			const osg::Vec3d& velocity,
			double slidingSpeed,
			const osg::Vec3d& gravity,
			triangle3d& triout,
			osg::Vec3d& hitPosition,
			bool& outFalling,
			bool& foundCollision);
		osg::Vec3d collideEllipsoidWithModel(
			COctreeTriangleSelector* selector,
			const osg::Vec3d& position,
			const osg::Vec3d& radius,  
			const osg::Vec3d& velocity,
			double slidingSpeed,
			const osg::Vec3d& gravity,
			triangle3d& triout,
			osg::Vec3d& hitPosition,
			bool& outFalling,
			bool& foundCollision);
		osg::Vec3d collideWithWorld(
			double recursionDepth,
			SCollisionData &colData, 
			osg::Vec3d pos, 
			osg::Vec3d vel,
			bool& foundCollision);
		osg::Vec3d collideWithModel(
			double recursionDepth,
			SCollisionData &colData, 
			osg::Vec3d pos, 
			osg::Vec3d vel,
			bool& foundCollision);
		bool testTriangleIntersection(SCollisionData* colData,
			triangle3d& triangle);
		bool testTriangleIntersectionWithModel(SCollisionData* colData,
			triangle3d& triangle);

	};
}


#endif //FE_INTERSECT_MATH_UTIL_H
