#include "Light.h"

namespace Engine
{
	Light::Light(Renderer* renderer) 
	{
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
		_renderer->DrawLight(_vao, _vbo);
	}

}