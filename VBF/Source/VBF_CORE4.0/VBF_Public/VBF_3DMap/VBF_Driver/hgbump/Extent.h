/**************************************************************************************************
* @file Extent.h
* @note 扩展信息
* @author c00005
* @data 2013-12-20
**************************************************************************************************/

//xahg h00017

#ifndef CEXTENT_H
#define CEXTENT_H

#include <iostream>
#include "export.h"

namespace FePlugin
{
    /**
    * @class CExtent
    * @brief 扩展信息存储类
    * @note 扩展信息存储类，其中存储了SRS的名称以及在当前投影下地球的包围球的范围
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CExtent
    {
    public:
        /**  
        * @brief 构造函数
        * @note 构造函数，将是否有效构造为了无效
        * @return 无
        */
        CExtent();

        /**  
        * @brief 构造函数
        * @note 带有参数的构造函数  
        * @param dXMin [in] x轴方向的最小值
        * @param dYMin [in] y轴方向的最小值
        * @param dXMax [in] x轴方向的最大值
        * @param dYMax [in] y轴方向的最大值
        * @param strSrs [in] 初始化Srs的名称类型
        * @return 无
        */
        CExtent( double dXMin, double dYMin, double dXMax, double dYMax, const std::string& strSrs );

        /**  
        * @brief 构造函数
        * @note 拷贝构造函数  
        * @param rhs [in] Extent类的对象引用，用来初始化类中变量的值
        * @return 无
        */
        CExtent( const CExtent& rhs );

        /**  
        *  @brief 赋值函数
        *  @note 赋值函数  
        *  @param rhs [in] Extent类的对象引用，用来初始化类中变量的值
        *  @return 无
        */
        CExtent & operator= (const CExtent &other);

        virtual ~CExtent();
    public:
        /**  
        * @note 返回x轴方向的最小值  
        */
        double GetXMin() const { return m_dXMin; }

        /**  
        * @note 返回y轴方向的最小值 
        */
        double GetYMin() const { return m_dYMin; }

        /**  
        * @note 返回x轴方向的最大值
        */
        double GetXMax() const { return m_dXMax; }

        /**  
        * @note 返回y轴方向的最大值
        */
        double GetYMax() const { return m_dYMax; }

        /**  
        * @note 返回srs的名称
        */
        const std::string& GetSrsName() { return m_strSrsName; }

        /**  
        * @note 返回该扩展信息是否有效
        */
        bool IsValid() const { return m_bIsValid; }

    private:
        ///x、y方向上的最大最小值
        double m_dXMin, m_dYMin, m_dXMax, m_dYMax;

        ///srs名称
        std::string m_strSrsName;

        ///该扩展信息否有效
        bool m_bIsValid;
    };
}

#endif
//xahg h00017
