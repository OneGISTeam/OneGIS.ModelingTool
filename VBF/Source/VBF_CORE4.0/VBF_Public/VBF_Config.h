//=======================================================================================
// ���ܼ�飺 ��������
// ��ʼ���ߣ� �����
// ����ʱ�䣺 2013-04-18
//=======================================================================================

#ifndef _VBF_CONFIG_
#define _VBF_CONFIG_

// ˵�������ļ�������VBF��Ŀ��ȫ���Ա������ã������ϵͳ��������������ѡ���
/* #undef OSG_NOTIFY_DISABLED */
/* #undef OSG_USE_FLOAT_MATRIX */
/* #undef OSG_USE_FLOAT_PLANE */
#define OSG_USE_FLOAT_BOUNDINGSPHERE
#define OSG_USE_FLOAT_BOUNDINGBOX
#define OSG_USE_REF_PTR_IMPLICIT_OUTPUT_CONVERSION
/* #undef OSG_USE_UTF8_FILENAME */
#define OSG_DISABLE_MSVC_WARNING

#define OSG_GL1_AVAILABLE
#define OSG_GL2_AVAILABLE
/* #undef OSG_GL3_AVAILABLE */
/* #undef OSG_GLES1_AVAILABLE */
/* #undef OSG_GLES2_AVAILABLE */
/* #undef OSG_GL_LIBRARY_STATIC */
#define OSG_GL_DISPLAYLISTS_AVAILABLE
#define OSG_GL_MATRICES_AVAILABLE
#define OSG_GL_VERTEX_FUNCS_AVAILABLE
#define OSG_GL_VERTEX_ARRAY_FUNCS_AVAILABLE
#define OSG_GL_FIXED_FUNCTION_AVAILABLE




#endif
