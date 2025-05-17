#include "TPCamera.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	TPCamera::TPCamera()
	{
		_offset = 10;
		DefaultSettings();
		
		_transformObj.position = glm::vec3(0, 0, 0);
		_transformObj.rotation = glm::vec3(0, 0, 0);
		_transformObj.scale = glm::vec3(1, 1, 1);

		_transformObj.preb_position = _transformObj.position;
		_transformObj.preb_rotation = _transformObj.rotation;
		_transformObj.preb_scale = _transformObj.scale;
		
		_transformObj.forward = glm::vec3(0, 0, 1);
		_transformObj.up = glm::vec3(0, 1, 0);
		_transformObj.right = glm::vec3(0, 1, 0);
	}
	TPCamera::TPCamera(Transform& transformObj)
	{
		_offset = 10;
		_transformObj = transformObj;

	}

	TPCamera::~TPCamera()
	{

	}
	void TPCamera::SetOffset(float offset)
	{
		_offset = offset;
	}
	void TPCamera::SetTransform(Transform& transformObj)
	{

		_transformObj = transformObj;
		 std::cout<<"trns" << "x " << transformObj.position.x << " y " << transformObj.position.y << "z" << transformObj.position.z<< std::endl;
	}

	void TPCamera::CameraInput(float deltatime)
	{
		
		Camera::CameraInput(deltatime);
		glm::vec3 asd = _transform.rotation;
		
		_transform.rotation.x = (-_transform.rotation.x) * _offset;
		_transform.rotation.y = (-_transform.rotation.y) * _offset;
		_transform.rotation.z = (-_transform.rotation.z) * _offset;
		
		_transform.forward = glm::normalize(_transform.rotation);

		_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));

		_transform.position = asd + _transformObj.position;
		std::cout<<"obj " << "x " << _transformObj.position.x << " y " << _transformObj.position.y << "z" << _transformObj.position.z<< std::endl;
		//_transform.position = (_transform.rotation)*= + _transformObj.position;



		_transformObj.rotation = glm::vec3(_transform.rotation.x, 0, _transform.rotation.z);

	}
	void TPCamera::UpdateView()
	{
		_view = glm::lookAt(_transform.position, _transformObj.position, _transform.up);

	}
}
