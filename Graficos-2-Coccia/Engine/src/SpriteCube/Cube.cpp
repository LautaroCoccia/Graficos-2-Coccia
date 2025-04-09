#include "Cube.h"

namespace Engine
{
	Cube::Cube(Renderer* renderer, const char* name, float x, float y, float z) : Entity (renderer)
	{
		walls = new Sprite(renderer);
		walls->InitTexture();
		walls->ImportTexture(name);
		_transform.position.x = x;
		_transform.position.y = y;
		_transform.position.z = z;
		
		walls->_transform.position.x = x;
		walls->_transform.position.y = y;
		walls->_transform.position.z = z;
	}
	Cube::~Cube()
	{
	}
	void Cube::Draw()
	{
		walls->Draw();
	}
	void Cube::SetColor(ENTITY_COLOR color) { }

	void Cube::SetColor(float r, float g, float b) { }

	void Cube::TriggerCollision(Entity* other) { }
}