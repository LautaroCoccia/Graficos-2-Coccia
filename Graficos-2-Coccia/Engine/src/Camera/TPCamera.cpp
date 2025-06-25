#include "TPCamera.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	TPCamera::TPCamera()
	{
		_distance = 10;
		DefaultSettings();
		_targetPosition = nullptr;
		/*_transformObj.position = glm::vec3(0, 0, 0);
		_transformObj.rotation = glm::vec3(0, 0, 0);
		_transformObj.scale = glm::vec3(1, 1, 1);

		_transformObj.preb_position = _transformObj.position;
		_transformObj.preb_rotation = _transformObj.rotation;
		_transformObj.preb_scale = _transformObj.scale;
		
		_transformObj.forward = glm::vec3(0, 0, 1);
		_transformObj.up = glm::vec3(0, 1, 0);
		_transformObj.right = glm::vec3(0, 1, 0);*/
	}
	TPCamera::TPCamera(glm::vec3* transformObj)
	{

		_distance = 10;
		_targetPosition = transformObj;
	}

	TPCamera::~TPCamera()
	{

	}
	void TPCamera::SetOffset(float distance)
	{
		_distance = distance;
	}
	void TPCamera::SetTransform(Transform& transformObj)
	{

		 std::cout<<"trns" << "x " << transformObj.position.x << " y " << transformObj.position.y << "z" << transformObj.position.z<< std::endl;
	}
	void TPCamera::SetTransform(glm::vec3* transformObj)
	{
		_targetPosition = transformObj;
	}

	void TPCamera::CameraInput(float deltatime)
	{
		
		Camera::CameraInput(deltatime);
		
		offset.x = (-_transform.rotation.x) * _distance;
		offset.y = (-_transform.rotation.y) * _distance;
		offset.z = (-_transform.rotation.z) * _distance;
		
		_transform.forward = glm::normalize(_transform.rotation);

		_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));

		_transform.position = offset + *_targetPosition;
		std::cout<<"obj " << "x " << _targetPosition->x << " y " << _targetPosition->y << "z" << _targetPosition->z<< std::endl;
		//_transform.position = (_transform.rotation)*= + _transformObj.position;



		//_transformObj.rotation = glm::vec3(_transform.rotation.x, 0, _transform.rotation.z);

	}
	void TPCamera::UpdateView()
	{
		
		_view = glm::lookAt(_transform.position, *_targetPosition, _transform.up);
		//_view = glm::lookAt(_transform.position, _transformObj.position, _transform.up);

	}
}
