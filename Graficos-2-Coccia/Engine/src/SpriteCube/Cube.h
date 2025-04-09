#ifndef CUBE_H
#define CUBE_H
#include "../Export/Export.h"
#include "../Sprite/Sprite.h"

namespace Engine
{
	class EXPORT_API Cube : public Entity
	{
		Sprite* walls;

	public:
		Cube(Renderer* renderer, const char* name, float x, float y, float z);
		~Cube();
		void Draw();
		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);

	};
}

#endif