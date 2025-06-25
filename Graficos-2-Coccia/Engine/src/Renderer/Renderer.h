#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <string>
#include "..\Export\Export.h"
#include "..\Shader\Shader.h"
#include "..\Camera\Camera.h"
#include "glm\glm\mat4x4.hpp"

namespace Engine
{
	struct LightData
	{
		glm::vec3 _color;
		glm::vec3 _position;

		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;

		int _isActive;
	};
	struct DirectionLightData
	{
		glm::vec3 _direction;
	};

	struct PointLightData
	{
		glm::vec3 _position;

		float _constant;
		float _linear;
		float _quadratic;
	};

	struct SpotlightData
	{
		glm::vec3 _position;
		glm::vec3 _direction;

		float _cutOff;
		float _outerCutOff;

		float _constant;
		float _linear;
		float _quadratic;
	};
	struct Material
	{
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _shininess;
	};
	enum class TypeOfShape {
		Triangle,
		Quad
	};

	class EXPORT_API Renderer
	{
	private:
		Shader* _shader;
		Camera* _currentCamera;
		int _width;
		int _height;
		

	public:
		Renderer();
		~Renderer();
		
		int InitGlew();
		void SetVertexBuffer(int size, float* vertex, unsigned int &vao, unsigned int &vbo);
		void SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo);
		void SetVertexAttribPointer(bool shape, unsigned int &model);
		void CreateShader();
		void BindTexture(unsigned int& texture);
		void DisableTexture();
		void Draw(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount);
		void UpdateModel(glm::mat4 model, unsigned int updateShape);

		void StopShader();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);

		unsigned int GetShader();
		
		void SetDefaultCamera(int width, int height);
		void SetCurrentCamera(Camera* currentCamera);

		//Light
		void UpdateLightData(LightData lightData);
		void UpdateDirectLightData(LightData& light, DirectionLightData& directional);
		void UpdatePointLight(LightData& light, PointLightData& point, int i);
		void UpdateSpotLight(LightData& light, SpotlightData& spot, int i);
		//Tiene logica llamar al renderer para pasarle a la camara sus atributos??
		//void SetCameraValues(CameraType type, float near, float far);
		//void SetCameraPosition(float x, float y, float z);
	};
}
#endif