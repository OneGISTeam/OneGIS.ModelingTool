#ifndef VBF_EARTH_TIME_CONTROL_H
#define VBF_EARTH_TIME_CONTROL_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Base/VBF_FrameStamp.h>
#include <vector>


// 序列中的帧信息
struct CVBF_SequenceFrameInfo
{
    std::string timeIdentifier; // 事件标识
};


// Interface to an object that is subject to time controls.
class IVBF_SequenceControl
{
public:
    virtual bool supportsSequenceControl() const =0; // 实现是否支持这些方法

    virtual void playSequence() =0; // 开始播放
    virtual void pauseSequence() =0; // 停止播放
    virtual void seekToSequenceFrame(unsigned frame) =0; // 定位到特定的帧

    virtual bool isSequencePlaying() const =0;	// 是否在播放

	// 获取序列中的当前帧的信息数据
    virtual const std::vector<CVBF_SequenceFrameInfo>& getSequenceFrameInfo() const =0;

	// 获取帧的索引
    virtual int getCurrentSequenceFrameIndex( const ::CVBF_FrameStamp* ) const =0;
};


#endif // VBF_EARTH_TIME_CONTROL_H
