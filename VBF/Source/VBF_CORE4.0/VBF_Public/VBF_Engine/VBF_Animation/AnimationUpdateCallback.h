#ifndef OSGANIMATION_ANIMATION_UPDATE_CALLBACK
#define OSGANIMATION_ANIMATION_UPDATE_CALLBACK 1

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_Animation/Channel>
#include <VBF_Engine/VBF_Animation/Animation>
#include <string>

namespace osgAnimation 
{

    class AnimationUpdateCallbackBase : public virtual osg::CVBF_Object
    {
    public:
		// 链接一个频道
        virtual bool link(Channel* channel) = 0;
		// 链接一个动画体对象并返回已经链接的频道数
        virtual int  link(Animation* animation) = 0;
    };


    template <class T>
    class AnimationUpdateCallback : public AnimationUpdateCallbackBase, public T
    {
    public:
        AnimationUpdateCallback() {}
        AnimationUpdateCallback(const std::string& name) { T::setName(name);}
        AnimationUpdateCallback(const AnimationUpdateCallback& apc,const osg::CopyOp& copyop): T(apc, copyop) {}

        META_Object(osgAnimation, AnimationUpdateCallback<T>);

        const std::string& getName() const { return T::getName(); }
        bool link(Channel* channel) { return 0; }
        int link(Animation* animation)
        {
            if (T::getName().empty())
            {
                osg::notify(osg::WARN) << "An update callback has no name, it means it could link only with \"\" named Target, often an error, discard" << std::endl;
                return 0;
            }
            int nbLinks = 0;
            for (ChannelList::iterator it = animation->getChannels().begin(); it != animation->getChannels().end(); ++it)
            {
                std::string targetName = (*it)->getTargetName();
                if (targetName == T::getName())
                {
                    AnimationUpdateCallbackBase* a = this;
                    a->link((*it).get());
                    nbLinks++;
                }
            }
            return nbLinks;
        }
    };

}

#endif
