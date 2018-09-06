#ifndef OSGEARTH_REVISIONING_H
#define OSGEARTH_REVISIONING_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <OpenThreads/Atomic>
#include <VBF_Base/observer_ptr>
#include <vector>

namespace osgEarth
{
	// �޶������ɸ��ٵģ�
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



    // ���޶�����Ļ��࣬һ�����޶��������ͨ���汾�ų�����������״̬�� ��ˣ��ܹ��ж�״̬�Ƿ������µģ���ͬ������ģ�͡�
	// ע�⣺Revisioned���ڶ���������һ�������״̬����֮��һ��������ٶ�������״̬��ʹ��TrackDirty  
    class Revisioned
    {
    public:
		// ͨ�����Ӱ汾�ŰѶ����ʶΪdirty����������и�����Ҳ���ᱻ��ʶΪdirty
        void dirty() { ++_revision; }

		// ���ⲿ�汾��ͬ��Ϊ������İ汾�ţ�effectively bringing the external object up to date.
        virtual void sync( Revision& externalRevision ) const
        {
            externalRevision = _revision;
        }

		// externalRevision�Ƿ��뱾����ͬ��
        bool outOfSyncWith( const Revision& externalRevision) const
        {
            return !inSyncWith( externalRevision );
        }

		// externalRevision�Ƿ��뱾����ͬ��
        virtual bool inSyncWith( const Revision& externalRevision ) const
        {
            return _alwaysDirty ? false : _revision == externalRevision;
        }

    protected:
        Revisioned() : _alwaysDirty(false) { }

        virtual ~Revisioned() { }

        // �Ѹö������Ǳ��Ϊdirty��inSyncWith()���Ƿ���false
        void setAlwaysDirty( bool value )
        {
            _alwaysDirty = value;
        }

    private:
        Revision _revision;
        bool     _alwaysDirty;
    };


   // һ��TrackedMutable������һ�����Ա�Ǳ���Ķ��󣬲���ѡ���Ե����ò�Ӱ�����ĸ�ĸ��������"dirtyBound"����������ϴ���
    class OSGEARTH_EXPORT DirtyNotifier
    {
    public:
        DirtyNotifier();
        virtual ~DirtyNotifier() { }

		// ���ö���Ϊdirty����֪ͨ������
        virtual void setDirty();

		// ���ö���Ϊnot dirty
        virtual void resetDirty() { m_ipDirtyCounter->m_nCount = 0; }

		// �����Ƿ�Ϊdirty
        virtual bool isDirty() const { return m_ipDirtyCounter->m_nCount > 0; }


		// ���/�Ƴ�һ�������ĸ����󣬱���������Ϊdirty����ô����ĸ�����Ҳ������Ϊdirty
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



    // һ���򵥵��̰߳�ȫ��"dirty"����ֻ֧��һ���ͻ���client��
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
