#include "Player3D.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Player3D::Player3D() : Entity()
	{
		_cubeModel = NULL;
		_movementSpeed = 10;

		_transform.position = vec3(0, 0, 0);

		_transform.rotation.x = 4.37114e-08f;
		_transform.rotation.y = 0;
		_transform.rotation.z = 1;
		
	}
	Player3D::Player3D(float movementSpeed, const char* texture, Renderer* renderer) : Entity()
	{
		_movementSpeed = movementSpeed;
		SetCubeModel(texture, renderer);
		_transform.position = vec3(0, 0, 0);

		_transform.rotation.x = 4.37114e-08f;
		_transform.rotation.y = 0;
		_transform.rotation.z = 1;

	}

	Player3D::~Player3D()
	{
		if (_cubeModel != NULL)
			delete _cubeModel;
	}
	void Player3D::SetCubeModel(const char* texture, Renderer* renderer)
	{
		_cubeModel = new Cubo(texture, renderer);
		_cubeModel->SetPosition(_transform.position);
		_cubeModel->SetRotation(_transform.rotation);
	}
	void Player3D::Move(float deltaTime) 
	{
		//_transform.forward.x = cos(glm::radians(_transform.rotation.x)) * cos(glm::radians(_transform.rotation.y));
		//_transform.forward.y = sin(glm::radians(_transform.rotation.y));
		//_transform.forward.z = sin(glm::radians(_transform.rotation.x)) * cos(glm::radians(_transform.rotation.y));
		//
		
		//_transform.forward.x = cos((_transform.rotation.x)) * cos((_transform.rotation.y));
		//_transform.forward.y = sin((_transform.rotation.y));
		//_transform.forward.z = sin((_transform.rotation.x)) * cos((_transform.rotation.y));
		
		//_transform.forward = vec3(0, 0, 1);
		_transform.forward = glm::normalize(_transform.rotation);
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

		std::cout << _transform.position.x << " " << _transform.position.y << " " << _transform.position.z << std::endl;

		if (_cubeModel != NULL)
		{
			_cubeModel->SetPosition(_transform.position);
			//_cubeModel->UpdatePosition();
			std::cout << _cubeModel->GetPosition().x << " " << _cubeModel->GetPosition().y << " " << _cubeModel->GetPosition().z << endl;
		}
		//std::cout << _transform.position.x << " " << _transform.position.y << " " << _transform.position.z << endl;
	}
	void Player3D::Draw()
	{
		if (_cubeModel != NULL)
			_cubeModel->Draw();
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