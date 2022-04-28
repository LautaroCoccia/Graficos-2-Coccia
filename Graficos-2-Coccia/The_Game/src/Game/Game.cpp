#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_roboBob = NULL;
		_wall1 = NULL;
		_wall2 = NULL;
		_box = NULL;
		_camera = NULL;
	}

	Game::~Game()
	{
		if (_roboBob != NULL)
			delete _roboBob;
		if (_wall1 != NULL)
			delete _wall1;
		if (_wall2 != NULL)
			delete _wall2;
		if (_box != NULL)
			delete _box;
		if (_camera != NULL)
			delete _camera;
	}

	void Game::Start()
	{
		StartEngine(1200, 600, "Coccia Graficos 2");
		srand(time(NULL));
		_camera = new Camera(CameraType::Perspective, 0.1f, 100.0f, 1200, 600, 0.5f);
		_camera->SetCameraMode(CameraMode::TPCamera);
		_camera->SetCameraOffset(glm::vec3(0, 0, 3));
		//_camera->LookAt(glm::vec3(0, 0, 0));
		//_camera->SetCameraPosition(0, 0, 3); 
		
		GetRenderer()->SetCurrentCamera(_camera);

		// --------------------------------
		
		_wall1 = new Sprite(GetRenderer());

		_wall1->InitTexture();
		_wall1->ImportTexture("res/wall.jpg");
		_wall1->SetPosition(0, -1, 0);
		_wall1->SetRotation(90, 0, 0);
		_wall1->SetScale(10,10,10);
		_wall1->SetStaticState(true);
		//GetCollisionManager()->AddNewObject(_wall1);
		
		// --------------------------------
		//_wall2 = new Sprite(GetRenderer());
		//_wall2->InitTexture();
		//_wall2->ImportTexture("res/wall.jpg");
		//_wall2->SetRotation(0, 0, 0);
		//_wall2->SetPosition(0, -1, 0);
		//_wall2->SetStaticState(true);
		//GetCollisionManager()->AddNewObject(_wall2);
		
		// --------------------------------

		_box = new Sprite(GetRenderer());
		_box->InitTexture();
		_box->ImportTexture("res/crate1_diffuse.png");
		_box->SetPosition(0, 0, 0);
		//GetCollisionManager()->AddNewObject(_box);

		// --------------------------------

		_roboBob = new Player(GetRenderer(), ivec2(9,5), 10,_camera);
		_roboBob->GetAnimation()->AddFrame(0.5, 0, 7);
		
		_roboBob->InitTexture();
		_roboBob->ImportTexture("res/character_robot_sheet.png");
		_roboBob->SetPosition(0, 0, 0);
		GetCollisionManager()->AddNewObject(_roboBob);

		//_camera->SetEntity(_roboBob);
	}
	
	void Game::Play()
	{
		UpdateEngine(0.0f, 0.0f, 0.0f, 1);
	}

	void Game::Update(float deltaTime)
	{
		//_camera->SetCameraPosition(_roboBob->_transform.position);
		_roboBob->Move(deltaTime);
		_camera->CameraInput(deltaTime,  _roboBob->_transform);
		
		//GetCollisionManager()->CheckAllCollisions();
		_wall1->Draw();
		//_wall2->Draw();
		//_box->Draw();
	}

	void Game::End()
	{
		EndEngine();
	}
}