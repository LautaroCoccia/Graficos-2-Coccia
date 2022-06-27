#include "Light.h"

namespace Engine
{
	Light::Light(Renderer* renderer) : Entity()
	{
		//_light = glm::vec3(1.0f, 0.5f, 0.31f);
		_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		_ambientStrength = 1.0f;
		_renderer = renderer;

		_renderer->SetLightVertexArray(_vao,_vbo);
		_renderer->SetLightAttribPointer();
		_transform.position = glm::vec3(0, 10, 0);
	}
	Light::~Light()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	}
	void Light::SetLightColor(glm::vec3 lightColor, float ambientStrength)
	{
		_lightColor = lightColor;
		_ambientStrength = ambientStrength;
	}
	void Light::Draw()
	{
		glm::vec3 result = _lightColor * _ambientStrength;
		_renderer->DrawLight(_vao, _vbo, result,_transform.position);
	}
	void Light::TriggerCollision(Entity* other)
	{
		if (!other->GetStaticState())
		{
			glm::vec3 newPos = _transform.position;
			ReturnToPrevPosition();
			newPos -= _transform.position;

			other->SetPosition(other->_transform.position + newPos);
		}
		else
		{
			ReturnToPrevPosition();
		}
	}
}