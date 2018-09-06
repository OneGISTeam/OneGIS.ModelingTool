#ifndef VBF_DYNAMICLIBRARY
#define VBF_DYNAMICLIBRARY 1

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>

#include <string>



// 装载/卸载动态库功能的封装，典型应用是加载数据读写插件
class VBF_UTILS_EXPORT VBF_DynamicLibrary : public ::CVBF_Referenced
{
    public:

        typedef void*   HANDLE;
        typedef void*   PROC_ADDRESS;
        
 		// 装载动态库
        static VBF_DynamicLibrary* loadLibrary(const std::string& libraryName);

 		// 获取动态库名字（去除路径）
        const std::string& getName() const     { return m_sName; }

  		// 获取动态库名字（含路径）
        const std::string& getFullName() const { return _fullName; }

   		// 获取动态库句柄（.dso/.dll）
        HANDLE getHandle() const   { return _handle; }

		// 获取函数地址
        PROC_ADDRESS getProcAddress(const std::string& procName);

        ~VBF_DynamicLibrary();
    protected:

        // 获取库文件的句柄
        static HANDLE getLibraryHandle( const std::string& libraryName);
        VBF_DynamicLibrary(const std::string& name,HANDLE handle);

		// 不允许构造和拷贝，只能调用loadLibrary
        VBF_DynamicLibrary();
        VBF_DynamicLibrary(const VBF_DynamicLibrary&);
        VBF_DynamicLibrary& operator = (const VBF_DynamicLibrary&);


        HANDLE          _handle;  // 句柄
        std::string     m_sName;    // 名字
        std::string     _fullName;// 全名

};



#endif // __DYNAMIC_LIBRARY_H
