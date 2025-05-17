#ifndef TPCAMERA_H
#define	TPCAMERA_H

#include "Camera.h"

namespace Engine
{
	class EXPORT_API TPCamera : public Camera
	{
		float _offset;
		Transform _transformObj;
	public:
		
		TPCamera();
		TPCamera(Transform& transformObj);
		~TPCamera();

		void CameraInput(float deltatime);
		void UpdateView();
		
		void SetOffset(float offset);
		void SetTransform(Transform& transformObj);
	};

}
#endif

