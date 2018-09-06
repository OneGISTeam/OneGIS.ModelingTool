#ifndef OSG_PagedLOD
#define OSG_PagedLOD 1

#include <VBF_Engine/VBF_SceneGraph/Export>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODPaged.h>

namespace osg {

/** 分页LOD节点：运用分页数据库的功能，将多个模型数据分批加载到场景图形中（作为PagedLOD 的子节点）；
                并根据当前的可视范围，将一段时间内无法被看到的PagedLOD子节点剔除出场景图形，以节约系统资源；
				如果用户移动了视点之后，被剔除的节点又重新进入视野，分页数据库线程将重新加载它。
*/

class OSG_EXPORT PagedLOD : public IVBF_SGNodeGroupLODImpl<IVBF_SGNodeGroupLODPaged>
{
	typedef IVBF_SGNodeGroupLODImpl<IVBF_SGNodeGroupLODPaged> BaseClass;
    public :
    
        PagedLOD();
        PagedLOD(const PagedLOD&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, PagedLOD);
        
        

        virtual void traverse(NodeVisitor& nv);
        
		// 添加/移除子节点
        virtual bool addChild(IVBF_SGNode *child);
        virtual bool addChild(IVBF_SGNode *child, float min, float max);
        virtual bool addChild(IVBF_SGNode *child, float min, float max,const std::string& filename, float priorityOffset=0.0f, float priorityScale=1.0f);
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove=1);


        // IE可能错误
        // 设置数据库选项，装载子节点时用到
        void setDatabaseOptions(CVBF_Referenced* options) { _databaseOptions = options; }
        CVBF_Referenced* getDatabaseOptions() { return _databaseOptions.get(); }
        const CVBF_Referenced* getDatabaseOptions() const { return _databaseOptions.get(); }


        // 设置数据库路径。子节点的文件名（filenames）在此路径下
        void setDatabasePath(const std::string& path);
        inline const std::string& getDatabasePath() const { return _databasePath; }

        
 
		// 设置/获取子节点的文件名
        void setFileName(unsigned int childNo, const std::string& filename);
        const std::string& getFileName(unsigned int childNo) const ;
        unsigned int getNumFileNames() const { return _perRangeDataList.size(); }


		// 设置/获取子节点的优先级
        void setPriorityOffset(unsigned int childNo, float priorityOffset) { expandPerRangeDataTo(childNo); _perRangeDataList[childNo]._priorityOffset=priorityOffset; }
        float getPriorityOffset(unsigned int childNo) const { return _perRangeDataList[childNo]._priorityOffset; }
        unsigned int getNumPriorityOffsets() const { return _perRangeDataList.size(); }


        void setPriorityScale(unsigned int childNo, float priorityScale) { expandPerRangeDataTo(childNo); _perRangeDataList[childNo]._priorityScale=priorityScale; }
        float getPriorityScale(unsigned int childNo) const { return _perRangeDataList[childNo]._priorityScale; }
        unsigned int getNumPriorityScales() const { return _perRangeDataList.size(); }


        void setTimeStamp(unsigned int childNo, double timeStamp) { expandPerRangeDataTo(childNo); _perRangeDataList[childNo]._timeStamp=timeStamp; }
        double getTimeStamp(unsigned int childNo) const { return _perRangeDataList[childNo]._timeStamp; }
        unsigned int getNumTimeStamps() const { return _perRangeDataList.size(); }

        void setFrameNumber(unsigned int childNo, unsigned int frameNumber) { expandPerRangeDataTo(childNo); _perRangeDataList[childNo]._frameNumber=frameNumber; }
        unsigned getFrameNumber(unsigned int childNo) const { return _perRangeDataList[childNo]._frameNumber; }
        unsigned int getNumFrameNumbers() const { return _perRangeDataList.size(); }




        /** Return the DatabaseRequest object used by the DatabasePager to keep track of file load requests 
          * being carried on behalf of the DatabasePager.
          * Note, in normal OSG usage you should not set this value yourself, as this will be managed by 
          * the osgDB::DatabasePager.*/
        ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) { return _perRangeDataList[childNo]._databaseRequest; }
        const ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) const { return _perRangeDataList[childNo]._databaseRequest; }


        /** Set the frame number of the last time that this PageLOD node was traversed.
          * Note, this frame number is automatically set by the traverse() method for all traversals (update, cull etc.). 
          */
        inline void setFrameNumberOfLastTraversal(unsigned int frameNumber) { _frameNumberOfLastTraversal=frameNumber; }
        inline unsigned int getFrameNumberOfLastTraversal() const { return _frameNumberOfLastTraversal; }


        /** Set the number of children that the PagedLOD must keep around, even if they are older than their expiry time.*/
        inline void setNumChildrenThatCannotBeExpired(unsigned int num) { _numChildrenThatCannotBeExpired = num; }
        unsigned int getNumChildrenThatCannotBeExpired() const { return _numChildrenThatCannotBeExpired; }

        /** Set wether you want to disable the paging in of external nodes.*/
        void setDisableExternalChildrenPaging(bool flag) { _disableExternalChildrenPaging = flag; }
        bool getDisableExternalChildrenPaging() const { return _disableExternalChildrenPaging; }



        /** Remove the children from the PagedLOD which haven't been visited since specified expiry time and expiry frame number.
          * The removed children are added to the removeChildren list passed into the method,
          * this allows the children to be deleted later at the caller's discretion.
          * Return true if children are removed, false otherwise. */
        virtual bool removeExpiredChildren(double expiryTime, unsigned int expiryFrame, NodeList& removedChildren);
        
		struct OSG_EXPORT PerRangeData
        {
            PerRangeData();
            PerRangeData(const PerRangeData& prd);
            PerRangeData& operator = (const PerRangeData& prd);

            std::string                     _filename;
            float                           _priorityOffset;
            float                           _priorityScale;
            double                          _timeStamp;
            unsigned int                    _frameNumber;
            unsigned int                    _frameNumberOfLastReleaseGLObjects;
            ref_ptr<CVBF_Referenced>   _databaseRequest;
        };

        typedef std::vector<PerRangeData> PerRangeDataList;

    protected :
    
        virtual ~PagedLOD();
        
        void expandPerRangeDataTo(unsigned int pos);

        ref_ptr<CVBF_Referenced> _databaseOptions;
        std::string         _databasePath;

        unsigned int        _frameNumberOfLastTraversal;
        unsigned int        _numChildrenThatCannotBeExpired;
        bool                _disableExternalChildrenPaging;

        PerRangeDataList    _perRangeDataList;
};

}

#endif
