#ifndef VBF_GL_TEXTURE_H
#define VBF_GL_TEXTURE_H 1

#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>

// If not defined by gl.h use the definition found in:
// http://oss.sgi.com/projects/ogl-sample/registry/EXT/texture_filter_anisotropic.txt


#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
    #define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

#ifndef GL_ARB_texture_compression
    #define GL_COMPRESSED_ALPHA_ARB                 0x84E9
    #define GL_COMPRESSED_LUMINANCE_ARB             0x84EA
    #define GL_COMPRESSED_LUMINANCE_ALPHA_ARB       0x84EB
    #define GL_COMPRESSED_INTENSITY_ARB             0x84EC
    #define GL_COMPRESSED_RGB_ARB                   0x84ED
    #define GL_COMPRESSED_RGBA_ARB                  0x84EE
    #define GL_TEXTURE_COMPRESSION_HINT_ARB         0x84EF
    #define GL_TEXTURE_COMPRESSED_ARB               0x86A1
    #define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB   0x86A2
    #define GL_COMPRESSED_TEXTURE_FORMATS_ARB       0x86A3
#endif

#ifndef GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB
    #define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB    0x86A0
#endif

#ifndef GL_EXT_texture_compression_s3tc
    #define GL_COMPRESSED_RGB_S3TC_DXT1_EXT         0x83F0
    #define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT        0x83F1
    #define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT        0x83F2
    #define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT        0x83F3
#endif

#ifndef GL_EXT_texture_compression_rgtc
  #define GL_COMPRESSED_RED_RGTC1_EXT                0x8DBB
  #define GL_COMPRESSED_SIGNED_RED_RGTC1_EXT         0x8DBC
  #define GL_COMPRESSED_RED_GREEN_RGTC2_EXT          0x8DBD
  #define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT   0x8DBE
#endif

#ifndef GL_IMG_texture_compression_pvrtc
    #define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG      0x8C00
    #define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG      0x8C01
    #define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG     0x8C02
    #define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG     0x8C03
#endif

#ifndef GL_OES_compressed_ETC1_RGB8_texture
    #define GL_ETC1_RGB8_OES                            0x8D64   
#endif

#ifndef GL_ARB_INTERNAL_TEXTURE_FORMAT
    #define GL_RGBA32F_ARB                           0x8814
    #define GL_RGB32F_ARB                            0x8815
    #define GL_ALPHA32F_ARB                          0x8816
    #define GL_INTENSITY32F_ARB                      0x8817
    #define GL_LUMINANCE32F_ARB                      0x8818
    #define GL_LUMINANCE_ALPHA32F_ARB                0x8819
    #define GL_RGBA16F_ARB                           0x881A
    #define GL_RGB16F_ARB                            0x881B
    #define GL_ALPHA16F_ARB                          0x881C
    #define GL_INTENSITY16F_ARB                      0x881D
    #define GL_LUMINANCE16F_ARB                      0x881E
    #define GL_LUMINANCE_ALPHA16F_ARB                0x881F
#endif

#ifndef GL_ARB_PIXEL_DATA
    #define GL_HALF_FLOAT_ARB                        0x140B
#endif

#ifndef GL_NV_texture_shader
    #define GL_HILO_NV                              0x86F4
    #define GL_DSDT_NV                              0x86F5
    #define GL_DSDT_MAG_NV                          0x86F6
    #define GL_DSDT_MAG_VIB_NV                      0x86F7
    #define GL_HILO16_NV                            0x86F8
    #define GL_SIGNED_HILO_NV                       0x86F9
    #define GL_SIGNED_HILO16_NV                     0x86FA
    #define GL_SIGNED_RGBA_NV                       0x86FB
    #define GL_SIGNED_RGBA8_NV                      0x86FC
    #define GL_SIGNED_RGB_NV                        0x86FE
    #define GL_SIGNED_RGB8_NV                       0x86FF
    #define GL_SIGNED_LUMINANCE_NV                  0x8701
    #define GL_SIGNED_LUMINANCE8_NV                 0x8702
    #define GL_SIGNED_LUMINANCE_ALPHA_NV            0x8703
    #define GL_SIGNED_LUMINANCE8_ALPHA8_NV          0x8704
    #define GL_SIGNED_ALPHA_NV                      0x8705
    #define GL_SIGNED_ALPHA8_NV                     0x8706
    #define GL_SIGNED_INTENSITY_NV                  0x8707
    #define GL_SIGNED_INTENSITY8_NV                 0x8708
    #define GL_DSDT8_NV                             0x8709
    #define GL_DSDT8_MAG8_NV                        0x870A
    #define GL_DSDT8_MAG8_INTENSITY8_NV             0x870B
    #define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV         0x870C
    #define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV       0x870D
#endif

#ifndef GL_NV_float_buffer
    #define GL_FLOAT_R_NV                           0x8880
    #define GL_FLOAT_RG_NV                          0x8881
    #define GL_FLOAT_RGB_NV                         0x8882
    #define GL_FLOAT_RGBA_NV                        0x8883
    #define GL_FLOAT_R16_NV                         0x8884
    #define GL_FLOAT_R32_NV                         0x8885
    #define GL_FLOAT_RG16_NV                        0x8886
    #define GL_FLOAT_RG32_NV                        0x8887
    #define GL_FLOAT_RGB16_NV                       0x8888
    #define GL_FLOAT_RGB32_NV                       0x8889
    #define GL_FLOAT_RGBA16_NV                      0x888A
    #define GL_FLOAT_RGBA32_NV                      0x888B
#endif

#ifndef GL_NV_half_float
    #define GL_HALF_FLOAT_NV                        0x140B
#endif

#ifndef GL_ATI_texture_float
    #define GL_RGBA_FLOAT32_ATI                     0x8814
    #define GL_RGB_FLOAT32_ATI                      0x8815
    #define GL_ALPHA_FLOAT32_ATI                    0x8816
    #define GL_INTENSITY_FLOAT32_ATI                0x8817
    #define GL_LUMINANCE_FLOAT32_ATI                0x8818
    #define GL_LUMINANCE_ALPHA_FLOAT32_ATI          0x8819
    #define GL_RGBA_FLOAT16_ATI                     0x881A
    #define GL_RGB_FLOAT16_ATI                      0x881B
    #define GL_ALPHA_FLOAT16_ATI                    0x881C
    #define GL_INTENSITY_FLOAT16_ATI                0x881D
    #define GL_LUMINANCE_FLOAT16_ATI                0x881E
    #define GL_LUMINANCE_ALPHA_FLOAT16_ATI          0x881F
#endif

#ifndef GL_MIRRORED_REPEAT_IBM
    #define GL_MIRRORED_REPEAT_IBM            0x8370
#endif

#ifndef GL_CLAMP_TO_EDGE
    #define GL_CLAMP_TO_EDGE                  0x812F
#endif

#ifndef GL_CLAMP
    #define GL_CLAMP                          0x2900  
#endif

#ifndef GL_CLAMP_TO_BORDER_ARB
    #define GL_CLAMP_TO_BORDER_ARB            0x812D
#endif

#ifndef GL_INTENSITY
    // OpenGL ES1 and ES2 doesn't provide GL_INTENSITY
    #define GL_INTENSITY 0x8049
#endif

#ifndef GL_GENERATE_MIPMAP_SGIS
    #define GL_GENERATE_MIPMAP_SGIS           0x8191
    #define GL_GENERATE_MIPMAP_HINT_SGIS      0x8192
#endif

#ifndef GL_TEXTURE_3D
    #define GL_TEXTURE_3D                     0x806F
#endif

#ifndef GL_TEXTURE_2D_ARRAY_EXT
    #define GL_TEXTURE_2D_ARRAY_EXT           0x8C1A
    #define GL_TEXTURE_2D_ARRAY_EXT                        0x8C1A
    #define GL_PROXY_TEXTURE_2D_ARRAY_EXT                  0x8C1B
    #define GL_TEXTURE_BINDING_2D_ARRAY_EXT                0x8C1D
    #define GL_MAX_ARRAY_TEXTURE_LAYERS_EXT                0x88FF
    #define GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT            0x884E
    #define GL_SAMPLER_2D_ARRAY_EXT                        0x8DC1
    #define GL_SAMPLER_2D_ARRAY_SHADOW_EXT                 0x8DC4
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT    0x8CD4
#endif

#ifndef GL_TEXTURE_CUBE_MAP
    #define GL_TEXTURE_CUBE_MAP             0x8513
    #define GL_TEXTURE_BINDING_CUBE_MAP     0x8514
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_X  0x8515
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X  0x8516
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y  0x8517
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y  0x8518
    #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z  0x8519
    #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  0x851A
    #define GL_PROXY_TEXTURE_CUBE_MAP       0x851B
    #define GL_MAX_CUBE_MAP_TEXTURE_SIZE    0x851C
#endif

#ifndef GL_TEXTURE_BINDING_3D
    #define GL_TEXTURE_BINDING_3D             0x806A
#endif

#ifndef GL_DEPTH_TEXTURE_MODE_ARB
    #define GL_DEPTH_TEXTURE_MODE_ARB         0x884B
#endif

#ifndef GL_TEXTURE_COMPARE_MODE_ARB
    #define GL_TEXTURE_COMPARE_MODE_ARB       0x884C
#endif
#ifndef GL_TEXTURE_COMPARE_FUNC_ARB
    #define GL_TEXTURE_COMPARE_FUNC_ARB       0x884D
#endif
#ifndef GL_COMPARE_R_TO_TEXTURE_ARB
    #define GL_COMPARE_R_TO_TEXTURE_ARB       0x884E
#endif

#ifndef TEXTURE_COMPARE_FAIL_VALUE_ARB
    #define TEXTURE_COMPARE_FAIL_VALUE_ARB    0x80BF
#endif

#if !defined( GL_MAX_TEXTURE_UNITS )
    #define GL_MAX_TEXTURE_UNITS              0x84E2
#endif

#ifndef  GL_TEXTURE_DEPTH
    #define GL_TEXTURE_DEPTH                  0x8071
#endif

#ifndef GL_TEXTURE_2D_MULTISAMPLE
    #define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#endif

// Integer texture extension as in http://www.opengl.org/registry/specs/EXT/texture_integer.txt
#ifndef GL_EXT_texture_integer
    #define GL_RGBA32UI_EXT                                    0x8D70
    #define GL_RGB32UI_EXT                                     0x8D71
    #define GL_ALPHA32UI_EXT                                   0x8D72
    #define GL_INTENSITY32UI_EXT                               0x8D73
    #define GL_LUMINANCE32UI_EXT                               0x8D74
    #define GL_LUMINANCE_ALPHA32UI_EXT                         0x8D75

    #define GL_RGBA16UI_EXT                                    0x8D76
    #define GL_RGB16UI_EXT                                     0x8D77
    #define GL_ALPHA16UI_EXT                                   0x8D78
    #define GL_INTENSITY16UI_EXT                               0x8D79
    #define GL_LUMINANCE16UI_EXT                               0x8D7A
    #define GL_LUMINANCE_ALPHA16UI_EXT                         0x8D7B

    #define GL_RGBA8UI_EXT                                     0x8D7C
    #define GL_RGB8UI_EXT                                      0x8D7D
    #define GL_ALPHA8UI_EXT                                    0x8D7E
    #define GL_INTENSITY8UI_EXT                                0x8D7F
    #define GL_LUMINANCE8UI_EXT                                0x8D80
    #define GL_LUMINANCE_ALPHA8UI_EXT                          0x8D81

    #define GL_RGBA32I_EXT                                     0x8D82
    #define GL_RGB32I_EXT                                      0x8D83
    #define GL_ALPHA32I_EXT                                    0x8D84
    #define GL_INTENSITY32I_EXT                                0x8D85
    #define GL_LUMINANCE32I_EXT                                0x8D86
    #define GL_LUMINANCE_ALPHA32I_EXT                          0x8D87

    #define GL_RGBA16I_EXT                                     0x8D88
    #define GL_RGB16I_EXT                                      0x8D89
    #define GL_ALPHA16I_EXT                                    0x8D8A
    #define GL_INTENSITY16I_EXT                                0x8D8B
    #define GL_LUMINANCE16I_EXT                                0x8D8C
    #define GL_LUMINANCE_ALPHA16I_EXT                          0x8D8D

    #define GL_RGBA8I_EXT                                      0x8D8E
    #define GL_RGB8I_EXT                                       0x8D8F
    #define GL_ALPHA8I_EXT                                     0x8D90
    #define GL_INTENSITY8I_EXT                                 0x8D91
    #define GL_LUMINANCE8I_EXT                                 0x8D92
    #define GL_LUMINANCE_ALPHA8I_EXT                           0x8D93

    #define GL_RED_INTEGER_EXT                                 0x8D94
    #define GL_GREEN_INTEGER_EXT                               0x8D95
    #define GL_BLUE_INTEGER_EXT                                0x8D96
    #define GL_ALPHA_INTEGER_EXT                               0x8D97
    #define GL_RGB_INTEGER_EXT                                 0x8D98
    #define GL_RGBA_INTEGER_EXT                                0x8D99
    #define GL_BGR_INTEGER_EXT                                 0x8D9A
    #define GL_BGRA_INTEGER_EXT                                0x8D9B
    #define GL_LUMINANCE_INTEGER_EXT                           0x8D9C
    #define GL_LUMINANCE_ALPHA_INTEGER_EXT                     0x8D9D

    #define GL_RGBA_INTEGER_MODE_EXT                           0x8D9E
#endif


#endif  // VBF_GL_TEXTURE_H
