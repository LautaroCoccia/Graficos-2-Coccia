#include "Cube3D.h"

namespace Engine
{
	Cube3D::Cube3D(Renderer* renderer)
	{
		_renderer = renderer;
		_renderer->SetVertexBuffer(sizeof(_vertices), _vertices, _vao, _vbo);
		_renderer->SetIndexBuffer(sizeof(_indices), _indices, _ebo);
	}
	Cube3D::~Cube3D()
	{

	}
	void Cube3D::Draw()
	{
		
		//_renderer->BindTexture(_data._diffuse);
		//_renderer->SetCubeVertexAttribPointer(_modelUniform);
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		_renderer->DrawCube(_vao, _vbo, _ebo, _vertices, _indicesSize);

		//_renderer->DisableTexture();
		
	}
	void Cube3D::SetColor(ENTITY_COLOR color) { }

	void Cube3D::SetColor(float r, float g, float b) { }

	void Cube3D::TriggerCollision(Entity* other) { }

}