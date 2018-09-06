#ifndef OSGPARTICLE_DOMAINOPERATOR
#define OSGPARTICLE_DOMAINOPERATOR

#include <Types/VBF_Plane.h>
#include <VBF_Engine/VBF_Particle/VBF_PSOperator.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

namespace osgParticle
{

// ��������������ܲ�ͬ��������״��Ϊ����������������ʵ�������������ཻ�Ĳ������μ�David McAllister������ϵͳAPI (http://www.particlesystems.org)
class OSGPARTICLE_EXPORT DomainOperator : public Operator
{
public:
    struct Domain
    {
        enum Type
        {
            UNDEFINED_DOMAIN = 0,
            POINT_DOMAIN,
            LINE_DOMAIN,
            TRI_DOMAIN,
            RECT_DOMAIN,
            PLANE_DOMAIN,
            SPHERE_DOMAIN,
            BOX_DOMAIN,
            DISK_DOMAIN
        };
        
        Domain( Type t ) : r1(0.0f), r2(0.0f), type(t) {}
        osg::Plane plane;
        osg::Vec3 v1;
        osg::Vec3 v2;
        osg::Vec3 v3;
        osg::Vec3 s1;
        osg::Vec3 s2;
        float r1;
        float r2;
        Type type;
    };
    
    DomainOperator() : Operator() {}
    
    DomainOperator( const DomainOperator& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY )
    : Operator(copy, copyop), _domains(copy._domains), _backupDomains(copy._backupDomains)
    {}
    
    META_Object( osgParticle, DomainOperator );
    
    // ���һ��������
    inline void addPointDomain( const osg::Vec3& p );
    inline void addLineSegmentDomain( const osg::Vec3& v1, const osg::Vec3& v2 );
    inline void addTriangleDomain( const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3 );
    inline void addRectangleDomain( const osg::Vec3& corner, const osg::Vec3& w, const osg::Vec3& h );
    inline void addPlaneDomain( const osg::Plane& plane );
    inline void addSphereDomain( const osg::Vec3& c, float r );
    inline void addBoxDomain( const osg::Vec3& min, const osg::Vec3& max );
    inline void addDiskDomain( const osg::Vec3& c, const osg::Vec3& n, float r1, float r2=0.0f );
    
    // ֱ�����һ��������󡣱�.osg wrappers��serializers����
    void addDomain( const Domain& domain ) { _domains.push_back(domain); }
    
    // ֱ�ӻ�ȡһ��������󡣱�.osg wrappers��serializers����
    const Domain& getDomain( unsigned int i ) const { return _domains[i]; }
    
    // �Ƴ�һ������
    void removeDomain( unsigned int i )
    { if (i<_domains.size()) _domains.erase(_domains.begin() + i); }
    
    // �Ƴ����е�����
    void removeAllDomains() { _domains.clear(); }
    
    // ��ȡ���������
    unsigned int getNumDomains() const { return _domains.size(); }
    
	// ������Ӧ�ü��ٶȣ���Ҫ�ֹ����ø÷���
    void operate( Particle* P, double dt );
    
    // ִ��һЩ��ʼ����������Ҫ�ֹ����ø÷���
    void beginOperate( Program* prg );
    
	// ִ��һЩ���ڲ�������Ҫ�ֹ����ø÷���
    void endOperate();
    
protected:
    virtual ~DomainOperator() {}
    DomainOperator& operator=( const DomainOperator& ) { return *this; }
    
    virtual void handlePoint( const Domain& domain, Particle* P, double dt ) { ignore("Point"); }
    virtual void handleLineSegment( const Domain& domain, Particle* P, double dt ) { ignore("LineSegment"); }
    virtual void handleTriangle( const Domain& domain, Particle* P, double dt ) { ignore("Triangle"); }
    virtual void handleRectangle( const Domain& domain, Particle* P, double dt ) { ignore("Rectangle"); }
    virtual void handlePlane( const Domain& domain, Particle* P, double dt ) { ignore("Plane"); }
    virtual void handleSphere( const Domain& domain, Particle* P, double dt ) { ignore("Sphere"); }
    virtual void handleBox( const Domain& domain, Particle* P, double dt ) { ignore("Box"); }
    virtual void handleDisk( const Domain& domain, Particle* P, double dt ) { ignore("Disk"); }
    
    inline void computeNewBasis( const osg::Vec3&, const osg::Vec3&, osg::Vec3&, osg::Vec3& );
    inline void ignore( const std::string& func );
    
    std::vector<Domain> _domains;
    std::vector<Domain> _backupDomains;
};

// INLINE METHODS

inline void DomainOperator::addPointDomain( const osg::Vec3& p )
{
    Domain domain( Domain::POINT_DOMAIN );
    domain.v1 = p;
    _domains.push_back( domain );
}

inline void DomainOperator::addLineSegmentDomain( const osg::Vec3& v1, const osg::Vec3& v2 )
{
    Domain domain( Domain::LINE_DOMAIN );
    domain.v1 = v1;
    domain.v2 = v2;
    domain.r1 = (v2 - v1).length();
    _domains.push_back( domain );
}

inline void DomainOperator::addTriangleDomain( const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3 )
{
    Domain domain( Domain::TRI_DOMAIN );
    domain.v1 = v1;
    domain.v2 = v2;
    domain.v3 = v3;
    domain.plane.set(v1, v2, v3);
    computeNewBasis( v2-v1, v3-v1, domain.s1, domain.s2 );
    _domains.push_back( domain );
}

inline void DomainOperator::addRectangleDomain( const osg::Vec3& corner, const osg::Vec3& w, const osg::Vec3& h )
{
    Domain domain( Domain::RECT_DOMAIN );
    domain.v1 = corner;
    domain.v2 = w;
    domain.v3 = h;
    domain.plane.set(corner, corner+w, corner+h);
    computeNewBasis( w, h, domain.s1, domain.s2 );
    _domains.push_back( domain );
}

inline void DomainOperator::addPlaneDomain( const osg::Plane& plane )
{
    Domain domain( Domain::PLANE_DOMAIN );
    domain.plane.set(plane);
    _domains.push_back( domain );
}

inline void DomainOperator::addSphereDomain( const osg::Vec3& c, float r )
{
    Domain domain( Domain::SPHERE_DOMAIN );
    domain.v1 = c;
    domain.r1 = r;
    _domains.push_back( domain );
}

inline void DomainOperator::addBoxDomain( const osg::Vec3& min, const osg::Vec3& max )
{
    Domain domain( Domain::BOX_DOMAIN );
    domain.v1 = min;
    domain.v2 = max;
    _domains.push_back( domain );
}

inline void DomainOperator::addDiskDomain( const osg::Vec3& c, const osg::Vec3& n, float r1, float r2 )
{
    Domain domain( Domain::DISK_DOMAIN );
    domain.v1 = c;
    domain.v2 = n;
    domain.r1 = r1;
    domain.r2 = r2;
    domain.plane.set(n, c);
    _domains.push_back( domain );
}

inline void DomainOperator::computeNewBasis( const osg::Vec3& u, const osg::Vec3& v, osg::Vec3& s1, osg::Vec3& s2 )
{
    // Copied from David McAllister's Particle System API (http://www.particlesystems.org), pDomain.h
    osg::Vec3 w = u ^ v;
    float det = w.z()*u.x()*v.y() - w.z()*u.y()*v.x() - u.z()*w.x()*v.y() -
                u.x()*v.z()*w.y() + v.z()*w.x()*u.y() + u.z()*v.x()*w.y();
    det = 1.0f / det;
    
    s1.set( v.y()*w.z() - v.z()*w.y(), v.z()*w.x() - v.x()*w.z(), v.x()*w.y() - v.y()*w.x() );
    s1 = s1 * det;
    s2.set( u.y()*w.z() - u.z()*w.y(), u.z()*w.x() - u.x()*w.z(), u.x()*w.y() - u.y()*w.x() );
    s2 = s2 * (-det);
}

inline void DomainOperator::ignore( const std::string& func )
{
    OSG_NOTICE << className() << ": " << func << " domain not yet implemented. " << std::endl;
}


}

#endif
