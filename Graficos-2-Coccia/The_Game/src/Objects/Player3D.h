#ifndef PLAYER3D_H
#define PLAYER3D_H

#include "..\src\Entity\Entity.h"
#include "GameBase/GameBase.h"

namespace Engine
{
	class  Player3D : public Entity
	{
		Sprite* _sprite;
		float _movementSpeed;
	public:
		Player3D();
		Player3D(float movementSpeed);
		~Player3D();
		void Move(float deltaTime);
		void SetSprite(Sprite* sprite);
		void TriggerCollision(Entity* other) override;

	};

}
#endif // !PLAYER3D


