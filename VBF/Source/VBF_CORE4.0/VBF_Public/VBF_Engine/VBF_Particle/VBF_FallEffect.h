/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#ifndef OSGPARTICLE_PRECIPITATIONEFFECT
#define OSGPARTICLE_PRECIPITATIONEFFECT

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <Types/VBF_BoundingBox.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrFog.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

#include <VBF_Engine/VBF_SGUtil/CullVisitor>

#include <VBF_Engine/VBF_Particle/Export>

namespace osgParticle
{
    // 粒子系统效果，如雨效和雪效( [fall]∶从天而降;落下)
    class OSGPARTICLE_EXPORT FallEffect : public osg::IVBF_SGNodeImpl<IVBF_SGNode>
    {
    public:   
        FallEffect();
        FallEffect(const FallEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
	  
        META_Node(osgParticle, FallEffect);
	  
        virtual void traverse(osg::NodeVisitor& nv);
               
		// 设置创建指定强度的雨效的所有参数
        void rain(float intensity);
        
        // 设置创建指定强度的雪效的所有参数
        void snow(float intensity);
        
		// 设置/获取最大的粒子密度
        void setMaximumParticleDensity(float density) { if (m_fMaxParticleDensity==density) return;  m_fMaxParticleDensity = density; m_bDirty = true;}
        float getMaximumParticleDensity() const { return m_fMaxParticleDensity; }

		// 设置/获取风向量
        void setWind(const osg::Vec3& wind) { m_vWind = wind; }
        const osg::Vec3& getWind() const { return m_vWind; }
        
		// 设置/获取原点位置
        void setPosition(const osg::Vec3& position) { _origin = position; }
        const osg::Vec3& getPosition() const { return _origin; }
        
		// 设置/获取范围的大小
        void setCellSize(const osg::Vec3& cellSize) { if (m_vCellSize==cellSize) return; m_vCellSize = cellSize; m_bDirty = true; }
        const osg::Vec3& getCellSize() const { return m_vCellSize; }
        
		// 设置/获取粒子的速度
        void setParticleSpeed(float particleSpeed) { if (m_fParticleSpeed==particleSpeed) return; m_fParticleSpeed = particleSpeed; m_bDirty = true; }
        float getParticleSpeed() const { return m_fParticleSpeed; }

		// 设置/获取粒子的大小
        void setParticleSize(float particleSize) { if (m_fParticleSize==particleSize) return; m_fParticleSize = particleSize; m_bDirty = true;}
        float getParticleSize() const { return m_fParticleSize; }
        
		// 设置/获取粒子的颜色
        void setParticleColor(const osg::Vec4& color) { if (m_vParticleColor==color) return; m_vParticleColor = color; m_bDirty = true;}
        const osg::Vec4& getParticleColor() const { return m_vParticleColor; }
        
		// 
        void setNearTransition(float nearTransition) { m_fNearTransition = nearTransition; }
        float getNearTransition() const { return m_fNearTransition; }

        void setFarTransition(float farTransition) { m_fFarTransition = farTransition; }
        float getFarTransition() const { return m_fFarTransition; }
        
        void setUseFarLineSegments(bool useFarLineSegments) { m_bUseFarLineSegments = useFarLineSegments; }
        bool getUseFarLineSegments() const { return m_bUseFarLineSegments; }

		// 设置/获取雾
        void setFog(osg::Fog* fog) { m_Fog = fog; }
        osg::Fog* getFog() { return m_Fog.get(); }
        const osg::Fog* getFog() const { return m_Fog.get(); }
        
        osg::Geometry* getQuadGeometry() { return _quadGeometry.get(); }
        osg::StateSet* getQuadStateSet() { return _quadStateSet.get(); }
        
        osg::Geometry* getLineGeometry() { return _lineGeometry.get(); }
        osg::StateSet* getLineStateSet() { return _lineStateSet.get(); }
        
        osg::Geometry* getPointGeometry() { return _pointGeometry.get(); }
        osg::StateSet* getPointStateSet() { return _pointStateSet.get(); }

        // 用于渲染cells的Drawable
        class OSGPARTICLE_EXPORT FallDrawable : public osg::Drawable
        {
        public:

            FallDrawable();
            FallDrawable(const FallDrawable& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

            META_Object(osgParticle, FallDrawable);

            virtual bool supports(const osg::PrimitiveFunctor&) const { return false; }
            virtual void accept(osg::PrimitiveFunctor&) const {}
            virtual bool supports(const osg::PrimitiveIndexFunctor&) const { return false; }
            virtual void accept(osg::PrimitiveIndexFunctor&) const {}

            void setRequiresPreviousMatrix(bool flag) { _requiresPreviousMatrix = flag; }
            bool getRequiresPreviousMatrix() const { return _requiresPreviousMatrix; }

            void setGeometry(osg::Geometry* geom) { _geometry = geom; }
            osg::Geometry* getGeometry() { return _geometry.get(); }
            const osg::Geometry* getGeometry() const { return _geometry.get(); }
            
            void setDrawType(GLenum type) { _drawType = type; }
            GLenum getDrawType() const { return _drawType; }
            
            void setNumberOfVertices(unsigned int numVertices) { _numberOfVertices = numVertices; }
            unsigned int getNumberOfVertices() const { return _numberOfVertices; }

            virtual void drawImplementation(osg::RenderInfo& renderInfo) const;

            struct Cell
            {
                Cell(int in_i, int in_j, int in_k): i(in_i), j(in_j), k(in_k) {}
                inline bool operator < (const Cell& rhs) const
                {
                    if (i<rhs.i) return true;
                    if (i>rhs.i) return false;
                    if (j<rhs.j) return true;
                    if (j>rhs.j) return false;
                    if (k<rhs.k) return true;
                    if (k>rhs.k) return false;
                    return false;
                }
                int i;
                int j;
                int k;
            };
            
            struct DepthMatrixStartTime
            {
                inline bool operator < (const DepthMatrixStartTime& rhs) const
                {
                    return depth < rhs.depth;
                }          
                float           depth;
                float           startTime;
                osg::Matrix     modelview;
            };

            typedef std::map< Cell, DepthMatrixStartTime >  CellMatrixMap;

            struct LessFunctor 
            {
                inline bool operator () (const CellMatrixMap::value_type* lhs,const CellMatrixMap::value_type* rhs) const
                {
                    return (*lhs).second<(*rhs).second; 
                }
            };


            CellMatrixMap& getCurrentCellMatrixMap() { return _currentCellMatrixMap; }
            CellMatrixMap& getPreviousCellMatrixMap() { return _previousCellMatrixMap; }

            inline void newFrame()
            {
                _previousCellMatrixMap.swap(_currentCellMatrixMap);
                _currentCellMatrixMap.clear();
            }

        protected:

            virtual ~FallDrawable() {}

            bool _requiresPreviousMatrix;

            ref_ptr<osg::Geometry> _geometry;

            mutable CellMatrixMap _currentCellMatrixMap;
            mutable CellMatrixMap _previousCellMatrixMap;
            
            GLenum          _drawType;
            unsigned int    _numberOfVertices;

        };




    protected:
        virtual ~FallEffect() {}
        
        void compileGLObjects(osg::RenderInfo& renderInfo) const;
        void update();  
        void createGeometry(unsigned int numParticles, osg::Geometry* quad_geometry,
                            osg::Geometry* line_geometry, osg::Geometry* point_geometry);
                    
        void setUpGeometries(unsigned int numParticles);


        struct FallDrawableSet
        {
            ref_ptr<FallDrawable> m_ipDrawableQuad;
            ref_ptr<FallDrawable> m_ipDrawableLine;
            ref_ptr<FallDrawable> m_ipDrawablePoint;
        };
        
        void cull(FallDrawableSet& pds, osgUtil::CullVisitor* cv) const;
        bool build(const osg::Vec3 eyeLocal, int i, int j, int k, float startTime, FallDrawableSet& pds, osg::Polytope& frustum, osgUtil::CullVisitor* cv) const;

        bool                        m_bDirty;
        osg::Vec3                   m_vWind;
        float                       m_fParticleSpeed;
        float                       m_fParticleSize;
        osg::Vec4                   m_vParticleColor;
        float                       m_fMaxParticleDensity;
        osg::Vec3                   m_vCellSize;
        float                       m_fNearTransition;
        float                       m_fFarTransition;
        bool                        m_bUseFarLineSegments;
        ref_ptr<osg::Fog>      m_Fog;

        ref_ptr<osg::Uniform>  _inversePeriodUniform;
        ref_ptr<osg::Uniform>  _particleSizeUniform;
        ref_ptr<osg::Uniform>  _particleColorUniform;

        typedef std::pair< osg::NodeVisitor*, osg::CVBF_SGNodePath > ViewIdentifier;
        typedef std::map< ViewIdentifier, FallDrawableSet >  ViewDrawableMap;

        OpenThreads::Mutex _mutex;
        ViewDrawableMap _viewDrawableMap;
        
        // 根据距离不同，采用不同的几何体，近处用四边形，远处用线或点
        ref_ptr<osg::Geometry> _quadGeometry;
        ref_ptr<osg::StateSet> _quadStateSet;

        ref_ptr<osg::Geometry> _lineGeometry;
        ref_ptr<osg::StateSet> _lineStateSet;

        ref_ptr<osg::Geometry> _pointGeometry;
        ref_ptr<osg::StateSet> _pointStateSet;

        // cache variables.
        float       m_fPeriod;
        osg::Vec3   _origin;
        osg::Vec3   _du;
        osg::Vec3   _dv;
        osg::Vec3   _dw;
        osg::Vec3   _inverse_du;
        osg::Vec3   _inverse_dv;
        osg::Vec3   _inverse_dw;

        double      _previousFrameTime;

    };

}

#endif
