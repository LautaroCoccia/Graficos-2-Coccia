#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
#include "..\Window\Window.h"
#include "..\Export\Export.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};

	class EXPORT_API Camera
	{
	private:
		
		const float cameraSpeed = 0.05f; // adjust accordingly

		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		glm::vec3 _cameraTarget;
		glm::vec3 _cameraDirection;
		glm::vec3 _cameraRight;
		glm::vec3 _up;
	public:
		Camera();
		Camera(CameraType type, float near, float far, float height, float width);
		~Camera();

		//void UpdateCameraVectors();
		void UpdateView();
		//void UpdateMVP(glm::mat4 model);
		//void SetIndex(unsigned int shaderId);
		void SetCameraValues(CameraType type, float near, float far, float height, float width);
		void LookAt(glm::vec3 target);
		void SetCameraPosition(float x, float y, float z);
		void SetCameraRotation(float x, float y, float z);
		void SetCameraRotation(glm::vec3 vec);
		void SetCameraDirection(float x, float y, float z);
		void DefaultSettings();
		void CameraInput(float deltaTime);
		glm::mat4 GetView();
		glm::mat4 GetProjection();
	};
}

#endif