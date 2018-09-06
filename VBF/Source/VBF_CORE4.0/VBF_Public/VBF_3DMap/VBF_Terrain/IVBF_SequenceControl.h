#ifndef VBF_EARTH_TIME_CONTROL_H
#define VBF_EARTH_TIME_CONTROL_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Base/VBF_FrameStamp.h>
#include <vector>


// �����е�֡��Ϣ
struct CVBF_SequenceFrameInfo
{
    std::string timeIdentifier; // �¼���ʶ
};


// Interface to an object that is subject to time controls.
class IVBF_SequenceControl
{
public:
    virtual bool supportsSequenceControl() const =0; // ʵ���Ƿ�֧����Щ����

    virtual void playSequence() =0; // ��ʼ����
    virtual void pauseSequence() =0; // ֹͣ����
    virtual void seekToSequenceFrame(unsigned frame) =0; // ��λ���ض���֡

    virtual bool isSequencePlaying() const =0;	// �Ƿ��ڲ���

	// ��ȡ�����еĵ�ǰ֡����Ϣ����
    virtual const std::vector<CVBF_SequenceFrameInfo>& getSequenceFrameInfo() const =0;

	// ��ȡ֡������
    virtual int getCurrentSequenceFrameIndex( const ::CVBF_FrameStamp* ) const =0;
};


#endif // VBF_EARTH_TIME_CONTROL_H
