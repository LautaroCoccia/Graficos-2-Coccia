#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"
#include "../Input/Input.h"

namespace Engine
{
	Camera::Camera()
	{
		DefaultSettings();
	}
	Camera::Camera(CameraType type, float near, float far, float height, float width)
	{
		DefaultSettings();
		//SetCameraValues(type, near, far, height, width);
	}
	Camera::~Camera()
	{

	}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
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

	void Camera::SetCameraValues(CameraType type, float near, float far,float height, float width)
	{
		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f), height / width, near, far);
			break;

		case CameraType::Ortho:
			_projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, near, far);
			break;
		}
		_view = glm::mat4(1.0f);
	}

	void Camera::LookAt(glm::vec3 target)
	{
		_view = glm::lookAt(_cameraPos, _cameraPos + target, _cameraUp);
	}
	void Camera::SetCameraPosition(float x, float y, float z)
	{
		_cameraPos = glm::vec3(x, y, z);
	}
	void Camera::SetCameraRotation(float x, float y, float z)
	{

	}
	void Camera::SetCameraRotation(glm::vec3 vec)
	{

	}
	void Camera::SetCameraDirection(float x, float y, float z)
	{
		_cameraDirection = glm::normalize(_cameraPos - glm::vec3(x, y, z));
		UpdateView();
	}
	void Camera::DefaultSettings()
	{

		_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		_cameraDirection = glm::normalize(_cameraPos - _cameraTarget);
		
		_up = glm::vec3(0.0f, 1.0f, 0.0f);
		_cameraRight = glm::normalize(glm::cross(_up, _cameraDirection));

		_cameraUp = glm::cross(_cameraDirection, _cameraRight);

		_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

		_projection = glm::perspective(glm::radians(45.0f), 1200.0f / 600.0f, 0.1f, 100.0f);
		_view = glm::lookAt(_cameraPos, _cameraPos +_cameraTarget, _up);
		_view = glm::mat4(1.0f);
	}
	void Camera::CameraInput(float deltaTime)
	{
		if (Input::GetKey(Keycode::W))
			_cameraPos += cameraSpeed * _cameraFront;
		if (Input::GetKey(Keycode::S))
			_cameraPos -= cameraSpeed * _cameraFront;
		if (Input::GetKey(Keycode::A))
			_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
		if (Input::GetKey(Keycode::D))
			_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
	}
	glm::mat4 Camera::GetView()
	{
		return _view;
	}
	glm::mat4 Camera::GetProjection()
	{
		return _projection;
	}
}