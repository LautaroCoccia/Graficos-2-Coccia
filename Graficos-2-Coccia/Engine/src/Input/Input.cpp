#include "Input.h"

#include "GLFW/glfw3.h"
#include <iostream>

namespace Engine
{
	static GLFWwindow* _window;
	static float _yaw = -90.0f;
	static float _pitch = 0;
	static float _lastX = 800 / 2;
	static float _lastY = 600 / 2;

	static bool _firstMouse =true;

	static float _sensitivity = 0.5f;
	static float camX;
	static float camZ;
	
	void Input::SetWindow(GLFWwindow* window)
	{
		_window = window;
	}

	bool Input::GetKey(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_PRESS);
	}

	bool Input::GetKeyUp(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_RELEASE);
	}
	/*void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)
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

	}*/
	GLFWwindow* Input::GetWindow()
	{
		return _window;
	}
}