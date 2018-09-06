#ifndef OSGEARTH_COMPOSITING_H
#define OSGEARTH_COMPOSITING_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_TileKey.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <vector>

namespace osgEarth
{
    // ͼ����tilekey�Ķԣ�pair��
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

    // ͼ��Ƕ�ף������࣬���ڴ�һ��ͼ�񼯺���ȡһ��ͼ��
    class OSGEARTH_EXPORT ImageMosaic : public ::CVBF_Referenced
    {
    public:
        ImageMosaic();
        virtual ~ImageMosaic();

        osg::Image* createImage();

        // ��Ƭͼ���б�
        typedef std::vector<TileImage> TileImageList;

        // ��ȡ��Ƭͼ������
        TileImageList& getImages() {return _images;}

        void getExtents(double &minX, double &minY, double &maxX, double &maxY);

    protected:

        TileImageList _images;
    };
}

#endif // OSGEARTH_COMPOSITING_H
