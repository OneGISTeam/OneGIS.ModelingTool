#ifndef OSGEARTH_ENGINE_MP_OPTIONS
#define OSGEARTH_ENGINE_MP_OPTIONS 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_ConfigOptionsTerrain.h>
#include <Types/VBF_Color.h>


using namespace osgEarth;

// MP地形引擎的配置选项
class CMP_ConfigOptionsTerrain : public CVBF_OptionsTerrain // NO EXPORT (header-only)
{
public:
	CMP_ConfigOptionsTerrain( const CVBF_Options& options =CVBF_Options() ) : CVBF_OptionsTerrain( options ),
		_skirtRatio    ( 0.05 ),
		_quickRelease  ( true ),
		_lodFallOff    ( 0.0 ),
		_normalizeEdges( true ),
		_rangeMode     ( osg::IVBF_SGNodeGroupLOD::DISTANCE_FROM_EYE_POINT ),
		_tilePixelSize ( 256 ),
		_premultAlpha  ( true ),
		_color         ( VBFCOLOR::White ),
		_reCalNormals  (false)
	{
		setDriver( "mp" );
		fromConfig( m_conf );
	}

	virtual ~CMP_ConfigOptionsTerrain() { }

public:
	CVBF_Optional<float>& heightFieldSkirtRatio() { return _skirtRatio; }
	const CVBF_Optional<float>& heightFieldSkirtRatio() const { return _skirtRatio; }

	CVBF_Optional<bool>& quickReleaseGLObjects() { return _quickRelease; }
	const CVBF_Optional<bool>& quickReleaseGLObjects() const { return _quickRelease; }

	CVBF_Optional<float>& lodFallOff() { return _lodFallOff; }
	const CVBF_Optional<float>& lodFallOff() const { return _lodFallOff; }

	CVBF_Optional<bool>& normalizeEdges() { return _normalizeEdges; }
	const CVBF_Optional<bool>& normalizeEdges() const { return _normalizeEdges; }

	CVBF_Optional<osg::IVBF_SGNodeGroupLOD::RangeMode>& rangeMode() { return _rangeMode;}
	const CVBF_Optional<osg::IVBF_SGNodeGroupLOD::RangeMode>& rangeMode() const { return _rangeMode;}

	CVBF_Optional<float>& tilePixelSize() { return _tilePixelSize; }
	const CVBF_Optional<float>& tilePixelSize() const { return _tilePixelSize; }

	CVBF_Optional<bool>& premultipliedAlpha() { return _premultAlpha; }
	const CVBF_Optional<bool>& premultipliedAlpha() const { return _premultAlpha; }

	CVBF_Optional<VBFCOLOR>& color() { return _color; }
	const CVBF_Optional<VBFCOLOR>& color() const { return _color; }

	CVBF_Optional<bool>& reCalNormals() { return _reCalNormals; }
	const CVBF_Optional<bool>& reCalNormals() const { return _reCalNormals; }

protected:
	virtual CVBF_Config getConfig() const 
	{
		CVBF_Config conf = CVBF_OptionsTerrain::getConfig();
		conf.updateIfSet( "skirt_ratio", _skirtRatio );					// 裙边比例
		conf.updateIfSet( "quick_release_gl_objects", _quickRelease );	// 是否快速释放GL对象
		conf.updateIfSet( "lod_fall_off", _lodFallOff );				// 
		conf.updateIfSet( "normalize_edges", _normalizeEdges);
		conf.updateIfSet( "tile_pixel_size", _tilePixelSize );			// 瓦片大小（纹理）
		conf.updateIfSet( "range_mode", "PIXEL_SIZE_ON_SCREEN", _rangeMode, osg::IVBF_SGNodeGroupLOD::PIXEL_SIZE_ON_SCREEN );
		conf.updateIfSet( "range_mode", "DISTANCE_FROM_EYE_POINT", _rangeMode, osg::IVBF_SGNodeGroupLOD::DISTANCE_FROM_EYE_POINT);
		conf.updateIfSet( "premultiplied_alpha", _premultAlpha );
		conf.updateIfSet( "color", _color );
		conf.updateIfSet( "recalnormals", _reCalNormals );

		return conf;
	}

	virtual void mergeConfig( const CVBF_Config& conf ) 
	{
		CVBF_OptionsTerrain::mergeConfig( conf );
		fromConfig( conf );
	}

private:
	void fromConfig( const CVBF_Config& conf ) 
	{
		conf.getIfSet( "skirt_ratio", _skirtRatio );
		conf.getIfSet( "quick_release_gl_objects", _quickRelease );
		conf.getIfSet( "lod_fall_off", _lodFallOff );
		conf.getIfSet( "normalize_edges", _normalizeEdges );
		conf.getIfSet( "tile_pixel_size", _tilePixelSize );

		conf.getIfSet( "range_mode", "PIXEL_SIZE_ON_SCREEN", _rangeMode, osg::IVBF_SGNodeGroupLOD::PIXEL_SIZE_ON_SCREEN );
		conf.getIfSet( "range_mode", "DISTANCE_FROM_EYE_POINT", _rangeMode, osg::IVBF_SGNodeGroupLOD::DISTANCE_FROM_EYE_POINT);
		conf.getIfSet( "premultiplied_alpha", _premultAlpha );
		conf.getIfSet( "color", _color );
		conf.getIfSet( "recalnormals", _reCalNormals );
	}

	CVBF_Optional<float>               _skirtRatio;
	CVBF_Optional<bool>                _quickRelease;
	CVBF_Optional<float>               _lodFallOff;
	CVBF_Optional<bool>                _normalizeEdges;
	CVBF_Optional<osg::IVBF_SGNodeGroupLOD::RangeMode> _rangeMode;
	CVBF_Optional<float>               _tilePixelSize;
	CVBF_Optional<bool>                _premultAlpha;
	CVBF_Optional<VBFCOLOR>            _color;
	CVBF_Optional<bool>				   _reCalNormals;  // 是否根据顶点高程值重新计算法线（如果计算，会导致全球法线在块边缘处不连续，杜莹添加：2018-04-21）
};


#endif // OSGEARTH_ENGINE_MP_OPTIONS
