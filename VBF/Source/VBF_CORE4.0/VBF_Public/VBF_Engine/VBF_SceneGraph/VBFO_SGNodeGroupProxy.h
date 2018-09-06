#ifndef OSG_ProxyNode
#define OSG_ProxyNode 1

#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>

namespace osg {

class IVBF_SGNodeGroupProxy : public IVBF_SGNodeGroup
{
public:
	IVBF_SGNodeGroupProxy(){}
	IVBF_SGNodeGroupProxy(const IVBF_SGNodeGroupProxy& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY):IVBF_SGNodeGroup(cs,copyop) {}
	inline explicit IVBF_SGNodeGroupProxy(bool threadSafeRefUnref):IVBF_SGNodeGroup(threadSafeRefUnref){}
   
    typedef osg::BoundingSphere::vec_type vec_type;
    typedef osg::BoundingSphere::value_type value_type;


	/** Set the database path to prepend to children's filenames.*/
	virtual void setDatabasePath(const std::string& path) =0;
	virtual const std::string& getDatabasePath() const =0;

	virtual void setFileName(unsigned int childNo, const std::string& filename) =0;
    virtual const std::string& getFileName(unsigned int childNo) const =0;
    virtual unsigned int getNumFileNames() const =0;

    virtual ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) =0;
    virtual const ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) const =0;


    /** Modes which control how the center of object should be determined when computed which child is active.*/
    enum CenterMode
    {
        USE_BOUNDING_SPHERE_CENTER,
        USER_DEFINED_CENTER
    };

    /** Set how the center of object should be determined when computed which child is active.*/
    virtual void setCenterMode(CenterMode mode)=0;
	virtual CenterMode getCenterMode() const=0;


	/** 代理对象的加载时机 */
	enum LoadingExternalReferenceMode
	{
		LOAD_IMMEDIATELY,                     // 立即加载
		DEFER_LOADING_TO_DATABASE_PAGER,      // 推迟加载
		NO_AUTOMATIC_LOADING                  // 不自动加载
	};

	/** 设置/获取代理对象的加载时机*/
	virtual void setLoadingExternalReferenceMode(LoadingExternalReferenceMode mode)=0;
	virtual LoadingExternalReferenceMode getLoadingExternalReferenceMode() const=0;

	/** Sets the object-space point which defines the center of the osg::ProxyNode.  
	center is affected by any transforms in the hierarchy above the osg::ProxyNode.*/
	virtual void setCenter(const Vec3& center)=0;

	/** return the ProxyNode center point. */
	virtual const vec_type& getCenter() const=0;


	/** Set the object-space reference radius of the volume enclosed by the ProxyNode. 
	* Used to determine the bounding sphere of the ProxyNode in the absence of any children.*/
	virtual void setRadius(value_type radius) =0;

	/** Get the object-space radius of the volume enclosed by the ProxyNode.*/
	virtual value_type getRadius() const=0;

};
/** 代理节点：就像网络上的代理服务器那样，使用代理节点可以指向某个已经存在的模型文件，并在需要的时候加载它。
*/
class OSG_EXPORT ProxyNode : public IVBF_SGNodeGroupImpl<IVBF_SGNodeGroupProxy>
{
    public :
    
        ProxyNode();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        ProxyNode(const ProxyNode&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, ProxyNode);
        


        virtual void traverse(NodeVisitor& nv);
       
        virtual bool addChild(IVBF_SGNode *child);
        virtual bool addChild(IVBF_SGNode *child, const std::string& filename);
        
        virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);



        /** Set the optional database osgDB::Options object to use when loaded children.*/
        void setDatabaseOptions(CVBF_Referenced* options) { _databaseOptions = options; }

        /** Get the optional database osgDB::Options object used when loaded children.*/
        CVBF_Referenced* getDatabaseOptions() { return _databaseOptions.get(); }

        /** Get the optional database osgDB::Options object used when loaded children.*/
        const CVBF_Referenced* getDatabaseOptions() const { return _databaseOptions.get(); }


        /** Set the database path to prepend to children's filenames.*/
        void setDatabasePath(const std::string& path);
        /** Get the database path used to prepend to children's filenames.*/
        inline const std::string& getDatabasePath() const { return _databasePath; }

        void setFileName(unsigned int childNo, const std::string& filename) { expandFileNameListTo(childNo); _filenameList[childNo].first=filename; }
        const std::string& getFileName(unsigned int childNo) const { return _filenameList[childNo].first; }
        unsigned int getNumFileNames() const { return _filenameList.size(); }

        /** Return the DatabaseRequest object used by the DatabasePager to keep track of file load requests 
          * being carried on behalf of the DatabasePager.
          * Note, in normal OSG usage you should not set this value yourself, as this will be managed by 
          * the osgDB::DatabasePager.*/
        ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) { return _filenameList[childNo].second; }
        
        /** Return the const DatabaseRequest object.*/ 
        const ref_ptr<CVBF_Referenced>& getDatabaseRequest(unsigned int childNo) const { return _filenameList[childNo].second; }


        /** Set how the center of object should be determined when computed which child is active.*/
        void setCenterMode(CenterMode mode) { _centerMode=mode; }
		CenterMode getCenterMode() const { return _centerMode; }
        
          /** 设置/获取代理对象的加载时机*/
        void setLoadingExternalReferenceMode(LoadingExternalReferenceMode mode) { _loadingExtReference=mode; }
        LoadingExternalReferenceMode getLoadingExternalReferenceMode() const { return _loadingExtReference; }

        /** Sets the object-space point which defines the center of the osg::ProxyNode.  
            center is affected by any transforms in the hierarchy above the osg::ProxyNode.*/
        inline void setCenter(const Vec3& center) { _centerMode=USER_DEFINED_CENTER; _userDefinedCenter = center; }
        
        /** return the ProxyNode center point. */
        inline const vec_type& getCenter() const { if (_centerMode==USER_DEFINED_CENTER) return _userDefinedCenter; else return getBound().center(); }


        /** Set the object-space reference radius of the volume enclosed by the ProxyNode. 
          * Used to determine the bounding sphere of the ProxyNode in the absence of any children.*/
        inline void setRadius(value_type radius) { _radius = radius; }
        
        /** Get the object-space radius of the volume enclosed by the ProxyNode.*/
        inline value_type getRadius() const { return _radius; }

        virtual BoundingSphere computeBound() const;

    protected :
    
        virtual ~ProxyNode() {}// IE可能错误

        void expandFileNameListTo(unsigned int pos);

        typedef std::pair< std::string, ref_ptr<CVBF_Referenced> >  FileNameDatabaseRequestPair;
        typedef std::vector<FileNameDatabaseRequestPair>                 FileNameDatabaseRequestList;

        FileNameDatabaseRequestList     _filenameList;
        ref_ptr<CVBF_Referenced>             _databaseOptions;
        std::string                     _databasePath;
        
        LoadingExternalReferenceMode    _loadingExtReference;
        
        CenterMode                      _centerMode;
        vec_type                        _userDefinedCenter;
        value_type                      _radius;
        
};

}

#endif
