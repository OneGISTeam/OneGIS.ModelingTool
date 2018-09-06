#ifndef OSGEARTH_PROGRESS_H
#define OSGEARTH_PROGRESS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>

namespace osgEarth
{
    // 用于输出进度的回调函数
    class OSGEARTH_EXPORT ProgressCallback : public ::CVBF_Referenced
    {
    public:
        ProgressCallback();
        virtual ~ProgressCallback() { }

        //被调用的回调函数，当前任务被取消了，返回true。msg描述在干什么。
        //current，当前步骤计数 total，步骤总数；stage，当前步骤数，totalStages总的步骤数
        virtual bool reportProgress( double current, double total,
            unsigned currentStage, unsigned totalStages, const std::string& msg );

        // 便捷函数
        bool reportProgress( double current, double total, const std::string& msg )
        {
            return reportProgress(current, total, 0, 1, msg );
        }
        bool reportProgress( double current, double total )
        {
            return reportProgress(current, total, 0, 1, "" );
        }

        virtual void onStarted() { }// 开始时调用
        virtual void onCompleted() { }// 完成时调用

        void cancel() { _canceled = true; }// 设置取消标志
        bool isCanceled() const { return _canceled; }// 是否被取消

        std::string& message() { return _message; }

        bool needsRetry() const { return _needsRetry; }// 是否需要重试
        void setNeedsRetry( bool needsRetry ) { _needsRetry = needsRetry; } // 设置是否需要重试

    protected:
        volatile unsigned _numStages;
        volatile bool     _canceled;
        std::string       _message;
        volatile bool     _needsRetry;
    };


    // 通过控制台显示进度的回调函数
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
