#include "Light.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Light::Light(Renderer* renderer) 
	{
		_position = glm::vec3(0, 0, 0);
		_ambient.color = glm::vec3(1.0f, 1.0f, 1.0);
		_ambient.strength = 1.0f;
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
	void Light::SetPosition(glm::vec3 position)
	{
		_position = position;

	}

	void Light::Draw()
	{
		glm::vec3 lightColor = _ambient.color * _ambient.strength;
		//cout << lightColor.x << " " << lightColor.y << " " << lightColor.z << endl;
		_renderer->DrawLight(_vao, _vbo, lightColor, _position);
	}
}