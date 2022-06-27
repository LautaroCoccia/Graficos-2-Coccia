#include "Cube.h"
#include <iostream>
namespace Engine
{
	Cube::Cube(const char* name, Renderer* renderer) : Entity()
	{
		_data = TextureImporter::ImportTexture(renderer,name);
		if (_data._nrChannels == 4)
			_alpha = true;

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
