#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "..\Export\Export.h"
#include "..\Entity\Entity.h"
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
#include "..\Window\Window.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};

	class EXPORT_API Camera : public Entity
	{
	private:

		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;

		std::string _tag;

		glm::mat4 _projection;
		glm::mat4 _view;
		
		float _width;
		float _height;
		const float cameraSpeed = 10.0f; // adjust accordingly

		void DefaultSettings();

	public:
		Camera();
		Camera(CameraType type, float near, float far, float height, float width, float sensibility);
		~Camera();
		//void UpdateCameraVectors();
		void UpdateView();
		void UpdateMVP(glm::mat4 model);
		void SetIndex(unsigned int shaderId);
		void SetValues(CameraType type, float near, float far, std::string tag, int windowWidth, int WindowHeight);
		void SetWidthHeight(int width, int height);
		void SetPosition(float x, float y, float z);
		void CameraInput(float deltaTime);
		

		std::string GetTag();

		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif