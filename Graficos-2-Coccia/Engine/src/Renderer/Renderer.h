#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "..\Export\Export.h"
#include "..\Shader\Shader.h"
#include "..\Camera\Camera.h"
#include "glm\glm\mat4x4.hpp"

namespace Engine
{
	enum class TypeOfShape {
		Triangle,
		Quad
	};

	class EXPORT_API Renderer
	{
	private:
		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;
		Shader* _shader;
		Camera* _camera;

		unsigned int _VBO = 0; // VertexBufferObject
		unsigned int _VAO = 0; // VertexArrayObject
		unsigned int _EBO = 0; // ElementsBufferObject
	public:
		Renderer();
		~Renderer();
		
		int InitGlew();

		void CreateBuffers();
		void BindBuffers();
		void SetVertexShapeAttribPointer();
		void SetVertexSpriteAttribPointer();
		void SetVertexMaterialAttribPointer();


		void SetLightVertexArray(unsigned int& vao, unsigned int& vbo);
		void SetLightAttribPointer();

		void SetVertexBuffer(int size, float* vertex, unsigned int &vao, unsigned int &vbo);
		void SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo);
		void SetVertexAttribPointer(bool shape, unsigned int &model);
		void CreateShader();
		void BindTexture(unsigned int& texture);
		void DisableTexture();
		void DrawLight(glm::vec3& lightColor, glm::vec3& lightPos);
		void Draw(float* vertex, float vertexSize, int vertexCount, glm::vec3 normal);
		void UpdateModel(glm::mat4 model, unsigned int updateShape);

		void StopShader();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);

		//void SetCameraValues(CameraType type, float near, float far, float height, float width);
		//void SetCameraPosition(float x, float y, float z);
		void SetIndex(unsigned int shaderId);
		void UpdateMVP(glm::mat4 model);
		unsigned int GetShader();
		void SetCurrentCamera(Camera* camera);
	};
}
#endif