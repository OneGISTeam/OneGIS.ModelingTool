#ifndef OSGEARTH_PROGRESS_H
#define OSGEARTH_PROGRESS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>

namespace osgEarth
{
    // ����������ȵĻص�����
    class OSGEARTH_EXPORT ProgressCallback : public ::CVBF_Referenced
    {
    public:
        ProgressCallback();
        virtual ~ProgressCallback() { }

        //�����õĻص���������ǰ����ȡ���ˣ�����true��msg�����ڸ�ʲô��
        //current����ǰ������� total������������stage����ǰ��������totalStages�ܵĲ�����
        virtual bool reportProgress( double current, double total,
            unsigned currentStage, unsigned totalStages, const std::string& msg );

        // ��ݺ���
        bool reportProgress( double current, double total, const std::string& msg )
        {
            return reportProgress(current, total, 0, 1, msg );
        }
        bool reportProgress( double current, double total )
        {
            return reportProgress(current, total, 0, 1, "" );
        }

        virtual void onStarted() { }// ��ʼʱ����
        virtual void onCompleted() { }// ���ʱ����

        void cancel() { _canceled = true; }// ����ȡ����־
        bool isCanceled() const { return _canceled; }// �Ƿ�ȡ��

        std::string& message() { return _message; }

        bool needsRetry() const { return _needsRetry; }// �Ƿ���Ҫ����
        void setNeedsRetry( bool needsRetry ) { _needsRetry = needsRetry; } // �����Ƿ���Ҫ����

    protected:
        volatile unsigned _numStages;
        volatile bool     _canceled;
        std::string       _message;
        volatile bool     _needsRetry;
    };


    // ͨ������̨��ʾ���ȵĻص�����
    class OSGEARTH_EXPORT ConsoleProgressCallback : public ProgressCallback
    {
    public:
        ConsoleProgressCallback();
        virtual ~ConsoleProgressCallback() { }

        virtual bool reportProgress( double current, double total,
            unsigned currentStage, unsigned totalStages, const std::string& msg );
    };
}

#endif
