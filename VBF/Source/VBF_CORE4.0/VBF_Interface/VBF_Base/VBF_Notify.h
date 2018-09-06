#ifndef VBF_NOTIFY_H
#define VBF_NOTIFY_H 1

#include <VBF_Base/VBF_BaseExport.h>
#include <VBF_Base/VBF_Referenced.h> 

#include <ostream>

namespace osg 
{

/** ֪ͨ��Level����DEBUG_FP��FATAL��,ͨ����������OSGNOTIFYLEVEL��OSG_NOTIFY_LEVEL���á�
  * - setenv OSGNOTIFYLEVEL DEBUG (for tsh)
  * - export OSGNOTIFYLEVEL=DEBUG (for bourne shell)
  * - set OSGNOTIFYLEVEL=DEBUG (for Windows)
*/
enum NotifySeverity // ��ΪEVBF_NotifyLevel
{
    ALWAYS=0,   // ���е���Ϣ
    FATAL=1,    // �����������Ϣ
    WARN=2,     // ���漶�����Ϣ
    NOTICE=3,   // ֪ͨ�������Ϣ��Ĭ�ϵ�
    INFO=4,
    DEBUG_INFO=5,
    DEBUG_FP=6
};

// ����/��ȡ֪ͨ��Level
extern VBF_BASE_EXPORT void setNotifyLevel(NotifySeverity severity);
extern VBF_BASE_EXPORT NotifySeverity getNotifyLevel();


// ��ʼ��֪ͨ�ļ���
extern VBF_BASE_EXPORT bool initNotifyLevel();

#ifdef OSG_NOTIFY_DISABLED
    inline bool isNotifyEnabled(NotifySeverity) { return false; }
#else
    // �ü����֪ͨ�Ƿ�������setNotifyLevel
    extern VBF_BASE_EXPORT bool isNotifyEnabled(NotifySeverity severity);
#endif

// ֪ͨ��Ϣ�����ṩ����������Ϣ���߳��ĵ�����Ϣ�Ȳ�ͬ��Σ�
extern VBF_BASE_EXPORT std::ostream& notify(const NotifySeverity severity);

// ֪ͨ��Ϣ��Ĭ��ΪINFO����
inline std::ostream& notify(void) { return notify(osg::INFO); }

#define OSG_NOTIFY(level) if (osg::isNotifyEnabled(level)) osg::notify(level)
#define OSG_ALWAYS   OSG_NOTIFY(osg::ALWAYS)
#define OSG_FATAL    OSG_NOTIFY(osg::FATAL)
#define OSG_WARN     OSG_NOTIFY(osg::WARN)
#define OSG_NOTICE   OSG_NOTIFY(osg::NOTICE)
#define OSG_INFO     OSG_NOTIFY(osg::INFO)
#define OSG_DEBUG    OSG_NOTIFY(osg::DEBUG_INFO)
#define OSG_DEBUG_FP OSG_NOTIFY(osg::DEBUG_FP)



/** Handler processing output of notification stream. It acts as a sink to 
  * notification messages. It is called when notification stream needs to be 
  * synchronized (i.e. after osg::notify() << std::endl).
  * StandardNotifyHandler is used by default, it writes notifications to stderr 
  * (severity <= WARN) or stdout (severity > WARN).
  * Notifications can be redirected to other sinks such as GUI widgets or 
  * windows debugger (WinDebugNotifyHandler) with custom handlers.
  * Use setNotifyHandler to set custom handler.
  * Note that osg notification API is not thread safe although notification 
  * handler is called from many threads. When incorporating handlers into GUI
  * widgets you must take care of thread safety on your own.
  * @see setNotifyHandler
  */
class VBF_BASE_EXPORT NotifyHandler : public ::CVBF_Referenced
{
public:
    virtual void notify(osg::NotifySeverity severity, const char *message) = 0;
};


// ����/��ȡNotify��Ϣ������������������ݣ���Ĭ����StandardNotifyHandler��
extern VBF_BASE_EXPORT void setNotifyHandler(NotifyHandler *handler);
extern VBF_BASE_EXPORT NotifyHandler* getNotifyHandler();


/** Redirects notification stream to stderr (severity <= WARN) or stdout (severity > WARN).
  * The fputs() function is used to write messages to standard files. Note that
  * std::out and std::cerr streams are not used.
  */
class VBF_BASE_EXPORT StandardNotifyHandler : public NotifyHandler
{
public:
    void notify(osg::NotifySeverity severity, const char *message);
};


#if defined(WIN32) && !defined(__CYGWIN__)
// ���������������
class VBF_BASE_EXPORT WinDebugNotifyHandler : public NotifyHandler
{
public:
    void notify(osg::NotifySeverity severity, const char *message);
};
#endif



}

#endif
