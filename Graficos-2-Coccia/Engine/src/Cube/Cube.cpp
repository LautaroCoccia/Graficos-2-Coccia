#include "Cube.h"
#include <iostream>
namespace Engine
{
	Cube::Cube(const char* filePath, Renderer* renderer) : Entity()
	{
		TI.ImportTexture(renderer, filePath, _data);
		if (_data._nrChannels == 4)
			_alpha = true;

		_renderer = renderer;

		_vertexSize = sizeof(_vertex);

		_renderer->SetVertexSpriteAttribPointer();

		_renderer->SetVertexBuffer(_vertexSize, vertexNormals, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, index, _ebo);
		_renderer->SetVertexAttribPointer(false, _modelUniform);
		//_renderer->CreateBuffers();
		//_renderer->BindBuffers();
		

		//for (int i = 0; i < 6; i++)
		//{
		//	cube[i] = new Sprite(renderer);
		//	cube[i]->InitTexture();
		//	cube[i]->ImportTexture(name);
		//	cube[i]->SetPosition(facesPositions[i]);
		//	cube[i]->SetRotation(facesRotations[i]);
		//}
	}
	Cube::~Cube()
	{
		//for (int i = 5; i >= 6; i--)
		//{
		//	if (cube[i] != NULL)
		//		delete cube[i];
		//}
	}
	void Cube::UpdatePosition()
	{
		//for (int i = 0; i < 6; i++)
		//{
		//	cube[i]->SetPosition(facesPositions[i] + _transform.position);
		//}
	}

	void Cube::Draw()
	{
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

		//_textureImporter->BindTexture(_textureData._texture);
		_renderer->BindTexture(_data._texture);
		_renderer->DrawCube(_vao, _vbo, _ebo, _vertices, _vertexSize, sizeof(index) / sizeof(float));

		_renderer->DisableTexture();
		//for (int i = 0; i < 6; i++)
		//{
		//	cube[i]->Draw();
		//}
	}
	void Cube::TriggerCollision(Entity* other)
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
