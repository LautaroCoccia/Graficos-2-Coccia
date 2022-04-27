#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"
#include "../Input/Input.h"
#include <iostream>
namespace Engine
{
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	float _yaw = -90.f;
	float _pitch = 0.0f;
	float _lastX = 800.f / 2;
	float _lastY = 600.f / 2;

	bool _firstMouse = true;

	float _sensitivity = 0.5f;

	Camera::Camera() : Entity()
	{
		DefaultSettings();
	}

	Camera::Camera(CameraType type, float near, float far, float height, float width, float sensibility) : Entity()
	{
		DefaultSettings();
		//SetCameraValues(type, near, far, height, width);
	}

	Camera::~Camera()
	{

	}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_transform.position, _transform.position + _transform.forward, _transform.up);
	}

	/*void Camera::UpdateMVP(glm::mat4 model)
	{
		UpdateView();
		glUniformMatrix4fv(_modelInd, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(_viewInd, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_projectionInd, 1, GL_FALSE, glm::value_ptr(_projection));
	}*/

	/*void Camera::SetIndex(unsigned int shaderId)
	{
		_modelInd = glGetUniformLocation(shaderId, "model");
		_viewInd = glGetUniformLocation(shaderId, "view");
		_projectionInd = glGetUniformLocation(shaderId, "projection");
	}*/

	void Camera::SetCameraValues(CameraType type, float near, float far,float height, float width, float sensibility)
	{
		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f), height / width, near, far);
			_yaw = -90.f;
			_pitch = 0.0f;
			_lastX = width / 2;
			_lastY = height / 2;

			_firstMouse = true;

			_sensitivity = sensibility;
			break;

		case CameraType::Ortho:
			_projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, near, far);
			break;
		}
		_view = glm::mat4(1.0f);
	}
	void Camera::LookAt(glm::vec3 target)
	{
		_view = glm::lookAt(_transform.position, _transform.position + target, _transform.up);
	}
	void Camera::SetCameraPosition(float x, float y, float z)
	{
		_transform.position = glm::vec3(x, y, z);
	}
	void Camera::SetCameraPosition(glm::vec3 position)
	{
		_transform.position = position;
	}
	void Camera::SetCameraRotation(float x, float y, float z)
	{

	}
	void Camera::SetCameraRotation(glm::vec3 vec)
	{

	}
	void Camera::SetCameraDirection(float x, float y, float z)
	{
		_transform.rotation = glm::normalize(_transform.position - glm::vec3(x, y, z));
		UpdateView();
	}
	void Camera::SetCameraMode(CameraMode mode)
	{
		_currentMode = mode;
	}
	void Camera::DefaultSettings()
	{
		_yaw = -90.f;
		_pitch = 0.0f;
		_lastX = 800.f / 2;
		_lastY = 600.f / 2;

		_firstMouse = true;

		_sensitivity = 0.5f;

		_transform.rotation.x = cos(glm::radians(_yaw));
		_transform.rotation.z = sin(glm::radians(_yaw));
	
		_camPos = glm::vec3(0, 0, 3);
		_transform.position = glm::vec3(0.0f, 0.0f, 3.0f);

		_transform.rotation = glm::normalize(_transform.position - _transform.position);
		
		_transform.up = glm::vec3(0.0f, 1.0f, 0.0f);
		_transform.right = glm::normalize(glm::cross(_transform.up, _transform.rotation));

		_transform.up = glm::cross(_transform.rotation, _transform.right);

		_transform.forward = glm::vec3(0.0f, 0.0f, -1.0f);

		_projection = glm::perspective(glm::radians(45.0f), 1200.0f / 600.0f, 0.1f, 100.0f);
		_view = glm::lookAt(_transform.position, _transform.position , _transform.up);
		_view = glm::mat4(1.0f);

		_currentMode = CameraMode::FlyCam;
	}
	void Camera::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (_firstMouse)
		{
			_lastX = xpos;
			_lastY = ypos;
			_firstMouse = false;
		}

		float xoffset = xpos - _lastX;
		float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top
		_lastX = xpos;
		_lastY = ypos;

		xoffset *= _sensitivity;
		yoffset *= _sensitivity;

		_yaw += xoffset;
		_pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
		
	}
	void Camera::CameraInput(float deltaTime, Transform& transformObj)
	{
		glfwSetInputMode(Input::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(Input::GetWindow(), MouseCallback);


		switch (_currentMode)
		{
		case Engine::CameraMode::FlyCam:
			_transform.rotation.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
			_transform.rotation.y = sin(glm::radians(_pitch));
			_transform.rotation.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
			
			_transform.forward = glm::normalize(_transform.rotation);
			_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
			_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));
			
			if (Input::GetKey(Keycode::W))
				_transform.position += cameraSpeed * _transform.forward * deltaTime;
			if (Input::GetKey(Keycode::S))
				_transform.position -= cameraSpeed * _transform.forward * deltaTime;
			if (Input::GetKey(Keycode::A))
				_transform.position -= glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;
			if (Input::GetKey(Keycode::D))
				_transform.position += glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;

			break;
		case Engine::CameraMode::FPCamera:

			_transform.rotation.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
			_transform.rotation.y = sin(glm::radians(_pitch));
			_transform.rotation.z = sin(glm::radians(_yaw))  * cos(glm::radians(_pitch));
			
			
			//std::cout << _transform.forward.x << " "<< _transform.forward.y << " "<< _transform.forward.z << std::endl;
			
			_transform.forward = glm::normalize(_transform.rotation);
			_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
			_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));

			transformObj.rotation = glm::vec3(_transform.rotation.x, 0, _transform.rotation.z);
			//if (_cameraTarget != NULL)
			//{

			//_transform.position = transformObj.position;
			//transformObj.rotation = glm::vec3(_transform.rotation.x, 0, _transform.rotation.z);
			
			//transformObj.forward = glm::normalize(transformObj.rotation);
			//transformObj.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), transformObj.forward));
			//transformObj.up = glm::normalize(glm::cross(transformObj.forward, transformObj.right));
			//}
			//else
			//	std::cout << "NULL _camera target" << std::endl;

			//_transform.forward.y = 0;
			//if (Input::GetKey(Keycode::W))
			//	_transform.position += cameraSpeed * glm::vec3(_transform.forward.x, 0, _transform.forward.z)* deltaTime;
			//if (Input::GetKey(Keycode::S))
			//	_transform.position -= cameraSpeed * glm::vec3(_transform.forward.x, 0, _transform.forward.z) * deltaTime;
			//if (Input::GetKey(Keycode::A))
			//	_transform.position -= glm::normalize(glm::cross(glm::vec3(_transform.forward.x, 0, _transform.forward.z), _transform.up)) * cameraSpeed * deltaTime;
			//if (Input::GetKey(Keycode::D))
			//	_transform.position += glm::normalize(glm::cross(glm::vec3(_transform.forward.x, 0, _transform.forward.z), _transform.up)) * cameraSpeed * deltaTime;

			break;
		case Engine::CameraMode::TPCamera:
			break;
		default:
			break;
		}
	}
	glm::mat4 Camera::GetView()
	{
		return _view;
	}
	glm::mat4 Camera::GetProjection()
	{
		return _projection;
	}
	glm::vec3 Camera::GetRotation()
	{
		return glm::vec3 (_transform.rotation.x, 0, _transform.rotation.z);
	}
	void Camera::TriggerCollision(Entity* other){ }

}