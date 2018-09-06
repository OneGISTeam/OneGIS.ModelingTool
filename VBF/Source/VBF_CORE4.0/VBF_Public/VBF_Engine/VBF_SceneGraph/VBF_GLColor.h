#ifndef VBF_GL_COLOR_H
#define VBF_GL_COLOR_H 1

#ifndef GL_VERSION_1_2
    // 1.2 definitions...
    #define GL_BGR                          0x80E0
    #define GL_BGRA                         0x80E1
    #define GL_UNSIGNED_BYTE_3_3_2          0x8032
    #define GL_UNSIGNED_BYTE_2_3_3_REV      0x8362
    #define GL_UNSIGNED_SHORT_5_6_5         0x8363
    #define GL_UNSIGNED_SHORT_5_6_5_REV     0x8364
    #define GL_UNSIGNED_SHORT_4_4_4_4       0x8033
    #define GL_UNSIGNED_SHORT_4_4_4_4_REV   0x8365
    #define GL_UNSIGNED_SHORT_5_5_5_1       0x8034
    #define GL_UNSIGNED_SHORT_1_5_5_5_REV   0x8366
    #define GL_UNSIGNED_INT_8_8_8_8         0x8035
    #define GL_UNSIGNED_INT_8_8_8_8_REV     0x8367
    #define GL_UNSIGNED_INT_10_10_10_2      0x8036
    #define GL_UNSIGNED_INT_2_10_10_10_REV  0x8368
#endif

#ifndef GL_COMPRESSED_ALPHA
    #define GL_COMPRESSED_ALPHA             0x84E9
    #define GL_COMPRESSED_LUMINANCE         0x84EA
    #define GL_COMPRESSED_LUMINANCE_ALPHA   0x84EB
    #define GL_COMPRESSED_INTENSITY         0x84EC
    #define GL_COMPRESSED_RGB               0x84ED
    #define GL_COMPRESSED_RGBA              0x84EE
#endif


#ifndef GL_ABGR_EXT
#define GL_ABGR_EXT                         0x8000
#endif

#if defined(OSG_GLES1_AVAILABLE) || defined(OSG_GLES2_AVAILABLE)
    #define GL_RED                  0x1903
    #define GL_GREEN                0x1904
    #define GL_BLUE                 0x1905
    #define GL_DEPTH_COMPONENT      0x1902
    #define GL_STENCIL_INDEX        0x1901
#endif

#if defined(OSG_GLES1_AVAILABLE) || defined(OSG_GLES2_AVAILABLE) || defined(OSG_GL3_AVAILABLE)
    #define GL_BITMAP               0x1A00
    #define GL_COLOR_INDEX          0x1900
    #define GL_INTENSITY12          0x804C
    #define GL_INTENSITY16          0x804D
    #define GL_INTENSITY4           0x804A
    #define GL_INTENSITY8           0x804B
    #define GL_LUMINANCE12          0x8041
    #define GL_LUMINANCE12_ALPHA4   0x8046
    #define GL_LUMINANCE12_ALPHA12  0x8047
    #define GL_LUMINANCE16          0x8042
    #define GL_LUMINANCE16_ALPHA16  0x8048
    #define GL_LUMINANCE4           0x803F
    #define GL_LUMINANCE4_ALPHA4    0x8043
    #define GL_LUMINANCE6_ALPHA2    0x8044
    #define GL_LUMINANCE8           0x8040
    #define GL_LUMINANCE8_ALPHA8    0x8045
    #define GL_RGBA8                0x8058
    #define GL_PACK_ROW_LENGTH      0x0D02
#endif

#ifndef GL_PACK_SKIP_IMAGES
    #define GL_PACK_SKIP_IMAGES     0x806B
    #define GL_PACK_IMAGE_HEIGHT    0x806C
    #define GL_UNPACK_SKIP_IMAGES   0x806D
    #define GL_UNPACK_IMAGE_HEIGHT  0x806E
#endif


#endif  