#include "FPCamera.h"

namespace Engine
{
	FPCamera::FPCamera()
	{
		DefaultSettings();
	}
	FPCamera::~FPCamera()
	{

	}
	void FPCamera::CameraInput(float deltaTime)
	{
		ProcessMouseMovement();

		if (Input::GetKey(Keycode::W))
			_transform.position += cameraSpeed * glm::vec3(_transform.forward.x, 0, _transform.forward.z) * deltaTime;
		if (Input::GetKey(Keycode::S))
			_transform.position -= cameraSpeed * glm::vec3(_transform.forward.x,0, _transform.forward.z) * deltaTime;
		if (Input::GetKey(Keycode::A))
			_transform.position -= glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;
		if (Input::GetKey(Keycode::D))
			_transform.position += glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;

		
	}


}