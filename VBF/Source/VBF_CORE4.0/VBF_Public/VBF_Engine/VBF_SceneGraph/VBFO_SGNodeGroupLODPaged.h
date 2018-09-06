#ifndef OSG_PagedLOD
#define OSG_PagedLOD 1

#include <VBF_Engine/VBF_SceneGraph/Export>

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODPaged.h>

namespace osg {

/** ��ҳLOD�ڵ㣺���÷�ҳ���ݿ�Ĺ��ܣ������ģ�����ݷ������ص�����ͼ���У���ΪPagedLOD ���ӽڵ㣩��
                �����ݵ�ǰ�Ŀ��ӷ�Χ����һ��ʱ�����޷���������PagedLOD�ӽڵ��޳�������ͼ�Σ��Խ�Լϵͳ��Դ��
				����û��ƶ����ӵ�֮�󣬱��޳��Ľڵ������½�����Ұ����ҳ���ݿ��߳̽����¼�������
*/

class OSG_EXPORT PagedLOD : public IVBF_SGNodeGroupLODImpl<IVBF_SGNodeGroupLODPaged>
{
	typedef IVBF_SGNodeGroupLODImpl<IVBF_SGNodeGroupLODPaged> BaseClass;
    public :
    
        PagedLOD();
        PagedLOD(const PagedLOD&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, PagedLOD);
        
        

        virtual void traverse(NodeVisitor& nv);
        
		// ���/�Ƴ��ӽڵ�
        virtual bool addChild(IVBF_SGNode *child);
        virtual bool addChild(IVBF_SGNode *child, float min, float max);
        virtual bool addChild(IVBF_SGNode *child, float min, float max,const std::string& filename, float priorityOffset=0.0f, float priorityScale=1.0f);
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove=1);


        // IE���ܴ���
        // �������ݿ�ѡ�װ���ӽڵ�ʱ�õ�
        void setDatabaseOptions(CVBF_Referenced* options) { _databaseOptions = options; }
        CVBF_Referenced* getDatabaseOptions() { return _databaseOptions.get(); }
        const CVBF_Referenced* getDatabaseOptions() const { return _databaseOptions.get(); }


        // �������ݿ�·�����ӽڵ���ļ�����filenames���ڴ�·����
        void setDatabasePath(const std::string& path);
        inline const std::string& getDatabasePath() const { return _databasePath; }

        
 
		// ����/��ȡ�ӽڵ���ļ���
        void setFileName(unsigned int childNo, const std::string& filename);
        const std::string& getFileName(unsigned int childNo) const ;
        unsigned int getNumFileNames() const { return _perRangeDataList.size(); }


		// ����/��ȡ�ӽڵ�����ȼ�
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
