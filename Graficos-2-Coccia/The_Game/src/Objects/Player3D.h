#ifndef PLAYER3D_H
#define PLAYER3D_H

#include "..\src\Entity\Entity.h"
#include "..\src\Lights\Light.h"
#include "GameBase/GameBase.h"

namespace Engine
{
	class  Player3D : public Entity
	{
		Light* _light;
		Cubo* _cubeModel;
		float _movementSpeed;
	public:
		Player3D();
		Player3D(float movementSpeed,const char* texture, Renderer* renderer);
		~Player3D();
		void SetCubeModel(const char* texture, Renderer* renderer);
		void Move(float deltaTime);
		void Draw();
		void TriggerCollision(Entity* other) override;

	};

}
#endif // !PLAYER3D