//xahg h00017

#ifndef OSGEARTH_VIRTUAL_PROGRAM_H
#define OSGEARTH_VIRTUAL_PROGRAM_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/Revisioning.h>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <VBF_3DMap/VBF_Terrain/ColorFilter.h>
#include <VBF_Engine/VBF_SceneGraph/Shader>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrProgram.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttribute.h>
#include <string>
#include <map>
#include <Types/VBF_Optional.h>
#include <VBF_3DMap/VBF_Terrain/Containers>

#ifdef OSG_GLES2_AVAILABLE
#    define GLSL_VERSION                 100
#    define GLSL_VERSION_STR             "100"
#    define GLSL_DEFAULT_PRECISION_FLOAT "precision highp float;"
#else
#    define GLSL_VERSION                 120
#    define GLSL_VERSION_STR             "120"
#    define GLSL_DEFAULT_PRECISION_FLOAT ""
#endif

namespace osgEarth
{
    namespace ShaderComp
    {
        // User function injection points.
        enum FunctionLocation
        {
            // vertex is in model space (equivalent to gl_Vertex).
            LOCATION_VERTEX_MODEL = 0,

            // vertex is in view(aka eye) coordinates, with the camera at 0,0,0
            // looking down the -Z axis.
            LOCATION_VERTEX_VIEW = 1,

            // vertex is in post-perspective coordinates; [-w..w] along each axis
            LOCATION_VERTEX_CLIP = 2,

            // fragment is being colored.
            LOCATION_FRAGMENT_COLORING = 3,

            // fragment is being lit.
            LOCATION_FRAGMENT_LIGHTING = 4,

            // fragment output is being assigned.
            LOCATION_FRAGMENT_OUTPUT = 5
        };

        /**
         * Callback that accepts a user-injected shader function (set with
         * setFunction) for inclusing in the program at render time.
         */
        class AcceptCallback : public CVBF_Referenced
        {
        public:
            // implement this to accept or reject based on the state
            virtual bool operator()(const osg::State& state) =0;
        protected:
            virtual ~AcceptCallback() { }
        };

        // User function (used internally)
        struct Function
        {
            std::string                  _name;
            ref_ptr<AcceptCallback> _accept;
            CVBF_Optional<float>     _minRange;
            CVBF_Optional<float>     _maxRange;

            bool accept(const osg::State& state) const {
                return (!_accept.valid()) || (_accept->operator()(state) == true);
            }
        };

        typedef std::pair<float, Function> OrderedFunction;

        // ordered set of user functions.
        typedef std::multimap<float, Function> OrderedFunctionMap; // duplicate keys allowed

        // user function sets, categorized by function location.
        typedef std::map<FunctionLocation, OrderedFunctionMap> FunctionLocationMap;
    }


    /**
     * VirtualProgram enables GLSL shader composition within osgEarth. It automatically
     * assembles shader functions into a full shader program at run time. You can add
     * or remove functions (injection points) at any time.
     *
     * Read about shader composition:
     * http://docs.osgearth.org/en/latest/developer/shader_composition.html
     *
     * VirtualProgram (VP) is an osg::StateAttribute. But unlike most attributes, a VP
     * will inherit properties from other VPs in the state stack.
     *
     * Though the code has evolved quite a bit, VirtualProgram was originally adapted
     * from the VirtualProgram shader composition work done by Wojciech Lewandowski and
     * found in OSG's osgvirtualprogram example.
     */
    class OSGEARTH_EXPORT VirtualProgram : public osg::StateAttribute
    {
    public:
        static const osg::StateAttribute::Type SA_TYPE;

        /**
        * Gets the VP on a stateset, creating and installing one if the stateset
        * does not already have one. This is a convenient patternt to use, since
        * the normal use-case is to add functions to an existing VP rather than
        * to replace it entirely.
        */
        static VirtualProgram* getOrCreate(osg::StateSet* on);

        /**
        * Gets the VP on a stateset, or NULL if one is not found.
        */
        static VirtualProgram* get(osg::StateSet* on);
        static const VirtualProgram* get(const osg::StateSet* on);

        /**
        * Creates a new VP on the stateset, cloning an existing one if found.
        */
        static VirtualProgram* cloneOrCreate(osg::StateSet* stateset);

        /**
        * Creates a new VP on the "dest" stateset, either by cloning one found
        * on the "src" stateset, or otherwise just constructing a new one.
        */
        static VirtualProgram* cloneOrCreate(const osg::StateSet* src, osg::StateSet* dest);

    public:
        /**
         * Adds a custom shader function to the program.
         *
         * Call this method (rather than setShader directly) to inject "user" functions into the
         * shader program.
         *
         * name:      Name of the function. This should be the actual function name in the shader source.
         * source:    The shader source code.
         * location:  Function location relative to the built-ins.
         * order:     Lets you control the order of functions that you inject at the same location.
         *            The default order is 1.0. Note that many of osgEarth's built-in shaders (like
         *            those that render the terrain) use order=0.0 so that by default they run before
         *            user-injected functions by default.
         */
        void setFunction(
            const std::string&           name,
            const std::string&           source,
            ShaderComp::FunctionLocation location,
            float                        order =1.0f );

        void setFunction(
            const std::string&           name,
            const std::string&           source,
            ShaderComp::FunctionLocation location,
            ShaderComp::AcceptCallback*  acceptCallback,
            float                        order =1.0f );

        /**
         * Sets the minimum active range for a named function. The function must already
         * exist in the VirtualProgram. For this to work, there must to a uniform in the
         * scene graph that conveys the current range; use the VirtualProgramRangeCallback
         * to activate this.
         */
        void setFunctionMinRange(const std::string& name, float minRange);

        void setFunctionMaxRange(const std::string& name, float maxRange);

        /**
         * Whether this VP should inherit shaders from parent state sets. This is
         * the normal operation. You can set this to "false" to "reset" the VP.
         */
        void setInheritShaders( bool value );

    public:
        /**
         * Constructs a new VP
         */
        VirtualProgram( unsigned int mask = 0xFFFFFFFFUL );

        /**
         * Copy constructor
         */
        VirtualProgram( const VirtualProgram& VirtualProgram,
                        const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY );

        META_StateAttribute( osgEarth, VirtualProgram, SA_TYPE);

        /** dtor */
        virtual ~VirtualProgram();

        /**
         * Compare this program against another (used for state-sorting)
         * return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.
         */
        virtual int compare(const StateAttribute& sa) const;

        /**
         * If enabled, activate our program in the GL pipeline,
         * performing any rebuild operations that might be pending.
         */
        virtual void apply(osg::State& state) const;

        /**
         * Gets a shader by its ID.
         */
        osg::Shader* getShader( const std::string& shaderID ) const;

        /**
         * Adds a shader to this VP's shader table.
         */
        osg::Shader* setShader(
            const std::string&                 shaderID,
            osg::Shader*                       shader,
            osg::StateAttribute::OverrideValue ov         =osg::StateAttribute::ON );

        osg::Shader* setShader(
            osg::Shader*                       shader,
            osg::StateAttribute::OverrideValue ov         =osg::StateAttribute::ON );

        /**
         * Removes a shader from the local VP.
         */
        void removeShader( const std::string& shaderID );

        /** Add an attribute location binding. */
        void addBindAttribLocation( const std::string& name, GLuint index );

        /** Remove an attribute location binding. */
        void removeBindAttribLocation( const std::string& name );

        /** Gets a reference to the attribute bindings. */
        typedef osg::Program::AttribBindingList AttribBindingList;
        const AttribBindingList& getAttribBindingList() const { return _attribBindingList; }

        /** Access to the property template. */
        osg::Program* getTemplate() { return _template.get(); }
        const osg::Program* getTemplate() const { return _template.get(); }

        /** Enable logging to the console, for debugging. */
        void setShaderLogging( bool log );

        /** Enable logging to a file, for deugging. */
        void setShaderLogging( bool log, const std::string& filepath );

        /** Gets whether the accept callbacks vary per frame */
        bool getAcceptCallbacksVaryPerFrame() const;

        /** Sets whether the accept callbacks vary per frame */
        void setAcceptCallbacksVaryPerFrame(bool acceptCallbacksVaryPerFrame);

    public: // StateAttribute
        virtual void compileGLObjects(osg::State& state) const;
        virtual void resizeGLObjectBuffers(unsigned maxSize);

        /** If State is non-zero, this function releases any associated OpenGL objects for
           * the specified graphics context. Otherwise, releases OpenGL objects
           * for all graphics contexts. */
        virtual void releaseGLObjects(osg::State* pState) const;

    public:
        typedef std::vector< ref_ptr<osg::Shader> > ShaderVector;

    public:
        struct ShaderEntry
        {
            ShaderEntry();
            bool accept(const osg::State& state) const;
            ref_ptr<osg::Shader>                _shader;
            osg::StateAttribute::OverrideValue       _overrideValue;
            ref_ptr<ShaderComp::AcceptCallback> _accept;
            bool operator < (const ShaderEntry& rhs) const;
        };

        struct ProgramEntry
        {
            ref_ptr<osg::Program> _program;
            unsigned                   _frameLastUsed;
        };

        typedef unsigned                              ShaderID;
        typedef vector_map<ShaderID, ShaderEntry>     ShaderMap;
        typedef std::map< std::string, std::string >  AttribAliasMap;
        typedef std::pair< std::string, std::string > AttribAlias;
        typedef std::vector< AttribAlias >            AttribAliasVector;

        typedef osgEarth::fast_map< ShaderVector, ProgramEntry > ProgramMap;
        typedef std::pair< const osg::StateAttribute*, osg::StateAttribute::OverrideValue > AttributePair;
        typedef std::vector< AttributePair > AttrStack;

    public:
        /**
         * Populates the output collection with all the osg::Shader objects that
         * are applicable for the given State.
         */
        static void getShaders(
            const osg::State&                        state,
            std::vector<ref_ptr<osg::Shader> >& output);

    protected:
        // thread-safe functions map getter
        void getFunctions( ShaderComp::FunctionLocationMap& out ) const;

        // thread-safe shader map copy
        void getShaderMap( ShaderMap& out ) const;

        // thread-safe shader accumulator
        void addShadersToAccumulationMap(VirtualProgram::ShaderMap& accumMap, const osg::State& state) const;

    protected:
        // holds "template" data that should be installed in every auto-generated
        // Program, like uniform buffer bindings, etc.
        ref_ptr<osg::Program> _template;

        unsigned int       _mask;
        AttribBindingList  _attribBindingList;
        AttribAliasMap     _attribAliases;

        // holds the injection points the user has added to this VP.
        // _dataModelMutex protects access to this member.
        ShaderComp::FunctionLocationMap _functions;

        // holds a map of each named shader installed in this VP.
        // _dataModelMutex protects access to this member.
        ShaderMap _shaderMap;

        // per-context cached shader map for thread-safe reuse without constant reallocation.
        struct ApplyVars
        {
            ShaderMap         accumShaderMap;
            ShaderVector      keyVector;
            AttribBindingList accumAttribBindings;
            AttribAliasMap    accumAttribAliases;
        };
        mutable osg::buffered_object<ApplyVars> _apply;

        // protects access to the data members, which may be accessed by other VPs in the state stack.
        mutable CVBF_Mutex _dataModelMutex;

        // The program cache holds an osg::Program instance for each collection of shaders
        // that comprises this VP. There can be multiple programs in the cache if the VP is
        // shared in the scene graph.
        mutable ProgramMap       _programCache;
        mutable CVBF_Mutex _programCacheMutex;

        mutable CVBF_Optional<bool> _active;
        bool _inherit;
        bool _inheritSet;

        bool _logShaders;
        std::string _logPath;

        // whether to use the "attribute stack memory" feature. default = true.
        // see below.
        bool _useStackMemory;

        bool _acceptCallbacksVaryPerFrame;

        // Mechnism for remembering whether a VP has been applied during the same frame
        // and with the same attribute stack.
        struct AttrStackMemory
        {
            void remember(const osg::State& state, const AttrStack& rhs, osg::Program* p);
            osg::Program* recall(const osg::State& state, const AttrStack& rhs);

            struct Item
            {
                int frameNumber;
                AttrStack attrStack;
                ref_ptr<osg::Program> program;
            };
            osg::buffered_object<Item> _item;
        };
        mutable AttrStackMemory _vpStackMemory;

        bool hasLocalFunctions() const;

        void accumulateFunctions(
            const osg::State&                state,
            ShaderComp::FunctionLocationMap& result ) const;

        const AttribAliasMap& getAttribAliases() const { return _attribAliases; }

        // utility function
        static void accumulateShaders(
            const osg::State&  state,
            unsigned           mask,
            ShaderMap&         accumShaderMap,
            AttribBindingList& accumAttribBindings,
            AttribAliasMap&    accumAttribAliases,
            bool&              acceptCallbacksPresent);

        bool readProgramCache(
            const ShaderVector& vec,
            unsigned frameNumber,
            ref_ptr<osg::Program>& program);

        void removeExpiredProgramsFromCache(
            osg::State& state,
            unsigned frameNumber);

        bool checkSharing();
    };

} // namespace osgEarth

#endif // OSGEARTH_VIRTUAL_PROGRAM_H
//xahg h00017
