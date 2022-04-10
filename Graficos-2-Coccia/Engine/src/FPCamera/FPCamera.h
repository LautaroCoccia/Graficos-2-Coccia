#ifndef FPCAMERA
#include "../Camera/Camera.h"
namespace Engine
{
	class EXPORT_API FPCamera : virtual public Camera
	{
	public:
		FPCamera();
		FPCamera(CameraType type, float near, float far, float height, float width);
		~FPCamera();
		//void CameraInput(float deltaTime);
	};
}
#define FPCAMERA
#endif // !FPCAMERA

