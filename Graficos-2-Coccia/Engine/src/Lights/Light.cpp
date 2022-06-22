#include "Light.h"

namespace Engine
{
	Light::Light(Renderer* renderer) 
	{
		//_light = glm::vec3(1.0f, 0.5f, 0.31f);
		_light = glm::vec3(1.0f, 1.0f, 1.0f);
		_renderer = renderer;

		_renderer->SetLightVertexArray(_vao,_vbo);
		_renderer->SetLightAttribPointer();
	}
	Light::~Light()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);

	}
	void Light::Draw()
	{
		_renderer->DrawLight(_vao, _vbo, _light);
	}

}