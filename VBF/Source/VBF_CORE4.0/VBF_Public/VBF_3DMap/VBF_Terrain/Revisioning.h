#ifndef OSGEARTH_REVISIONING_H
#define OSGEARTH_REVISIONING_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <OpenThreads/Atomic>
#include <VBF_Base/observer_ptr>
#include <vector>

namespace osgEarth
{
	// 修订本（可跟踪的）
    struct Revision
    {
        Revision() : _value(-1) { }
        Revision(int init) : _value(init) { }

        void reset() { _value = -1; }

        operator int() const { return _value; }

        int operator ++() { return ++_value; }
        int operator --() { return --_value; }
    private:
        int _value;
    };



    // 可修订对象的基类，一个可修订对象可以通过版本号持续跟踪它的状态。 因此，能够判断状态是否是最新的，并同步数据模型。
	// 注意：Revisioned用于多个对象跟踪一个对象的状态；反之，一个对象跟踪多个对象的状态则使用TrackDirty  
    class Revisioned
    {
    public:
		// 通过增加版本号把对象标识为dirty，如果对象有父对象，也将会被标识为dirty
        void dirty() { ++_revision; }

		// 把外部版本号同步为本对象的版本号，effectively bringing the external object up to date.
        virtual void sync( Revision& externalRevision ) const
        {
            externalRevision = _revision;
        }

		// externalRevision是否与本对象不同步
        bool outOfSyncWith( const Revision& externalRevision) const
        {
            return !inSyncWith( externalRevision );
        }

		// externalRevision是否与本对象同步
        virtual bool inSyncWith( const Revision& externalRevision ) const
        {
            return _alwaysDirty ? false : _revision == externalRevision;
        }

    protected:
        Revisioned() : _alwaysDirty(false) { }

        virtual ~Revisioned() { }

        // 把该对象总是标记为dirty，inSyncWith()总是返回false
        void setAlwaysDirty( bool value )
        {
            _alwaysDirty = value;
        }

    private:
        Revision _revision;
        bool     _alwaysDirty;
    };


   // 一个TrackedMutable对象是一个可以标记本身的对象，并可选择性的设置并影响它的父母，近似于"dirtyBound"概念，可以向上传导
    class OSGEARTH_EXPORT DirtyNotifier
    {
    public:
        DirtyNotifier();
        virtual ~DirtyNotifier() { }

		// 设置对象为dirty，并通知父对象
        virtual void setDirty();

		// 设置对象为not dirty
        virtual void resetDirty() { m_ipDirtyCounter->m_nCount = 0; }

		// 对象是否为dirty
        virtual bool isDirty() const { return m_ipDirtyCounter->m_nCount > 0; }


		// 添加/移除一个从属的父对象，本对象被设置为dirty，则该从属的父对象也被设置为dirty
        virtual void addParent( DirtyNotifier* parent );
        virtual void removeParent( DirtyNotifier* parent );

    private:
        // this pattern is used to we can track parents with an observer pointer.
        struct DirtyCounter : public ::CVBF_Referenced
        {
            DirtyCounter(DirtyNotifier* owner) : _owner(owner), m_nCount(1) { }
            DirtyNotifier* _owner;
            int            m_nCount;
            friend class DirtyNotifer;
        };
        ref_ptr<DirtyCounter>                     m_ipDirtyCounter;
        std::vector< observer_ptr<DirtyCounter> > _parents;
    };



    // 一个简单但线程安全的"dirty"对象，只支持一个客户（client）
    template<typename T>
    struct SimpleMutable
    {
        SimpleMutable() : m_bDirty(1) { }
        SimpleMutable(const T& value) : _value(value), m_bDirty(1) { }
        operator const T&() const { return _value; }
        const T* operator ->() const { return &_value; }
        SimpleMutable& operator = (const T& value) { _value = value; m_bDirty.exchange(1); return *this; }
        bool changed(bool reset=true) const { unsigned r = reset? m_bDirty.exchange(0) : (unsigned)m_bDirty; return r==1; }
        void clean() { m_bDirty.exchange(0); }
    private:
        T                           _value;
        mutable OpenThreads::Atomic m_bDirty;
    };

}

#endif // OSGEARTH_REVISIONING_H
