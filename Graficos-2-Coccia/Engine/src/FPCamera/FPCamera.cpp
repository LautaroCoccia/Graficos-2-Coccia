#include "FPCamera.h"
namespace Engine
{
	FPCamera::FPCamera()
	{

	}
	FPCamera::FPCamera(CameraType type, float near, float far, float height, float width):Camera( type, near, far, height, width)
	{
		
	}
	FPCamera::~FPCamera()
	{


	}
	/*void FPCamera::CameraInput(float deltaTime)
	{

	}*/
}