#ifndef VBF_DYNAMICLIBRARY
#define VBF_DYNAMICLIBRARY 1

#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Common/VBF_Utils/VBF_UtilsExport.h>

#include <string>



// װ��/ж�ض�̬�⹦�ܵķ�װ������Ӧ���Ǽ������ݶ�д���
class VBF_UTILS_EXPORT VBF_DynamicLibrary : public ::CVBF_Referenced
{
    public:

        typedef void*   HANDLE;
        typedef void*   PROC_ADDRESS;
        
 		// װ�ض�̬��
        static VBF_DynamicLibrary* loadLibrary(const std::string& libraryName);

 		// ��ȡ��̬�����֣�ȥ��·����
        const std::string& getName() const     { return m_sName; }

  		// ��ȡ��̬�����֣���·����
        const std::string& getFullName() const { return _fullName; }

   		// ��ȡ��̬������.dso/.dll��
        HANDLE getHandle() const   { return _handle; }

		// ��ȡ������ַ
        PROC_ADDRESS getProcAddress(const std::string& procName);

        ~VBF_DynamicLibrary();
    protected:

        // ��ȡ���ļ��ľ��
        static HANDLE getLibraryHandle( const std::string& libraryName);
        VBF_DynamicLibrary(const std::string& name,HANDLE handle);

		// ��������Ϳ�����ֻ�ܵ���loadLibrary
        VBF_DynamicLibrary();
        VBF_DynamicLibrary(const VBF_DynamicLibrary&);
        VBF_DynamicLibrary& operator = (const VBF_DynamicLibrary&);


        HANDLE          _handle;  // ���
        std::string     m_sName;    // ����
        std::string     _fullName;// ȫ��

};



#endif // __DYNAMIC_LIBRARY_H
