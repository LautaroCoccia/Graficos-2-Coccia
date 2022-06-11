#ifndef CUBE_H
#define CUBE_H

#include "..\Entity\Entity.h"
#include "..\Sprite\Sprite.h"

namespace Engine
{

	class EXPORT_API Cube : public Entity
	{
		Sprite* cube[6];
		vec3 facesPositions[6] = {
			vec3(0.0f, 0.0f, 0.5f),
			vec3(0.0f, 0.0f, -0.5f),
			vec3(0.5f, 0.0f, 0.0f),
			vec3(-0.5f, 0.0f, 0.0f),
			vec3(0.0f, 0.5f, 0.0f),
			vec3(0.0f, -0.5f, 0.0f)
		};
		vec3 facesRotations[6] = {
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 90.0f, 0.0f),
			vec3(0.0f, -90.0f, 0.0f),
			vec3(90.0f, 0.0f, 0.0f),
			vec3(-90.0f, 0.0f, 0.0f)
		};
	public:
        Cube(const char* texture, Renderer* renderer);
        ~Cube();
		void TriggerCollision(Entity* other) override;
		void Draw();
	};
}	
#endif // !CUBE_H


