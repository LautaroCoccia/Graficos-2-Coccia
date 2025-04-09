#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Camera::Camera()
	{
		_projection = glm::mat4(1.0f);
		_view = glm::mat4(1.0f);

		_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	Camera::~Camera()
	{

	}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
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

	void Camera::SetValues(CameraType type, float near, float far, std::string tag)
	{
		_tag = tag;

		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, near, far);
			break;

		case CameraType::Ortho:
			_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near, far);
			break;
		}
		_view = glm::mat4(1.0f);

	}

	void Camera::SetPosition(float x, float y, float z)
	{
		_cameraPos = glm::vec3(x, y, z);
	}

}