#ifndef OSGEARTH_STATE_SET_CACHE_H
#define OSGEARTH_STATE_SET_CACHE_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <set>

namespace osgEarth
{
	// 状态集的缓存
    class OSGEARTH_EXPORT StateSetCache : public ::CVBF_Referenced
    {
    public:
        StateSetCache() { }
        virtual ~StateSetCache() { }

		// 检查一个状态集是否适合共享
        bool eligible( osg::StateSet* stateSet ) const;

		// 检查一个状态属性是否适合共享
        bool eligible( osg::StateAttribute* attr ) const;

		// 遍历节点，优化等价的状态集
        void optimize( osg::IVBF_SGNode* node );

		// 在缓存中查找与输入的状态集匹配的，如果找到在输出中返回，如果找不到把输入的状态集放在缓存中，并在输出中返回
		// 使用智能指针，以保证线程安全
        bool share( ref_ptr<osg::StateSet>& input, ref_ptr<osg::StateSet>& output, bool checkEligible =true );

		// 在缓存中查找与输入的属性匹配的，如果找到在输出中返回，如果找不到把输入的属性放在缓存中，并在输出中返回
		// 使用智能指针，以保证线程安全
        bool share( ref_ptr<osg::StateAttribute>& input, ref_ptr<osg::StateAttribute>& output,bool checkEligible =true );

		// 缓存中状态集的数量
        unsigned size() const { return _stateSetCache.size(); }

		// 清空缓存
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
