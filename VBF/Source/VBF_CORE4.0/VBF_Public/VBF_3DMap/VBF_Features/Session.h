#ifndef OSGEARTH_FEATURES_SESSION_H
#define OSGEARTH_FEATURES_SESSION_H 1

#include <VBF_3DMap/VBF_Features/Common>
#include <VBF_3DMap/VBF_Features/VBFO_ScriptEngine.h>
#include <VBF_3DMap/VBF_Symbology/StyleSheet.h>
#include <VBF_3DMap/VBF_Terrain/StateSetCache.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapInfo.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapFrame.h>
#include <VBF_3DMap/VBF_Terrain/VBF_Map.h>


namespace osgEarth { namespace Features
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    class FeatureSource;

    /**
     * Session��һ��״̬������ʼ���մ������������feature�༭������
     * Session���湲��ġ������õ����ݣ������ݿ�ͨ��FilterContext���з���
     *
     * Whereas a FilterContext exists thoughout the life of a single compilation, a Session
     * exists one level above this and governs any number of "related" compilations
     * (���磬��ɵ���ͼ��Ķ������ı༭).
     * Sessionʵ��URIResolver�ӿڣ����ھ����������URIs.
     */
    class OSGEARTHFEATURES_EXPORT Session : public ::CVBF_Referenced
    {
    public:
        Session( const CVBF_Map* map, StyleSheet* styles =0L, FeatureSource* source =0L, const osgDB::Options* dbOptions =0L );
        virtual ~Session();

        // URI��Ϣ�����·����
        void setURIContext( const URIContext& value ) { _uriContext = value; }
        const URIContext& uriContext() const { return _uriContext; }

        /**
         * Gets the underlying map (frame) interface in this session
         */
        CVBF_MapFrame createMapFrame( CVBF_Map::ModelParts parts =CVBF_Map::TERRAIN_LAYERS ) const;


        // ��ȡ��session�����ĵ�ͼ��Ϣ
        const CVBF_MapInfo& GetMapInfo() const { return _mapInfo; }

        // ��ȡ��session�����Ŀռ�ο�ϵͳ
        const CVBF_SpatialReference* GetMapSRS() const { return _mapInfo.getSRS(); }

        // ��ȡ��session�����ĵ�ͼ��ע����������ָ��
        const CVBF_Map* GetMap() const { return _map.get(); }

        /** The style sheet governing this session. */
        void setStyles( StyleSheet* value );
        StyleSheet* styles() const { return _styles.get(); }

        // ��ȡ����Դ
        FeatureSource* getFeatureSource() const;

        /** The I/O options for operations within this session */
        const osgDB::Options* getDBOptions() const;

    public:
        template<typename T>
        struct CreateFunctor 
		{
            virtual T* operator()() const =0;
        };

        /**
         * Stores an object in the shared Session cache.
         *
         * WARNING! Don't store things like nodes in here unless you plan
         * to clone them. This is a multi-threaded store.
         *
         * Returns the object written, OR the already-existing object if overwrite = false
         * and the key was already taken.
         */
        template<typename T>
        T* putObject( const std::string& key, T* object, bool overwrite =true ) 
		{
            CVBF_ScopedMutexLock lock( _objMapMutex );

            ObjectMap::iterator i = _objMap.find(key);
            if ( i != _objMap.end() && !overwrite )
                return dynamic_cast<T*>(i->second.get());

            _objMap[key] = object;
            return object;
        }

        /**
         * Gets an object from the shared Session cache.
         * (returns a ref_ptr so as not to lose its ref in a multi-threaded app)
         */
        template<typename T>
        ref_ptr<T> getObject( const std::string& key ) 
		{
            CVBF_ScopedMutexLock lock( _objMapMutex );
            ObjectMap::const_iterator i = _objMap.find(key);
            return i != _objMap.end() ? dynamic_cast<T*>( i->second.get() ) : 0L;
        }

        template<typename T>
        bool getOrCreateObject(const std::string& key, ref_ptr<T>& ipOutput, const CreateFunctor<T>& create) 
		{
            CVBF_ScopedMutexLock lock( _objMapMutex );
            ObjectMap::const_iterator i = _objMap.find(key);
            if ( i != _objMap.end() ) 
			{
                ipOutput = dynamic_cast<T*>( i->second.get() );
                return true;
            }
            else 
			{
				T* pObject = create();
				if ( pObject == NULL ) return false;

				_objMap[key] = pObject;
				ipOutput = pObject;
				return true;
            }
        }

        void removeObject( const std::string& key );

    public:
        /**
         * The cache for optimizing stateset sharing within a session
         */
        StateSetCache* getStateSetCache() { return _stateSetCache.get(); }

    public:
      CVBFO_ScriptEngine* getScriptEngine() const;

    private:
        typedef std::map<std::string, ref_ptr<CVBF_Referenced> > ObjectMap;
        ObjectMap                    _objMap;
        CVBF_Mutex					 _objMapMutex;

        URIContext                    _uriContext;
        observer_ptr<const CVBF_Map>  _map;
        CVBF_MapInfo                  _mapInfo;
        ref_ptr<StyleSheet>           _styles;
        ref_ptr<const osgDB::Options> _dbOptions;
        ref_ptr<CVBFO_ScriptEngine>   _styleScriptEngine;
        ref_ptr<FeatureSource>        _featureSource;
        ref_ptr<StateSetCache>        _stateSetCache;
    };

} }

#endif // OSGEARTH_FEATURES_SESSION_H
