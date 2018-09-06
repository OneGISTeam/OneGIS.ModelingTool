#ifndef VBF_IMAGEUTILS_H
#define VBF_IMAGEUTILS_H

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_GLTexture.h>

    class VBF_GLAUX_EXPORT ImageUtils
    {
    public:
        // ����ͼ����osg::Image�Ŀ������캯���������ƣ�������ȫ
        static osg::Image* cloneImage( const osg::Image* image );

        // ʹͼ��淶��������OpenGL��GL_RGBA��GL_RGBA8��һ�µģ�Ϊ�˸��ϸ��ͼ�����΢��
        static void normalizeImage( osg::Image* image );


        // ��ͼ���һ���ֿ�������һ��ͼ��
        static bool copyAsSubImage( const osg::Image* src, osg::Image* dst,
                                   int dst_start_col, int dst_start_row, int dst_start_img=0 );

        /**
         * �ı�ͼ���С��ʹ���ٽ���������������ͼ�񲻸ı�Դͼ��
         *
         * ˵��������������ΪNULL�������·���һ����ͼ��If the output parameter is non-NULL, this method will
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

        // �������ͼ����Ҫ������ͬ�ĳߴ�
        static bool mix( osg::Image* dest, const osg::Image* src, float a );

        // ��ͼ��
        static osg::Image* sharpenImage( const osg::Image* image );

        // �ж�ͼ��ߴ��Ƿ���2�ĳ˷�
        static bool isPowerOfTwo(const osg::Image* image);

        // ����һ��͸���ģ������ص�ͼ������ռλ��
        static osg::Image* createEmptyImage();

        // ����ֻ��һ�����ص�ͼ��
        static osg::Image* createOnePixelImage(const osg::Vec4& color);

        // �ж�ͼ���Ƿ�Ϊ�գ�������ȫ͸����ͨ��alpha��ֵ�жϣ�
        static bool isEmptyImage(const osg::Image* image, float alphaThreshold =0.01);

        // �Ƿ��ǵ�һ��ɫͼ��
        static bool isSingleColorImage(const osg::Image* image, float threshold =0.01);

        // ͼ���Ƿ���ת��Ϊ�ض���ʽ/��������
        static bool canConvert(const osg::Image* image, GLenum pixelFormat, GLenum dataType);

        // ��ͼ��ת��Ϊ�ض���ʽ
        static osg::Image* convert(const osg::Image* image, GLenum pixelFormat, GLenum dataType);

        // ��ͼ��װ��ΪRGB8
        static osg::Image* convertToRGB8(const osg::Image* image);

        // ��ͼ��װ��ΪRGBA8
        static osg::Image* convertToRGBA8(const osg::Image* image);

        // �ж�����ͼ���Ƿ�һ��
        static bool areEquivalent(const osg::Image *lhs, const osg::Image *rhs);

        // �ж�������ɫ�Ƿ�������
        static bool areRGBEquivalent( const osg::Vec4& lhs, const osg::Vec4& rhs, float epsilon =0.01f ) {
            return
                fabs(lhs.r() - rhs.r()) < epsilon &&
                fabs(lhs.g() - rhs.g()) < epsilon &&
                fabs(lhs.b() - rhs.b()) < epsilon;
        }

        // ����Ƿ���alphaͨ��
        static bool hasAlphaChannel( const osg::Image* image );

        // ���ͼ���Ƿ�͸�������κ�һ�����ص�Alphaֵ���ڸ�����ֵ��
        static bool hasTransparency(const osg::Image* image, float alphaThreshold =1.0f);

        /**
         * ����alphaС��[maxAlpha]�����أ�������������ɫʹ֮ƥ������non-alpha�����أ�
           This facilitates multipass
         * blending or abutting tiles by overlapping them slightly. Specify "maxAlpha"
         * as the maximum value to consider when searching for fully-transparent pixels.
         */
        static void featherAlphaRegions(osg::Image* image, float maxAlpha =0.0f);

        // Converts an image (in place) to premultiplied-alpha format.
        static void convertToPremultipliedAlpha(osg::Image* image);

        // ͼ���Ƿ�Ϊѹ����ʽ
        static bool isCompressed( const osg::Image* image );

         // ����͹��ͼ
        static osg::Image* createBumpMap( const osg::Image* input );

        // ��һ��ͼ���ȡ��ɫ���ݣ������ڲ���ʽ
        class VBF_GLAUX_EXPORT PixelReader
        {
        public:
            PixelReader(const osg::Image* image);

            // �Ƿ�֧�ָ�����ʽ/��������
            static bool supports( GLenum pixelFormat, GLenum dataType );

            // �Ƿ���ԴӸ�����ͼ���ȡ����
            static bool supports( const osg::Image* image ) {
                return image && supports(image->getPixelFormat(), image->getDataType() );
            }

            // ��ȡһ�����ص���ɫ
            osg::Vec4 operator()(int s, int t, int r=0, int m=0) const {
                return (*_reader)(this, s, t, r, m);
            }

            // �ڲ�ʹ��:
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

        // ��һ��ͼ��д��ɫ���ݣ������ڲ���ʽ
        class VBF_GLAUX_EXPORT PixelWriter
        {
        public:
            PixelWriter(osg::Image* image);

            // �Ƿ�֧�ָ�����ʽ/��������
            static bool supports( GLenum pixelFormat, GLenum dataType );

            static bool supports( const osg::Image* image ) {
                return image && supports(image->getPixelFormat(), image->getDataType() );
            }

            // д��һ�����ص���ɫ
            void operator()(const osg::Vec4& c, int s, int t, int r=0, int m=0) {
                (*_writer)(this, c, s, t, r, m );
            }

            // �ڲ�ʹ��:
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

        // ����ͼ���ÿһ������
        template<typename T>
        struct PixelVisitor : public T
        {
            // ����ͼ�񣬲����ø���� bool operator(osg::Vec4& pixel);
            // ����÷�������true���Ѵ�����ͼ��ֵд��ԭλ��
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

            // ����ͼ�񣬲����ø���� bool operator(const osg::Vec4& srcPixel, osg::Vec4& destPixel);
            // ����÷�������true���Ѵ�����ͼ��ֵд��Ŀ��ͼ����ͬ��λ��
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

        // ��һ��ͼ������һ��ͼ�񿽱�����
        // �÷���PixelVisitor<CopyImage>().accept( fromImage, toImage );
        struct CopyImage
        {
            bool operator()( const osg::Vec4f& src, osg::Vec4f& dest ) {
                dest = src;
                return true;
            }
        };
        // �ѻҶ�ͼ��ת���ɴ�Alpha��ͼ�񣨱����Ǵ�8λͼ��ֱ�Ӷ�ȡ��ͼ��
        // ע�⣺�˷���Ҫ����8λ
        static osg::Image* VBF_GreyImageToAlha(osg::Image* pImage);
    };


#endif
