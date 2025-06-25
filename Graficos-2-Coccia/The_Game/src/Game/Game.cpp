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
		_fpcamera = NULL;
		_tpcamera = NULL;

		_currentCamera = NULL;
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
		if (_fpcamera != NULL)
			delete _fpcamera;
		if (_tpcamera != NULL)
			delete _tpcamera;
		if (_currentCamera != NULL)
			delete _currentCamera;
	}

	void Game::Start()
	{
		StartEngine(800, 600, "Coccia Graficos 2");
		srand(time(NULL));

		// sugerencia: Podria settear una camara por defecto?
		//SetCamera(CameraType::Perspective, 0.1f, 100.0f);
		//SetCameraPosition(0, 0, 5);

		_fpcamera = new FPCamera();
		_fpcamera->SetValues(CameraType::Perspective, 0.1, 100, "FPS", 800, 600);
		_fpcamera->SetPosition(0, 0, 5);
		 
		_currentCamera = _fpcamera;
		GetRenderer()->SetCurrentCamera(_fpcamera);

		_tpcamera = new TPCamera();
		_tpcamera->SetValues(CameraType::Perspective, 0.1, 100, "TPC", 800, 600);
		_tpcamera->SetPosition(0, 0, 10);
		_tpcamera->SetOffset(4);
		// --------------------------------
		
		_wall1 = new Sprite(GetRenderer());
		_wall1->InitTexture();
		_wall1->ImportTexture("res/wall.jpg");
		_wall1->SetPosition(0, 1.2, -5);
		_wall1->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_wall1);
		
		// --------------------------------
		_wall2 = new Sprite(GetRenderer());
		_wall2->InitTexture();
		_wall2->ImportTexture("res/wall.jpg");
		_wall2->SetPosition(0, -1.2, 0);
		_wall2->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_wall2);
		
		// --------------------------------
		
		_box = new Sprite(GetRenderer());
		_box->InitTexture();
		_box->ImportTexture("res/crate1_diffuse.png");
		_box->SetPosition(0, 0, 0);
		GetCollisionManager()->AddNewObject(_box);

		// --------------------------------

		_roboBob = new Player(GetRenderer(), ivec2(9,5), 2);
		_roboBob->GetAnimation()->AddFrame(0.5, 0, 7);

		_roboBob->InitTexture();
		_roboBob->ImportTexture("res/character_robot_sheet.png");
		_roboBob->SetPosition(-1.8, 0, 0);
		GetCollisionManager()->AddNewObject(_roboBob);

		_testCube = new Cube(GetRenderer(), "res/wall.jpg", 0, 0, 0);
		_tpcamera->SetTransform(&(_roboBob->_transform.position));

	}
	
	void Game::Play()
	{
		UpdateEngine(0.0f, 0.0f, 0.0f, 1);
	}

	void Game::Update(float deltaTime)
	{
	
		_roboBob->Move(deltaTime);
		_currentCamera->CameraInput(deltaTime);

		GetCollisionManager()->CheckAllCollisions();
		_testCube->Draw();


		_wall1->Draw();
		_wall2->Draw();
		_box->Draw();
		if (Input::GetKey(Keycode::KP_1))
		{
			 //ChangeWindowSize(1376, 720);
			// _fpcamera->SetWidthHeight(1376, 720);
			_currentCamera = _tpcamera;
			 GetRenderer()->SetCurrentCamera(_tpcamera);
		}
	}

	void Game::End()
	{
		EndEngine();
	}
	
}