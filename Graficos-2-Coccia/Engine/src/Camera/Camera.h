#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
#include "..\Window\Window.h"
#include "..\Export\Export.h"
//#include "..\Entity\Entity.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};
	enum class CameraMode {
		FlyCam,
		FPCamera,
		TPCamera
	};
	class EXPORT_API Camera
	{
	private:
		
		const float cameraSpeed = 10.0f; // adjust accordingly

		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		glm::vec3 _cameraTarget;
		glm::vec3 _cameraDirection;
		glm::vec3 _cameraRotation;
		glm::vec3 _cameraRight;
		glm::vec3 _up;

		glm::vec3 _camPos;
		CameraMode _currentMode;

	public:
		Camera();
		Camera(CameraType type, float near, float far, float height, float width, float sensibility);
		~Camera();

		//void UpdateCameraVectors();
		void UpdateView();
		//void UpdateMVP(glm::mat4 model);
		//void SetIndex(unsigned int shaderId);
		void SetCameraValues(CameraType type, float near, float far, float height, float width, float sensibility);
		void LookAt(glm::vec3 target);
		void SetCameraPosition(float x, float y, float z);
		void SetCameraPosition(glm::vec3 position);
		void SetCameraRotation(float x, float y, float z);
		void SetCameraRotation(glm::vec3 vec);
		void SetCameraDirection(float x, float y, float z);
		void SetCameraMode(CameraMode mode);
		void DefaultSettings();
		void CameraInput(float deltaTime); 
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::vec3 GetRotation();
	};
}
#endif