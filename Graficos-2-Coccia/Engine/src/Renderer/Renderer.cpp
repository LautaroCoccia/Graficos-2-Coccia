#include "Renderer.h"
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Renderer::Renderer()
	{		
		_width = 0;
		_height = 0;
		_shader = new Shader();
		_currentCamera = new Camera();
	}

	Renderer::~Renderer()
	{
		if (_shader != NULL)
		{
			delete _shader;
			_shader = NULL;
		}
		
		if (_currentCamera != NULL)
		{
			delete _currentCamera;
			_currentCamera = NULL;
		}
	}

	int Renderer::InitGlew()
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error in Glew Init" << std::endl;
			return -1;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	void Renderer::CreateShader()
	{
		_shader->SetShader("../Engine/shaders/Vertex.shader", "../Engine/shaders/Fragment.shader");
		glUseProgram(_shader->GetShader());

		_currentCamera->SetIndex(_shader->GetShader());//REVISAR
	}
	
	void Renderer::BindTexture(unsigned int& texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Renderer::DisableTexture()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisable(GL_TEXTURE_2D);
	}

	void Renderer::Draw(unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount)
	{
		glUseProgram(_shader->GetShader());
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Renderer::UpdateModel(glm::mat4 model, unsigned int modelUniform)
	{
		glUseProgram(_shader->GetShader());
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));

		_currentCamera->UpdateMVP(model);

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

	// ----------------------------

	unsigned int Renderer::GetShader() 
	{
		return _shader->GetShader();
	}

	void Renderer::SetDefaultCamera(int width, int height)
	{
		_currentCamera->SetValues(CameraType::Perspective, 0.1f, 100.0f, "default", width, height);
		_currentCamera->SetPosition(0, 0, 5);
	}
	void Renderer::SetCurrentCamera(Camera* currentCamera)
	{
		_currentCamera = currentCamera;
		//_currentCamera->SetWidthHeight();
		_currentCamera->SetIndex(_shader->GetShader());//REVISAR
	}

	void Renderer::UpdateLightData(LightData lightData)
	{
		glUseProgram(_shader->GetShader());
		//glBindVertexArray(vao);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo);


		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.ambient"), 1, &lightData._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.diffuse"), 1, &lightData._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.specular"), 1, &lightData._specular[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "light.position"), 1, &lightData._position[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "viewPos"), 1, &_currentCamera->GetPosition()[0]);
		//glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);
		//
		//glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	void Renderer::UpdateDirectLightData(LightData& light, DirectionLightData& directional)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 color = { 0.5f, 0.5f, 0.5f, 0.5f };

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "color"), 1, &color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "viewPos"), 1, &_currentCamera->GetPosition()[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "directionLight.color"), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "directionLight.direction"), 1, &directional._direction[0]);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "directionLight.ambient"), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "directionLight.diffuse"), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "directionLight.specular"), 1, &light._specular[0]);
		light._isActive = 1;
		glUniform1i(glGetUniformLocation(_shader->GetShader(), "directionLight.isActive"), light._isActive);

		glUseProgram(0);
	}
	void Renderer::UpdatePointLight(LightData& light, PointLightData& point, int i)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 color = { 0.5f, 0.5f, 0.5f, 0.5f };

		std::string fragComand = "pointLight[" + (char)i;
		std::cout << light._color.x << " " << light._color.y << " " << light._color.z << std::endl;

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "color"), 1, &color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "viewPos"), 1, &_currentCamera->GetPosition()[0]);
		light._isActive = 1;
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].isActive").c_str()), light._isActive);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].color").c_str()), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].position").c_str()), 1, &point._position[0]);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].constant").c_str()), point._constant);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].linear").c_str()), point._linear);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].quadratic").c_str()), point._quadratic);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].ambient").c_str()), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].diffuse").c_str()), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].specular").c_str()), 1, &light._specular[0]);

		glUniform1i(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].isActive").c_str()), light._isActive);

		glUseProgram(0);
	}
	void Renderer::UpdateSpotLight(LightData& light, SpotlightData& spot, int i)
	{
		glUseProgram(_shader->GetShader());

		glm::vec4 u_color = { 0.5f, 0.5f, 0.5f, 0.5f };

		std::string fragComand = "spotLight[" + (char)i;

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].color").c_str()), 1, &u_color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].viewPos").c_str()), 1, &_currentCamera->GetPosition()[0]);

		light._isActive = 1;
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].isActive").c_str()), light._isActive);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].cutOff").c_str()), spot._cutOff);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].color").c_str()), 1, &light._color[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].position").c_str()), 1, &spot._position[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].direction").c_str()), 1, &spot._direction[0]);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].outerCutOff").c_str()), spot._outerCutOff);

		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].constant").c_str()), spot._constant);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].linear").c_str()), spot._linear);
		glUniform1f(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].quadratic").c_str()), spot._quadratic);

		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].ambient").c_str()), 1, &light._ambient[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].diffuse").c_str()), 1, &light._diffuse[0]);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].specular").c_str()), 1, &light._specular[0]);

		glUniform1i(glGetUniformLocation(_shader->GetShader(), std::string(fragComand + "].isActive").c_str()), light._isActive);

		glUseProgram(0);
	}

}