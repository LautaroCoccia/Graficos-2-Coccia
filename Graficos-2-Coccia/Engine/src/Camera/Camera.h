#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
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

		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;

		std::string _tag;

		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;

	public:
		Camera();
		~Camera();

		//void UpdateCameraVectors();
		void UpdateView();
		void UpdateMVP(glm::mat4 model);
		void SetIndex(unsigned int shaderId);
		void SetValues(CameraType type, float near, float far, std::string tag);

		void SetPosition(float x, float y, float z);
		
		std::string GetTag();
	};
}

#endif