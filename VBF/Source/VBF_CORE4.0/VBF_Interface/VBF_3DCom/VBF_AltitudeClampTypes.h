//***************************************************************************************
// FileName：VBF_3DTerrainDataTypes.h
// Function：与地形有关的公用数据类型
// Author:   杜莹
// Date:     2012-06-13
//***************************************************************************************

#ifndef __VBF_3DTERRAIN_DATATYPES_H__
#define __VBF_3DTERRAIN_DATATYPES_H__


// 定义模型高程值夹取方式
const char VBF_ALTITUDE_CLAMP_TO_TERRAIN[]			= "ClampToTerrain";			// 忽略用户输入的高程值，使用地面点的实际高程值
const char VBF_ALTITUDE_CLAMP_ABSOLUTE[]			= "ClampAbsolute";			// 将用户输入的高程值作为地面点的绝对高程值
const char VBF_ALTITUDE_CLAMP_RELATIVE_TO_TERRAIN[]	= "ClampRelativeToTerrain";	// 将用户输入的高程值作为地面点的相对高程值


#endif

