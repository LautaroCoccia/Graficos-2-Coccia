#include "Light.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Light::Light(Renderer* renderer) 
	{
		_lightData._position = glm::vec3(0, 0, 0);
		_ambient.color = glm::vec3(1.0f, 1.0f, 1.0);
		_ambient.strength = 1.0f;

		//_material._ambient = glm::vec3(0.31f, 0.2f, 1.0f);
		//_material._diffuse = glm::vec3(0.31f, 0.2f, 1.0f);
		//_material._ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		//_material._diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		//_material._specular = glm::vec3(0.5f, 0.5f, 0.5f);
		//_material._shininess = 32.0f;

		_lightData._ambient = glm::vec3(0.2, 0.2, 0.2);
		_lightData._diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		_lightData._specular = glm::vec3(1, 1, 1);

		_renderer = renderer;

		_renderer->SetLightVertexArray(_vao,_vbo);
		_renderer->SetLightAttribPointer();
	}
	Light::~Light()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	}
	void Light::SetLightColorAmbient(glm::vec3 lightColor, float ambientStrength)
	{
		_ambient.color = lightColor;
		_ambient.strength = ambientStrength;
	}
	void Light::SetLightData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		_lightData._ambient = ambient;
		_lightData._diffuse = diffuse;
		_lightData._specular = specular;

	}
	void Light::SetPosition(glm::vec3 position)
	{
		_lightData._position = position;
	}

	void Light::Draw()
	{
		glm::vec3 lightColor = _ambient.color * _ambient.strength;
		_renderer->DrawLight(_lightData, lightColor);
	}
}