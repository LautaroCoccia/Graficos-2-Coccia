#include "Player3D.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Player3D::Player3D() : Entity()
	{
		_cubeModel = NULL;
		_light = NULL;
		_movementSpeed = 10;

		_transform.position = vec3(0, 0, 0);

		_transform.rotation.x = 4.37114e-08f;
		_transform.rotation.y = 0;
		_transform.rotation.z = 1;


	}
	Player3D::Player3D(float movementSpeed, const char* texture, const char* texture2, Renderer* renderer) : Entity()
	{
		_light = new Light(renderer, glm::vec3(1,1,1));
		_movementSpeed = movementSpeed;
		SetCubeModel(texture, texture2, renderer);
		_transform.position = vec3(0, 0, 0);

		_transform.rotation.x = 4.37114e-08f;
		_transform.rotation.y = 0;
		_transform.rotation.z = 1;

		_light->SetPosition(glm::vec3(0, 0, 0));
		_light->SetLightColorAmbient(glm::vec3(0.1, 1, 1), 0);

	}

	Player3D::~Player3D()
	{
		if (_light != NULL)
			delete _light;
		if (_cubeModel != NULL)
			delete _cubeModel;
	}
	void Player3D::SetCubeModel(const char* diffuseMap, const char* specularMap , Renderer* renderer)
	{
		_cubeModel = new Cubo(diffuseMap, specularMap , renderer);
		_cubeModel->SetMaterial(glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.7, 0.7, 0.7), 32);

		_cubeModel->SetPosition(_transform.position);
		_cubeModel->SetRotation(_transform.rotation);

	}
	Light* Player3D::GetLight()
	{
		return _light;
	}
	void Player3D::Move(float deltaTime) 
	{
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
		
		_light->SetPosition(_transform.position);

		std::cout << _transform.position.x << " " << _transform.position.y << " " << _transform.position.z << endl;
		
		if (_cubeModel != NULL)
		{
			_cubeModel->SetPosition(_transform.position);
			//_cubeModel->UpdatePosition();
			//std::cout << _cubeModel->GetPosition().x << " " << _cubeModel->GetPosition().y << " " << _cubeModel->GetPosition().z << endl;
		}
		
	}
	void Player3D::Draw()
	{
		if(_light !=NULL)
			_light->Draw();
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