#ifndef OSGEARTH_COMPOSITING_H
#define OSGEARTH_COMPOSITING_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <vector>

namespace osgEarth
{
    // 图像与tilekey的对（pair）
    struct OSGEARTH_EXPORT TileImage
    {
        TileImage(osg::Image* image, const CVBF_TileKey& key);
        virtual ~TileImage() { }

        osg::Image* getImage() {return _image.get();}

        ref_ptr<osg::Image> _image;       
        double _minX, _minY, _maxX, _maxY;
        unsigned int _tileX;
        unsigned int _tileY;
    };

    // 图像嵌套，工具类，用于从一个图像集合提取一个图像
    class OSGEARTH_EXPORT ImageMosaic : public ::CVBF_Referenced
    {
    public:
        ImageMosaic();
        virtual ~ImageMosaic();

        osg::Image* createImage();

        // 瓦片图像列表
        typedef std::vector<TileImage> TileImageList;

        // 获取瓦片图像的类表
        TileImageList& getImages() {return _images;}

        void getExtents(double &minX, double &minY, double &maxX, double &maxY);

    protected:

        TileImageList _images;
    };
}

#endif // OSGEARTH_COMPOSITING_H
