#include "Cube.h"
#include <iostream>
namespace Engine
{
	Cube::Cube(const char* name, Renderer* renderer) : Entity()
	{
		for (int i = 0; i < 6; i++)
		{
			cube[i] = new Sprite(renderer);
			cube[i]->ImportTexture(name);
			cube[i]->SetPosition(facesPositions[i]);
		}
	}
	Cube::~Cube()
	{

	}
	void Cube::Draw()
	{
		for (int i = 0; i < 6; i++)
		{
			cube[i]->Draw();
		}
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
