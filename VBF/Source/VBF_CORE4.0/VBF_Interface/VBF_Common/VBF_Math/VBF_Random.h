///**********************************************************************************
// 文件名：  VBF_Random.h
// 描述：    定义随机数
// 作者:     杜莹
// 日期:     2013-07-02
//**********************************************************************************

#ifndef __VBF_RANDOM_H__
#define __VBF_RANDOM_H__

#include <VBF_Common/VBF_Math/VBF_Export.h>

enum EVBF_RANDOM_METHOD
{
    VBF_RANDOM_METHOD_FAST        // not great, but super-fast and cheap.
};

/**
* Psuedo random number generator. Results are guaranteed to be consistent across
* machines given the same seed value.
*/
class VBF_MATH_EXPORT CVBF_Random
{
public:
    /**
        * Constructs a new random number generator. It is seeded with
        * the system clock.
        * @param method RNG method to use
        */
    CVBF_Random(EVBF_RANDOM_METHOD method=VBF_RANDOM_METHOD_FAST);

    /**
        * Constucts a new random number generator with a user-specified seed.
        * The results are guaranteed to be globally consistent.
        * @param seed   RNG seed value
        * @param method RNG method to use
        */
    CVBF_Random(unsigned seed, EVBF_RANDOM_METHOD method=VBF_RANDOM_METHOD_FAST);

    /**
        * Copy constructor.
        */
    CVBF_Random(const CVBF_Random& rhs);

    virtual ~CVBF_Random();

    /**
    * Resets the PRNG to its initial state (initial seed).
    */
    void reset();

    /**
        * Gets the next random number as an unsigned int.
        * @param mod Modulus value. The result will fall within the range [0..mod)
        */
    unsigned next(unsigned mod);

    /**
        * Gets the next random number as a double in the range [0..1].
        */
    double next();

private:
    EVBF_RANDOM_METHOD	_method;
    unsigned			_seed;
    unsigned			_next;
};


#endif
