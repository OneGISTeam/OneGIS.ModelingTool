#ifndef OSGVOLUME_LAYER
#define OSGVOLUME_LAYER 1

#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexture.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SceneGraph/TransferFunction>
#include <VBF_Engine/VBF_SceneGraph/VBF_ObjectMatrix.h>

#include <VBF_Engine/VBF_Volume/Locator>
#include <VBF_Engine/VBF_Volume/VBF_VolumeProperty.h>

namespace osgVolume {

/** Data strucutre for passing details about the loading imagery on to osgVolume for use when setting up dimensions etc.*/
class OSGVOLUME_EXPORT ImageDetails : public osg::CVBF_Object
{
    public:

        ImageDetails();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        ImageDetails(const ImageDetails&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgVolume, ImageDetails);

        void setTexelOffset(const osg::Vec4& offset) { _texelOffset = offset; }
        const osg::Vec4& getTexelOffset() const { return _texelOffset; }

        void setTexelScale(const osg::Vec4& scale) { _texelScale = scale; }
        const osg::Vec4& getTexelScale() const { return _texelScale; }

        void setMatrix(osg::RefMatrix* matrix) { _matrix = matrix; }
        osg::RefMatrix* getMatrix() { return _matrix.get(); }
        const osg::RefMatrix* getMatrix() const { return _matrix.get(); }

    protected:

        osg::Vec4                       _texelOffset;
        osg::Vec4                       _texelScale;
        ref_ptr<osg::RefMatrix>    _matrix;

};

/** Base class for representing a single layer of volume data.*/
class OSGVOLUME_EXPORT Layer : public osg::CVBF_Object
{
    public:

        Layer();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Layer(const Layer&,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgVolume, Layer);

        /** Set the file name of the data associated with this layer. */
        virtual void setFileName(const std::string& filename) { _filename = filename; }

        /** Get the file name of the layer. */
        virtual const std::string& getFileName() const { return _filename; }

        void setLocator(Locator* locator) { _locator = locator; }
        Locator* getLocator() { return _locator.get(); }
        const Locator* getLocator() const { return _locator.get(); }

        void setDefaultValue(const osg::Vec4& value) { _defaultValue = value; }
        const osg::Vec4& getDefaultValue() const { return _defaultValue; }

        /** Set the minification texture filter to use when do texture associated with this layer.*/
        void setMinFilter(osg::Texture::FilterMode filter) { _minFilter = filter; }

        /** Get the minification texture filter to use when do texture associated with this layer.*/
        osg::Texture::FilterMode getMinFilter() const { return _minFilter; }

        /** Set the magniification texture filter to use when do texture associated with this layer.*/
        void setMagFilter(osg::Texture::FilterMode filter) { _magFilter = filter; }

        /** Get the magnification texture filter to use when do texture associated with this layer.*/
        osg::Texture::FilterMode getMagFilter() const { return _magFilter; }

        /** Return image associated with layer if supported. */
        virtual osg::Image* getImage() { return 0; }

        /** Return const image associated with layer if supported. */
        virtual const osg::Image* getImage() const { return 0; }


        /** Set the Property (or Properties via the CompositeProperty) that informs the VolumeTechnique how this layer should be rendered.*/
        void setProperty(Property* property) { _property = property; }

        /** Get the Property that informs the VolumeTechnique how this layer should be rendered.*/
        Property* getProperty() { return _property.get(); }

        /** Get the const Property that informs the VolumeTechnique how this layer should be rendered.*/
        const Property* getProperty() const { return _property.get(); }

        /** Add a property, automatically creating a CompositePorperty if one isn't already assigned.*/
        void addProperty(Property* property);


        /** Specify whether ImageLayer requires update traversal. */
        virtual bool requiresUpdateTraversal() const { return false; }

        /** Call update on the Layer.*/
        virtual void update(osg::NodeVisitor& /*nv*/) {}

        /** increment the modified count."*/
        virtual void dirty() {};

        /** Set the modified count value.  */
        virtual void setModifiedCount(unsigned int /*value*/) {};

        /** Get modified count value. */
        virtual unsigned int getModifiedCount() const { return 0; }

        virtual osg::BoundingSphere computeBound() const;

    protected:

        virtual ~Layer();

        std::string                         _filename;
        ref_ptr<Locator>               _locator;
        osg::Vec4                           _defaultValue;
        osg::Texture::FilterMode            _minFilter;
        osg::Texture::FilterMode            _magFilter;

        ref_ptr<Property>              _property;

};

class OSGVOLUME_EXPORT ImageLayer : public Layer
{
    public:

        ImageLayer(osg::Image* image=0);

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        ImageLayer(const ImageLayer& imageLayer,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgVolume, ImageLayer);

        void setFileName(const std::string& filename) { _filename = filename; if (_image.valid()) _image->setFileName(filename); }
        virtual const std::string& getFileName() const { return _image.get() ? _image->getFileName() : _filename; }

        void setImage(osg::Image* image);

        /** Return image associated with layer. */
        virtual osg::Image* getImage() { return _image.get(); }

        /** Return const image associated with layer. */
        virtual const osg::Image* getImage() const { return _image.get(); }


        void setTexelOffset(const osg::Vec4& offset) { _texelOffset = offset; }
        const osg::Vec4& getTexelOffset() const { return _texelOffset; }

        void setTexelScale(const osg::Vec4& scale) { _texelScale = scale; }
        const osg::Vec4& getTexelScale() const { return _texelScale; }


        /** Compute the min and max pixel colors.*/
        bool computeMinMax(osg::Vec4& min, osg::Vec4& max);

        /** Apply color transformation to pixels using c' = offset + c * scale .*/
        void offsetAndScaleImage(const osg::Vec4& offset, const osg::Vec4& scale);

        /** Compute the min max range of the image, and then remap this to a 0 to 1 range.*/
        void rescaleToZeroToOneRange();

        /** Compute the min color component of the image and then translate and pixels by this offset to make the new min component 0.*/
        void translateMinToZero();

        virtual bool requiresUpdateTraversal() const;

        virtual void update(osg::NodeVisitor& /*nv*/);

        virtual void dirty();
        virtual void setModifiedCount(unsigned int value);
        virtual unsigned int getModifiedCount() const;

    protected:

        virtual ~ImageLayer() {}

        osg::Vec4                   _texelOffset;
        osg::Vec4                   _texelScale;
        ref_ptr<osg::Image>    _image;

};

class OSGVOLUME_EXPORT CompositeLayer : public Layer
{
    public:

        CompositeLayer();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        CompositeLayer(const CompositeLayer& compositeLayer,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

        META_Object(osgVolume, CompositeLayer);

        void clear();

        void setFileName(unsigned int i, const std::string& filename) { if (i>=_layers.size()) _layers.resize(i+1); _layers[i].filename = filename; if (_layers[i].layer.valid()) _layers[i].layer->setFileName(filename); }
        const std::string& getFileName(unsigned int i) const { return _layers[i].layer.valid() ? _layers[i].layer->getFileName() : _layers[i].filename; }

        void setLayer(unsigned int i, Layer* layer) { if (i>=_layers.size()) _layers.resize(i+1); _layers[i].layer = layer; }
        Layer* getLayer(unsigned int i) { return i<_layers.size() ? _layers[i].layer.get() : 0; }
        const Layer* getLayer(unsigned int i) const { return i<_layers.size() ? _layers[i].layer.get() : 0; }

        void addLayer(Layer* layer) { _layers.push_back(NameLayer(layer->getFileName(),layer)); }

        void removeLayer(unsigned int i) { _layers.erase(_layers.begin()+i); }

        unsigned int getNumLayers() const { return _layers.size(); }

        bool requiresUpdateTraversal() const;

        virtual void update(osg::NodeVisitor& /*nv*/);

    protected:

        virtual ~CompositeLayer() {}

        struct NameLayer
        {
            NameLayer() {}

            NameLayer(const NameLayer& cnl):
                filename(cnl.filename),
                layer(cnl.layer) {}

            NameLayer(const std::string& fn, Layer* l):
                filename(fn),
                layer(l) {}

            NameLayer& operator = (const NameLayer& cnl)
            {
                if (&cnl==this) return *this;

                filename = cnl.filename;
                layer = cnl.layer;
                return *this;
            }

            std::string         filename;
            ref_ptr<Layer> layer;
        };

        typedef std::vector< NameLayer > Layers;

        Layers _layers;
};

/** Compute a 3d image that represent the normal map of the specified 3d image.*/
extern OSGVOLUME_EXPORT osg::Image* createNormalMapTexture(osg::Image* image_3d);

/** Create an image that has a transfer function applied specified Image.*/
extern OSGVOLUME_EXPORT osg::Image* applyTransferFunction(osg::Image* image, osg::TransferFunction1D* transferFunction);

}

#endif
