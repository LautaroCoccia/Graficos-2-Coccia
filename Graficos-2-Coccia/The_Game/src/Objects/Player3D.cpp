#include "Player3D.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Player3D::Player3D() : Entity()
	{
		_movementSpeed = 10;

		_transform.rotation.x = -1;
		_transform.rotation.y = 0;
		_transform.rotation.z = 4.37f;
		
	}
	Player3D::Player3D(float movementSpeed) : Entity()
	{
		_movementSpeed = movementSpeed;

		
		_transform.rotation.x = 4.37114e-08f;
		_transform.rotation.y = 0;
		_transform.rotation.z = 1;
	}

	Player3D::~Player3D()
	{

	}
	void Player3D::Move(float deltaTime) 
	{
		
		_transform.forward = glm::normalize(_transform.rotation);
		//_transform.forward = vec3(0, 0, 1);
		_transform.right = glm::cross(glm::vec3(0, 1, 0), _transform.forward);
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));
		
		if (Input::GetKey(Keycode::W))
			_transform.position += _movementSpeed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::S))
			_transform.position -= _movementSpeed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::A))
			_transform.position -= glm::cross(_transform.forward, _transform.up) * _movementSpeed * deltaTime;
		if (Input::GetKey(Keycode::D))
			_transform.position += glm::cross(_transform.forward, _transform.up) * _movementSpeed * deltaTime;
		
		//std::cout << _transform.right.x << " " << _transform.right.y << " " << _transform.right.z << std::endl;
		
		//std::cout << _transform.forward.x << " " << _transform.forward.y << " " << _transform.forward.z << std::endl;
		//std::cout << _transform.rotation.x << " " << _transform.rotation.y << " " << _transform.rotation.z << std::endl;

		//std::cout << _transform.position.x << " " << _transform.position.y << " " << _transform.position.z << std::endl;
		
		//if (Input::GetKey(Keycode::W))
		//{
		//	_transform.position = _transform.position - (_transform.forward * (_movementSpeed * deltaTime));
		//}
		//if (Input::GetKey(Keycode::S))
		//{
		//	_transform.position = _transform.position + (_transform.forward * (_movementSpeed * deltaTime));
		//}
		//if (Input::GetKey(Keycode::A))
		//{
		//	_transform.position = _transform.position - (_transform.right * (_movementSpeed * deltaTime));
		//}
		//if (Input::GetKey(Keycode::D))
		//{
		//	_transform.position = _transform.position + (_transform.right * (_movementSpeed * deltaTime));
		//}



		if (_sprite != NULL)
		{
			_sprite->SetPosition(_transform.position);
		}

	}
	void Player3D::SetSprite(Sprite* sprite)
	{
		_sprite = sprite;
	}
	void Player3D::TriggerCollision(Entity* other)
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