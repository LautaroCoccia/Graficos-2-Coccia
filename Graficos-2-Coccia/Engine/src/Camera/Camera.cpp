#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"
#include "../Input/Input.h"

namespace Engine
{
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	float _yaw = -90.f;
	float _pitch = 0.0f;
	float _lastX = 800.f / 2;
	float _lastY = 600.f / 2;

	bool _firstMouse = true;

	float _sensitivity = 1.5f;
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
		_yaw = -90;//esto tiene que ser asi.

		_direction.x = cos(glm::radians(_yaw));
		_direction.z = sin(glm::radians(_yaw));
	
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
	
	void MouseCallback(GLFWwindow* window, double xpos, double ypos)
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

		glfwSetCursorPosCallback(Input::GetWindow(), MouseCallback);
		glfwSetInputMode(Input::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		_direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_direction.y = sin(glm::radians(_pitch));
		_direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_cameraFront = glm::normalize(_direction);
		_cameraRight = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _cameraFront));
		_cameraUp= glm::normalize(glm::cross(_cameraFront, _cameraRight));
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