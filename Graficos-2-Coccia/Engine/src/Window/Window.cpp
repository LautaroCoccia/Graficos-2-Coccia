#include "Window.h"
#include "iostream"
#include "GLFW/glfw3.h"

namespace Engine
{
	Window::Window()
	{
		_width = 0;
		_height = 0;
	}

	Window::~Window()
	{

	}

	int Window::CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_width = width;
		_height = height;

		_window = glfwCreateWindow(width, height, title, monitor, NULL);

		if (!_window)
		{
			std::cout << "Error al iniciar la ventana" << std::endl;
			return 0;
		}
		return 1;
	}

	void Window::InitWindow()
	{
		glfwMakeContextCurrent(_window);
		glViewport(0, 0, _width, _height);

	}

	void Window::DestroyWindow()
	{
		glfwDestroyWindow(_window);
	}

	int Window::WindowShouldClose()
	{
		return glfwWindowShouldClose(_window);
	}
	void Window::SetWindowShouldClose()
	{
		glfwSetWindowShouldClose(_window, true);
	}
	void Window::SwapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	void Window::ClearWindow(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	GLFWwindow* Window::ReturnWindow()
	{
		return _window;
	}
	void Window::SetWindowSize(int width, int height)
	{
		_width = width;
		_height = height;
		glfwSetWindowSize(_window, _width, _height);
		//glfwGetFramebufferSize(_window, _width, _height);
		glViewport(0, 0, _width, _height);

	}

	void Window::GetWindowSize(int* width, int* height)
	{
		glfwGetWindowSize(_window, width, height);
	}
}