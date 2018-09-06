#ifndef VBF_IMAGEUTILS_H
#define VBF_IMAGEUTILS_H

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_GLTexture.h>

    class VBF_GLAUX_EXPORT ImageUtils
    {
    public:
        // 拷贝图像，与osg::Image的拷贝构造函数功能类似，但更安全
        static osg::Image* cloneImage( const osg::Image* image );

        // 使图像规范化，对于OpenGL，GL_RGBA和GL_RGBA8是一致的，为了更严格对图像进行微调
        static void normalizeImage( osg::Image* image );


        // 把图像的一部分拷贝到另一个图像
        static bool copyAsSubImage( const osg::Image* src, osg::Image* dst,
                                   int dst_start_col, int dst_start_row, int dst_start_img=0 );

        /**
         * 改变图像大小（使用临近采样），返回新图像不改变源图像
         *
         * 说明：如果输出参数为NULL，将重新分配一个新图像，If the output parameter is non-NULL, this method will
         * assume that the output image is already allocated to the proper size, and will
         * do a resize+copy into that image. In the latter case, it is your responsibility
         * to make sure the output image is allocated to the proper size.
         *
         * If the output parameter is non-NULL, then the mipmapLevel is also considered.
         * This lets you resize directly into a particular mipmap level of the output image.
         */
        static bool resizeImage( const osg::Image* input, unsigned int new_s, unsigned int new_t,
            ref_ptr<osg::Image>& output, unsigned int mipmapLevel =0 );

        /**
         * Crops the input image to the dimensions provided and returns a
         * new image. Returns a new image, leaving the input image unaltered.
         * Note:  The input destination bounds are modified to reflect the bounds of the
         *        actual output image.  Due to the fact that you cannot crop in the middle of a pixel
         *        The specified destination extents and the output extents may vary slightly.
         *@param src_minx
         *       The minimum x coordinate of the input image.
         *@param src_miny
         *       The minimum y coordinate of the input image.
         *@param src_maxx
         *       The maximum x coordinate of the input image.
         *@param src_maxy
         *       The maximum y coordinate of the input image.
         *@param dst_minx
         *       The desired minimum x coordinate of the cropped image.
         *@param dst_miny
         *       The desired minimum y coordinate of the cropped image.
         *@param dst_maxx
         *       The desired maximum x coordinate of the cropped image.
         *@param dst_maxy
         *       The desired maximum y coordinate of the cropped image.
         */
        static osg::Image* cropImage( const osg::Image* image,
            double src_minx, double src_miny, double src_maxx, double src_maxy,
            double &dst_minx, double &dst_miny, double &dst_maxx, double &dst_maxy);

        /**
         * Creates an Image that "blends" two images into a new image in which "primary"
         * occupies mipmap level 0, and "secondary" occupies all the other mipmap levels.
         *
         * WARNING: this method assumes that primary and seconday are the same exact size
         * and the same exact format.
         */
        static osg::Image* createMipmapBlendedImage( const osg::Image* primary, const osg::Image* secondary );

        // 混合两个图像，需要具有相同的尺寸
        static bool mix( osg::Image* dest, const osg::Image* src, float a );

        // 锐化图像
        static osg::Image* sharpenImage( const osg::Image* image );

        // 判断图像尺寸是否是2的乘方
        static bool isPowerOfTwo(const osg::Image* image);

        // 创建一个透明的，单像素的图像，用于占位符
        static osg::Image* createEmptyImage();

        // 创建只有一个像素的图像
        static osg::Image* createOnePixelImage(const osg::Vec4& color);

        // 判断图像是否为空，例如完全透明（通过alpha阈值判断）
        static bool isEmptyImage(const osg::Image* image, float alphaThreshold =0.01);

        // 是否是单一颜色图像
        static bool isSingleColorImage(const osg::Image* image, float threshold =0.01);

        // 图像是否能转换为特定格式/数据类型
        static bool canConvert(const osg::Image* image, GLenum pixelFormat, GLenum dataType);

        // 把图像转换为特定格式
        static osg::Image* convert(const osg::Image* image, GLenum pixelFormat, GLenum dataType);

        // 把图像装换为RGB8
        static osg::Image* convertToRGB8(const osg::Image* image);

        // 把图像装换为RGBA8
        static osg::Image* convertToRGBA8(const osg::Image* image);

        // 判断两个图像是否一样
        static bool areEquivalent(const osg::Image *lhs, const osg::Image *rhs);

        // 判断两个颜色是否近似相等
        static bool areRGBEquivalent( const osg::Vec4& lhs, const osg::Vec4& rhs, float epsilon =0.01f ) {
            return
                fabs(lhs.r() - rhs.r()) < epsilon &&
                fabs(lhs.g() - rhs.g()) < epsilon &&
                fabs(lhs.b() - rhs.b()) < epsilon;
        }

        // 检测是否有alpha通道
        static bool hasAlphaChannel( const osg::Image* image );

        // 检测图像是否透明（有任何一个像素的Alpha值低于给定的值）
        static bool hasTransparency(const osg::Image* image, float alphaThreshold =1.0f);

        /**
         * 查找alpha小于[maxAlpha]的像素，并设置它的颜色使之匹配相邻non-alpha的像素，
           This facilitates multipass
         * blending or abutting tiles by overlapping them slightly. Specify "maxAlpha"
         * as the maximum value to consider when searching for fully-transparent pixels.
         */
        static void featherAlphaRegions(osg::Image* image, float maxAlpha =0.0f);

        // Converts an image (in place) to premultiplied-alpha format.
        static void convertToPremultipliedAlpha(osg::Image* image);

        // 图像是否为压缩格式
        static bool isCompressed( const osg::Image* image );

         // 创建凸凹图
        static osg::Image* createBumpMap( const osg::Image* input );

        // 从一个图像读取颜色数据，不管内部格式
        class VBF_GLAUX_EXPORT PixelReader
        {
        public:
            PixelReader(const osg::Image* image);

            // 是否支持给定格式/数据类型
            static bool supports( GLenum pixelFormat, GLenum dataType );

            // 是否可以从给定的图像读取数据
            static bool supports( const osg::Image* image ) {
                return image && supports(image->getPixelFormat(), image->getDataType() );
            }

            // 读取一个像素的颜色
            osg::Vec4 operator()(int s, int t, int r=0, int m=0) const {
                return (*_reader)(this, s, t, r, m);
            }

            // 内部使用:
            const unsigned char* data(int s=0, int t=0, int r=0, int m=0) const {
                return m == 0 ?
                    _image->data() + s*_colMult + t*_rowMult + r*_imageSize :
                    _image->getMipmapData(m) + s*_colMult + t*(_rowMult >> m) + r*(_imageSize>>m) ;
            }

            typedef osg::Vec4 (*ReaderFunc)(const PixelReader* ia, int s, int t, int r, int m);
            ReaderFunc _reader;
            const osg::Image* _image;
            unsigned _colMult;
            unsigned _rowMult;
            unsigned _imageSize;
        };

        // 向一个图像写颜色数据，不管内部格式
        class VBF_GLAUX_EXPORT PixelWriter
        {
        public:
            PixelWriter(osg::Image* image);

            // 是否支持给定格式/数据类型
            static bool supports( GLenum pixelFormat, GLenum dataType );

            static bool supports( const osg::Image* image ) {
                return image && supports(image->getPixelFormat(), image->getDataType() );
            }

            // 写入一个像素的颜色
            void operator()(const osg::Vec4& c, int s, int t, int r=0, int m=0) {
                (*_writer)(this, c, s, t, r, m );
            }

            // 内部使用:
            osg::Image* _image;
            unsigned _colMult;
            unsigned _rowMult;
            unsigned _imageSize;

            unsigned char* data(int s=0, int t=0, int r=0, int m=0) const {
                return m == 0 ?
                    _image->data() + s*_colMult + t*_rowMult + r*_imageSize :
                    _image->getMipmapData(m) + s*_colMult + t*(_rowMult >> m) + r*(_imageSize>>m);
            }

            typedef void (*WriterFunc)(const PixelWriter* iw, const osg::Vec4& c, int s, int t, int r, int m);
            WriterFunc _writer;
        };

        // 遍历图像的每一个像素
        template<typename T>
        struct PixelVisitor : public T
        {
            // 遍历图像，并调用父类的 bool operator(osg::Vec4& pixel);
            // 如果该方法返回true，把处理后的图像值写回原位置
            void accept( osg::Image* image ) {
                PixelReader _reader( image );
                PixelWriter _writer( image );
                for( int r=0; r<image->r(); ++r ) {
                    for( int t=0; t<image->t(); ++t ) {
                        for( int s=0; s<image->s(); ++s ) {
                            osg::Vec4f pixel = _reader(s,t,r);
                            if ( (*this)(pixel) )
                                _writer(pixel,s,t,r);
                        }
                    }
                }
            }          

            // 遍历图像，并调用父类的 bool operator(const osg::Vec4& srcPixel, osg::Vec4& destPixel);
            // 如果该方法返回true，把处理后的图像值写到目的图像相同的位置
            void accept( const osg::Image* src, osg::Image* dest ) {
                PixelReader _readerSrc( src );
                PixelReader _readerDest( dest );
                PixelWriter _writerDest( dest );
                for( int r=0; r<src->r(); ++r ) {
                    for( int t=0; t<src->t(); ++t ) {
                        for( int s=0; s<src->s(); ++s ) {
                            const osg::Vec4f pixelSrc = _readerSrc(s,t,r);
                            osg::Vec4f pixelDest = _readerDest(s,t,r);
                            if ( (*this)(pixelSrc, pixelDest) )
                                _writerDest(pixelDest,s,t,r);
                        }
                    }
                }
            }
        };

        // 从一个图像向另一个图像拷贝像素
        // 用法：PixelVisitor<CopyImage>().accept( fromImage, toImage );
        struct CopyImage
        {
            bool operator()( const osg::Vec4f& src, osg::Vec4f& dest ) {
                dest = src;
                return true;
            }
        };
        // 把灰度图像转换成带Alpha的图像（必须是从8位图像直接读取的图像）
        // 注意：此方法要求是8位
        static osg::Image* VBF_GreyImageToAlha(osg::Image* pImage);
    };


#endif
