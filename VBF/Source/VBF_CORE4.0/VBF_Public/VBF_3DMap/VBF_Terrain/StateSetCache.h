#ifndef OSGEARTH_STATE_SET_CACHE_H
#define OSGEARTH_STATE_SET_CACHE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <set>

namespace osgEarth
{
	// ״̬���Ļ���
    class OSGEARTH_EXPORT StateSetCache : public ::CVBF_Referenced
    {
    public:
        StateSetCache() { }
        virtual ~StateSetCache() { }

		// ���һ��״̬���Ƿ��ʺϹ���
        bool eligible( osg::StateSet* stateSet ) const;

		// ���һ��״̬�����Ƿ��ʺϹ���
        bool eligible( osg::StateAttribute* attr ) const;

		// �����ڵ㣬�Ż��ȼ۵�״̬��
        void optimize( osg::IVBF_SGNode* node );

		// �ڻ����в����������״̬��ƥ��ģ�����ҵ�������з��أ�����Ҳ����������״̬�����ڻ����У���������з���
		// ʹ������ָ�룬�Ա�֤�̰߳�ȫ
        bool share( ref_ptr<osg::StateSet>& input, ref_ptr<osg::StateSet>& output, bool checkEligible =true );

		// �ڻ����в��������������ƥ��ģ�����ҵ�������з��أ�����Ҳ�������������Է��ڻ����У���������з���
		// ʹ������ָ�룬�Ա�֤�̰߳�ȫ
        bool share( ref_ptr<osg::StateAttribute>& input, ref_ptr<osg::StateAttribute>& output,bool checkEligible =true );

		// ������״̬��������
        unsigned size() const { return _stateSetCache.size(); }

		// ��ջ���
        void clear();

    protected: 
        struct CompareStateSets 
		{
            bool operator()( const ref_ptr<osg::StateSet>& lhs, const ref_ptr<osg::StateSet>& rhs) const 
			{
                    return lhs->compare(*(rhs.get()), true) < 0;
            }
        };
        typedef std::set< ref_ptr<osg::StateSet>, CompareStateSets> StateSetSet;
        StateSetSet _stateSetCache;

        struct CompareStateAttributes 
		{
            bool operator()( const ref_ptr<osg::StateAttribute>& lhs, const ref_ptr<osg::StateAttribute>& rhs) const 
			{
                    return lhs->compare(*rhs.get()) < 0;
            }
        };
        typedef std::set< ref_ptr<osg::StateAttribute>, CompareStateAttributes> StateAttributeSet;
        StateAttributeSet _stateAttributeCache;

        mutable CVBF_Mutex _mutex;
    };
}

#endif // OSGEARTH_STATE_SET_CACHE_H
