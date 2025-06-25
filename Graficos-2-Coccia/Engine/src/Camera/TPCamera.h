#ifndef TPCAMERA_H
#define	TPCAMERA_H

#include "Camera.h"

namespace Engine
{
	class EXPORT_API TPCamera : public Camera
	{
		float _distance;
		glm::vec3 offset;
		glm::vec3* _targetPosition;
	public:
		
		TPCamera();
		TPCamera(glm::vec3* transformObj);
		~TPCamera();

		void CameraInput(float deltatime);
		void UpdateView();
		
		void SetOffset(float _distance);
		void SetTransform(Transform& transformObj);
		void SetTransform(glm::vec3* transformObj);
	};

}
#endif

