#include "SceneOne.h"

namespace GE {
	bool SceneOne::Init(Camera* _cam)
	{
		//Setup skybox
		skybox = new SkyboxRenderer("assets/textures/skybox/front.jpg", 
			"assets/textures/skybox/back.jpg", 
			"assets/textures/skybox/left.jpg", 
			"assets/textures/skybox/right.jpg", 
			"assets/textures/skybox/top.jpg", 
			"assets/textures/skybox/bottom.jpg");

		//environmentRenderer = new EnvironmentRenderer();
		//skydome = new Skydome();
		//skydome->Init(20, 10);
		//skydomeTexture = new Texture("assets/textures/skybox/test.png");
		//environmentRenderer->InitSkydome(skydome);
		//environmentRenderer->SetSkyTexture(skydomeTexture);

		//Setup gameobjects

		//Ground model
		ground = new Model(modelLoader);
		ground->LoadFromFile("assets/models/Plane.obj");
		if (ground->GetVerticies() == nullptr) {
			std::cerr << "Failed to load ground model!" << std::endl;
		}
		groundMat = new Texture("assets/textures/Grass.jpg");
		groundRenderer = new ModelRenderer(ground, _cam);
		groundRenderer->Init();
		groundRenderer->SetMaterial(groundMat);

		//Load house materials
		houseMatOne = new Texture("assets/textures/HousesONE.jpg");
		houseMatTwo = new Texture("assets/textures/HousesTWO.jpg");


		//House One model
		houseOne = new Model(modelLoader);
		houseOne->LoadFromFile("assets/models/HouseClusterOne.obj");
		if (houseOne->GetVerticies() == nullptr) {
			std::cerr << "Failed to load houseOne model!" << std::endl;
		}
		houseOneRenderer = new ModelRenderer(houseOne, _cam);
		houseOneRenderer->Init();
		houseOneRenderer->SetMaterial(houseMatOne);

		//House two model
		houseTwo = new Model(modelLoader);
		houseTwo->LoadFromFile("assets/models/HouseClusterTwo.obj");
		if (houseTwo->GetVerticies() == nullptr) {
			std::cerr << "Failed to load houseTwo model!" << std::endl;
		}
		houseTwoRenderer = new ModelRenderer(houseTwo, _cam);
		houseTwoRenderer->Init();
		houseTwoRenderer->SetMaterial(houseMatOne);

		//House three model
		houseThree = new Model(modelLoader);
		houseThree->LoadFromFile("assets/models/HouseClusterThree.obj");
		if (houseThree->GetVerticies() == nullptr) {
			std::cerr << "Failed to load houseThree model!" << std::endl;
		}
		houseThreeRenderer = new ModelRenderer(houseThree, _cam);
		houseThreeRenderer->Init();
		houseThreeRenderer->SetMaterial(houseMatOne);
		return false;
	}

	void SceneOne::ProcessInput()
	{
	}

	void SceneOne::Update()
	{
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "Error: " << err << std::endl;
		}
	}

	void SceneOne::Draw(Camera* _cam)
	{
		skybox->Draw(_cam);
		groundRenderer->Draw(_cam);
		houseOneRenderer->Draw(_cam);
		houseTwoRenderer->Draw(_cam);
		houseThreeRenderer->Draw(_cam);
		//environmentRenderer->DrawSkydome(_cam);
	}

	void SceneOne::Shutdown()
	{
		groundRenderer->Destroy();
		houseOneRenderer->Destroy();
		houseTwoRenderer->Destroy();
		houseThreeRenderer->Destroy();
		skybox->Destroy();
		//environmentRenderer->Destroy();

		delete groundRenderer;
		delete ground;
		delete houseOneRenderer;
		delete houseOne;
		delete houseTwoRenderer;
		delete houseTwo;
		delete houseThreeRenderer;
		delete houseThree;
		delete skybox;
	}
}

