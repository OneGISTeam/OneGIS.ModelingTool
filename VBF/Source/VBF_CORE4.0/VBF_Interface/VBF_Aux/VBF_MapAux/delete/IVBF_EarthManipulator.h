
#ifndef IVBF_EARTHMANIPULATOR
#define IVBF_EARTHMANIPULATOR

#include "VBF_MapAuxExport.h"
#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include "../../../VBF_Public/VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h"

class VBF_MAPAUX_EXPORT IVBF_EarthManipulator : public IVBF_CameraManipulatorImpl<IVBF_CameraManipulator>
{
public:
	virtual ~IVBF_EarthManipulator() {}

public:
	virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0, bool testFlag = false ) = 0;

	virtual CVBF_Viewpoint getViewpoint() const = 0;

	/**
	* Move the focal point of the camera using deltas (normalized screen coords).
	*/
	virtual void pan( double dx, double dy ) = 0;

	/**
	* Rotate the camera (dx = azimuth, dy = pitch) using deltas (radians).
	*/
	virtual void rotate( double dx, double dy ) = 0;

	/**
	* Zoom the camera using deltas (dy only)
	*/
	virtual void zoom( double dx, double dy ) = 0;
	
	/**
	* Zoom the camera using deltas (dy only)
	*/
	virtual void rotateWithCamCenter( double dx, double dy ) = 0;
	
	/**
	* Zoom the camera using deltas (dy only)
	*/
	virtual void panThroughCtrl(double dx, double dy) = 0;
};

#endif // IVBF_EARTHMANIPULATOR
