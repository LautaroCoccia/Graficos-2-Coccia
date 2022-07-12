#include "Renderer.h"
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Renderer::Renderer()
	{		
		_shader = new Shader();
		_camera  = new Camera();
	}

	Renderer::~Renderer()
	{
		if (_shader != NULL)
		{
			delete _shader;
			_shader = NULL;
		}

		if (_camera != NULL)
		{
			_camera = NULL;
		}
	}

	int Renderer::InitGlew()
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error in Glew Init" << std::endl;
			return -1;
		}

		//glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::SetLightVertexArray(unsigned int& vao, unsigned int& vbo)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// we only need to bind to the VBO, the container's VBO's data already contains the data.
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}
	void Renderer::SetLightAttribPointer()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	void Renderer::SetVertexBuffer(int size, float* vertex, unsigned int& vao, unsigned int& vbo)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
	}

	void Renderer::SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo)
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, index, GL_STATIC_DRAW);
	}

	void Renderer::SetVertexAttribPointer(bool shape, unsigned int& model)
	{
		if (shape)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		else
		{
			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}

		model = glGetUniformLocation(GetShader(), "model");
	}
	void Renderer::CreateBuffers()
	{
		glGenVertexArrays(1, &_VAO); // first: Specifies the number of vertex array object 
									// second: the generated vertex array object names are stored 
		glGenBuffers(1, &_VBO);		//first: the number of buffer object 
		glGenBuffers(1, &_EBO);		//second: an array in which the generated buffer object names are stored 

		
	}
	void Renderer::BindBuffers()
	{
		glBindVertexArray(_VAO);// Specifies the name of the vertex array to bind 
		glBindBuffer(GL_ARRAY_BUFFER, _VBO); //first: type buffer to bound 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO); //second: the buffer 
	}
	void Renderer::SetVertexShapeAttribPointer()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void Renderer::SetVertexSpriteAttribPointer()
	{
		// position attribute 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute 
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	void Renderer::SetCubeVertexAttribPointer(unsigned int& model)
	{
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(3);

		//Texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		model = glGetUniformLocation(GetShader(), "model");
	}
	void Renderer::CreateShader()
	{
		_shader->SetShader("../Engine/shaders/Vertex.vert", "../Engine/shaders/Fragment.frag");
		glUseProgram(_shader->GetShader());

		SetIndex(_shader->GetShader());

		glUniform1i(glGetUniformLocation(_shader->GetShader(), "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1);
	}
	
	void Renderer::BindTexture(unsigned int& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE0);

		/*glm::vec3 ambient = glm::vec3(1, 1, 1);
		glm::vec3 diffuse = glm::vec3(0.1, 0.5f, 0.31f);
		glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
		float shininess = 256;

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.ambient"), 1, &ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.diffuse"), 1, &diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1, &specular[0]);
		glUniform1fv(glGetUniformLocation(_shader->GetShader(), "material.shininess"), 1, &shininess); */
	}
	void Renderer::BindTextures(unsigned int& texture1, unsigned int& texture2)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
	}
	void Renderer::DisableTexture()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisable(GL_TEXTURE_2D);
	}
	void Renderer::DrawLight(LightData lightData, glm::vec3 &lightColor)
	{ 
		glUseProgram(_shader->GetShader());
		//glBindVertexArray(vao);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		 
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.ambient"), 1, &lightData._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.diffuse"), 1, &lightData._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.specular"), 1, &lightData._specular[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.position"),1, &lightData._position[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "viewPos"),1, &_camera->GetPosition()[0]);
		//glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);
		//
		//glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	void Renderer::Draw(bool alpha, unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount)
	{
		glUseProgram(_shader->GetShader());
		if (alpha)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		//BindBuffers();
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
		//glm::vec3 objectColor = glm::vec3(1, 1, 1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	void Renderer::DrawCube(bool alpha,unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount)
	{
		glUseProgram(_shader->GetShader());

		if (alpha) // TODO: clean pls
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		//BindBuffers();
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);

		//glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glm::vec3 objectColor = glm::vec3(1, 1, 1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	void Renderer::UpdateModel(glm::mat4 model, unsigned int modelUniform)
	{
		glUseProgram(_shader->GetShader());
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));

		UpdateMVP(model);

		glUseProgram(0);
	}

	void Renderer::UpdateMaterial(Material& material)
	{
		glUseProgram(_shader->GetShader());


		//glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1, &material._specular[0]);
		glUniform1i(glGetUniformLocation(_shader->GetShader(), "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), "material.shininess"), material._shininess);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.ambient"), 1, &material._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.diffuse"), 1, &material._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "material.specular"), 1, &material._specular[0]);
		glUniform1fv(glGetUniformLocation(_shader->GetShader(), "material.shininess"), 1, &material._shininess);
		glUseProgram(0);
	}
	void Renderer::StopShader()
	{
		if (_shader != NULL)
		{
			_shader->ClearShader();
		}
	}

	void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	/*void Renderer::SetCameraValues(CameraType type, float near, float far, float height, float width)
	{
		_camera->SetCameraValues(type, near, far,height,width);
	}

	void Renderer::SetCameraPosition(float x, float y, float z)
	{
		_camera->SetCameraPosition(x, y, z);
	}*/

	// ----------------------------
	void Renderer::UpdateMVP(glm::mat4 model)
	{
		_camera->UpdateView();
		glUniformMatrix4fv(_modelInd, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(_viewInd, 1, GL_FALSE, glm::value_ptr(_camera->GetView()));
		glUniformMatrix4fv(_projectionInd, 1, GL_FALSE, glm::value_ptr(_camera->GetProjection()));
	}
	void Renderer::SetIndex(unsigned int shaderId)
	{
		_modelInd = glGetUniformLocation(shaderId, "model");
		_viewInd = glGetUniformLocation(shaderId, "view");
		_projectionInd = glGetUniformLocation(shaderId, "projection");
	}
	unsigned int Renderer::GetShader() 
	{
		return _shader->GetShader();
	}
	void Renderer::SetCurrentCamera(Camera* camera)
	{
		_camera = camera;
	}
}