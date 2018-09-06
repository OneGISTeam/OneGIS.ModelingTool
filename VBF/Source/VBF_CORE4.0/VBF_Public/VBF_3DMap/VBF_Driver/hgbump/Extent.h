/**************************************************************************************************
* @file Extent.h
* @note ��չ��Ϣ
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
    * @brief ��չ��Ϣ�洢��
    * @note ��չ��Ϣ�洢�࣬���д洢��SRS�������Լ��ڵ�ǰͶӰ�µ���İ�Χ��ķ�Χ
    * @author c00005
    */
    class VBF_3DNormalMap_EXPORT CExtent
    {
    public:
        /**  
        * @brief ���캯��
        * @note ���캯�������Ƿ���Ч����Ϊ����Ч
        * @return ��
        */
        CExtent();

        /**  
        * @brief ���캯��
        * @note ���в����Ĺ��캯��  
        * @param dXMin [in] x�᷽�����Сֵ
        * @param dYMin [in] y�᷽�����Сֵ
        * @param dXMax [in] x�᷽������ֵ
        * @param dYMax [in] y�᷽������ֵ
        * @param strSrs [in] ��ʼ��Srs����������
        * @return ��
        */
        CExtent( double dXMin, double dYMin, double dXMax, double dYMax, const std::string& strSrs );

        /**  
        * @brief ���캯��
        * @note �������캯��  
        * @param rhs [in] Extent��Ķ������ã�������ʼ�����б�����ֵ
        * @return ��
        */
        CExtent( const CExtent& rhs );

        /**  
        *  @brief ��ֵ����
        *  @note ��ֵ����  
        *  @param rhs [in] Extent��Ķ������ã�������ʼ�����б�����ֵ
        *  @return ��
        */
        CExtent & operator= (const CExtent &other);

        virtual ~CExtent();
    public:
        /**  
        * @note ����x�᷽�����Сֵ  
        */
        double GetXMin() const { return m_dXMin; }

        /**  
        * @note ����y�᷽�����Сֵ 
        */
        double GetYMin() const { return m_dYMin; }

        /**  
        * @note ����x�᷽������ֵ
        */
        double GetXMax() const { return m_dXMax; }

        /**  
        * @note ����y�᷽������ֵ
        */
        double GetYMax() const { return m_dYMax; }

        /**  
        * @note ����srs������
        */
        const std::string& GetSrsName() { return m_strSrsName; }

        /**  
        * @note ���ظ���չ��Ϣ�Ƿ���Ч
        */
        bool IsValid() const { return m_bIsValid; }

    private:
        ///x��y�����ϵ������Сֵ
        double m_dXMin, m_dYMin, m_dXMax, m_dYMax;

        ///srs����
        std::string m_strSrsName;

        ///����չ��Ϣ����Ч
        bool m_bIsValid;
    };
}

#endif
//xahg h00017
