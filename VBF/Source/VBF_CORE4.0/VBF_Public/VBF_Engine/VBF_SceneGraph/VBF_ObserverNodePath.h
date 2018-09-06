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

#ifndef OSG_OBSERVERNODEPATH
#define OSG_OBSERVERNODEPATH 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>
#include <VBF_Base/observer_ptr>
#include <vector>

namespace osg {

typedef std::vector< ref_ptr<osg::IVBF_SGNode> > RefNodePath;

// 节点路径观察者：跟踪CVBF_SGNodePath的变化，当节点被删除时自动使之失效

class OSG_EXPORT ObserverNodePath
{
    public:
        ObserverNodePath();

        ObserverNodePath(const ObserverNodePath& rhs);

        ObserverNodePath(const osg::CVBF_SGNodePath& nodePath);

        ~ObserverNodePath();

        ObserverNodePath& operator = (const ObserverNodePath& rhs);

        /** get the CVBF_SGNodePath from the first parental chain back to root, plus the specified node.*/
        void setNodePathTo(osg::IVBF_SGNode* node);

        void setNodePath(const osg::RefNodePath& nodePath);

        void setNodePath(const osg::CVBF_SGNodePath& nodePath);

        void clearNodePath();

        /** Get a thread safe RefNodePath, return true if CVBF_SGNodePath is valid.*/
        bool getRefNodePath(RefNodePath& refNodePath) const;

        /** Get a lightweight CVBF_SGNodePath that isn't thread safe but
          * may be safely used in single threaded applications, or when
          * its known that the CVBF_SGNodePath won't be invalidated during usage
          * of the CVBF_SGNodePath. return true if CVBF_SGNodePath is valid.*/
        bool getNodePath(osg::CVBF_SGNodePath& nodePath) const;

        bool empty() const
        {
            OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
            return _nodePath.empty();
        }

    protected:

        void _setNodePath(const osg::CVBF_SGNodePath& nodePath);
        void _clearNodePath();

        typedef std::vector< observer_ptr<osg::IVBF_SGNode> > ObsNodePath;
        mutable OpenThreads::Mutex      _mutex;
        ObsNodePath                     _nodePath;
};

}

#endif
