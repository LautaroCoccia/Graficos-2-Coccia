#include "Player.h"

namespace Engine
{
	Player::Player(Renderer* renderer, const glm::ivec2& tileDimensions, float speed, Camera* camera) : Sprite(renderer, tileDimensions)
	{
		_speed = speed;
		_camera = camera;
		_x = 0;
		_z = 0;
	}
	
	Player::~Player()
	{

	}

	void Player::Move(float deltaTime)
	{
		/*if (Input::GetKey(Keycode::W))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(180);

			SetPosition(_transform.position.x, _transform.position.y , _transform.position.z + (_speed * deltaTime));
		}
		else if (Input::GetKey(Keycode::S))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);

			SetPosition(_transform.position.x, _transform.position.y , _transform.position.z - (_speed * deltaTime));
		}
		else if (Input::GetKey(Keycode::A))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(180);
		
			SetPosition(_transform.position.x - (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else if (Input::GetKey(Keycode::D))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);
		
			SetPosition(_transform.position.x + (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else 
		{
			//GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVs(36));
		}*/

		if (Input::GetKey(Keycode::W))
		{
			_z += (_speed * deltaTime);
		}
		else if (Input::GetKey(Keycode::S))
		{
			_z -= (_speed * deltaTime);

		}
		else if (Input::GetKey(Keycode::A))
		{
			_x -= (_speed * deltaTime);

		}
		else if (Input::GetKey(Keycode::D))
		{
			_x += (_speed * deltaTime);

		}
		_transform.position = _transform.right * _x + _transform.forward * _z;
		_camera->SetCameraPosition(_transform.position);
		_transform.rotation = _camera->GetRotation();
	}

	void Player::TriggerCollision(Entity* other)
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