#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"
#include <iostream>
namespace Engine
{
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	float _yaw = -90.0f;
	float _pitch = 0;
	float _lastX = 800 / 2;
	float _lastY = 600 / 2;

	bool _firstMouse = true;

	float _sensitivity = 0.5f;
	float camX;
	float camZ;

	Camera::Camera() : Entity()
	{
		DefaultSettings();
	}

	Camera::~Camera()
	{

	}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_transform.position, _transform.position + _transform.forward, _transform.up);
	}

	void Camera::UpdateMVP(glm::mat4 model)
	{
		UpdateView();
		//Mover a renderer?
		glUniformMatrix4fv(_modelInd, 1, GL_FALSE, glm::value_ptr(model));//Reemplazar con un getter de model 
		glUniformMatrix4fv(_viewInd, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_projectionInd, 1, GL_FALSE, glm::value_ptr(_projection));
	}

	void Camera::SetIndex(unsigned int shaderId)
	{
		_modelInd = glGetUniformLocation(shaderId, "model");
		_viewInd = glGetUniformLocation(shaderId, "view");
		_projectionInd = glGetUniformLocation(shaderId, "projection");
	}

	void Camera::SetValues(CameraType type, float near, float far, std::string tag,int windowWidth,int WindowHeight)
	{
		_width = windowWidth;
		_height = WindowHeight;
		_lastX = windowWidth / 2;
		_lastY = WindowHeight / 2;
		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f),(_width / _height), near, far);
			break;

		case CameraType::Ortho:
			_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near, far);
			break;
		}
		_view = glm::mat4(1.0f);

	}
	void Camera::SetWidthHeight(int width, int height)
	{
		_width = width;
		_height = height;
		_lastX = _width / 2;
		_lastY = _height / 2;
	}
	void Camera::SetPosition(float x, float y, float z)
	{
		_transform.position = glm::vec3(x, y, z);
	}

	void Camera::DefaultSettings()
	{


		/*_transform.rotation.x = 0;
		_transform.rotation.y = 0;
		_transform.rotation.z = 5;
		
		_transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
		_transform.forward = glm::vec3(0.0f, 0.0f, -1.0f);
		_transform.up = glm::vec3(0.0f, 1.0f, 0.0f);
		_transform.up = glm::cross(_transform.rotation, _transform.right);
		_transform.right = glm::cross(_transform.up, _transform.rotation);

		_transform.forward = glm::vec3(0.0f, 0.0f, 1.0f);
		*/
		_transform.rotation.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_transform.rotation.y = sin(glm::radians(_pitch));
		_transform.rotation.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

		_transform.forward = glm::normalize(_transform.rotation);
		_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));
		std::cout << _transform.right.x << " " << _transform.right.y << " " << _transform.right.z << std::endl;
		std::cout << _transform.rotation.x << " " << _transform.rotation.y << " " << _transform.rotation.z << std::endl;

		_projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 100.0f);
		_view = glm::lookAt(_transform.position, _transform.position, _transform.up);
		_view = glm::mat4(1.0f);
		
		//_currentMode = CameraMode::FlyCamera;
	}
	void Camera::CameraInput(float deltaTime)
	{
		glfwSetInputMode(Input::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(Input::GetWindow(), MouseCallback);

		_transform.rotation.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_transform.rotation.y = sin(glm::radians(_pitch));
		_transform.rotation.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		
		_transform.forward = glm::normalize(_transform.rotation);
		_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));

//----------------------------------------------------------------------------------------------		
		/*if (Input::GetKey(Keycode::W))
			_transform.position += cameraSpeed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::S))
			_transform.position -= cameraSpeed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::A))
			_transform.position -= glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;
		if (Input::GetKey(Keycode::D))
			_transform.position += glm::normalize(glm::cross(_transform.forward, _transform.up)) * cameraSpeed * deltaTime;*/

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

	void Camera::SetColor(ENTITY_COLOR color) { }

	void Camera::SetColor(float r, float g, float b) { }

	void Camera::TriggerCollision(Entity* other) { }
}