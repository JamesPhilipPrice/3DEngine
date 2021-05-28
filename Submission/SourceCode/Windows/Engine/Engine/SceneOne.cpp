#include "SceneOne.h"

namespace GE {
	bool SceneOne::Init(Camera* _cam)
	{
		//Setup skybox
		skybox = new SkyboxRenderer("assets/textures/skybox/front.png", 
			"assets/textures/skybox/back.png", 
			"assets/textures/skybox/left.png", 
			"assets/textures/skybox/right.png", 
			"assets/textures/skybox/top.png", 
			"assets/textures/skybox/bottom.png");

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

		//Setup HUD
		checkerTexture = new Texture("assets/textures/checker.jpg");
		testSprite = new OrthoSpriteRenderer(checkerTexture);
		testSprite->Init();

		//Terrain
		terrainMat = new Texture("assets/textures/terrain/SceneOneTerrTex.png");
		terrainTool = new Terrain("assets/textures/heightmaps/SceneOne.png", terrainMat, 200, 23.2f);
		terrainModel = new Model(modelLoader);
		terrainModel->SetVerticies(terrainTool->GetVerticies());
		terrainRenderer = new ModelRenderer(terrainModel, _cam);
		terrainRenderer->Init();
		terrainRenderer->SetMaterial(terrainTool->GetTexture());
		terrainRenderer->SetPos(100.0f, -3.5f, 100.0f);

		//Water
		waterMat = new Texture("assets/textures/water.jpg");
		water = new WaterRenderer(200, 200, 200, -0.2f);
		water->Init();
		water->SetMaterial(waterMat);

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

		//Load windmill stuff
		windmillModel = new Model(modelLoader);
		windmillFanModel = new Model(modelLoader);
		windmillModel->LoadFromFile("assets/models/windmill/Windmill_base.obj");
		windmillFanModel->LoadFromFile("assets/models/windmill/Windmill_fan.obj");
		if (windmillModel->GetVerticies() == nullptr) {
			std::cerr << "Failed to load windmill base model" << std::endl;
		}

		if (windmillFanModel->GetVerticies() == nullptr) {
			std::cerr << "Failed to load windmill fan model" << std::endl;
		}
		windmillTexture = new Texture("assets/textures/windmill/Windmill_base.png");
		windmillFanTexture = new Texture("assets/textures/windmill/Windmill_fan.png");

		windmillBase = new ModelRenderer(windmillModel, _cam);
		windmillBase->Init();
		windmillBase->SetMaterial(windmillTexture);
		windmillFan = new ModelRenderer(windmillFanModel, _cam);
		windmillFan->Init();
		windmillFan->SetMaterial(windmillFanTexture);

		windmillBase->SetRot(0, 180, 0);
		windmillBase->SetPos(30, 1, 30);
		windmillFan->SetRot(0, 0, 0);
		windmillFan->SetPos(30-6.84587, 11.7247f, 30);

		//Load bird stuff
		birdModel = new Model(modelLoader);
		birdModel->LoadFromFile("assets/models/animals/Bird.obj");
		if (birdModel->GetVerticies() == nullptr) {
			std::cerr << "Failed to load Bird model" << std::endl;
		}
		birdTexture = new Texture("assets/textures/animals/Bird.png");
		birdOne = new ModelRenderer(birdModel, _cam);
		birdOne->Init();
		birdOne->SetMaterial(birdTexture);
		birdOne->SetPos(0, 20, 0);

		//Load tanks
		tankTexture = new Texture("assets/textures/Mark_V.bmp");
		tankModel = new Model(modelLoader);
		tankModel->LoadFromFile("assets/models/Mark_V.obj");
		if (tankModel->GetVerticies() == nullptr) {
			std::cerr << "Failed to load tank model" << std::endl;
		}
		tankRendererOne = new ModelRenderer(tankModel, _cam);
		tankRendererOne->Init();
		tankRendererOne->SetMaterial(tankTexture);
		tankRendererOne->SetScale(0.025f, 0.025f, 0.025f);
		tankRendererOne->SetPos(10, 0, -15);
		tankRendererTwo = new ModelRenderer(tankModel, _cam);
		tankRendererTwo->Init();
		tankRendererTwo->SetMaterial(tankTexture);
		tankRendererTwo->SetRot(0, 45, 0);
		tankRendererTwo->SetScale(0.025f, 0.025f, 0.025f);
		tankRendererTwo->SetPos(10, 0, 15);
		return false;
	}

	void SceneOne::ProcessInput()
	{
	}

	void SceneOne::Update(float _deltaTime)
	{
		//Error pulling stuff
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cout << "Error: " << err << std::endl;
		}

		//Actual update stuff

		//Bird movement
		//Rotate bird
		birdAngle += (float)(birdSpeed * _deltaTime);
		birdOne->SetRot(0.0f, birdAngle, 0.0f);
		float birdX;
		float birdZ;
		birdX = (float)(birdRadiusFromOrigin * sinf(birdAngle * (3.1415 / 180)));
		birdZ = (float)(birdRadiusFromOrigin * cosf(birdAngle * (3.1415 / 180)));
		//Set bird pos
		birdOne->SetPos(birdX, birdOne->GetPosY(), birdZ);

		//Windmill
		windmillAngle += windmillFanSpeed * _deltaTime;
		windmillFan->SetRot(windmillAngle, 0.0f, 0.0f);

		//Water
		water->AddToGameTime(_deltaTime);
	}

	void SceneOne::Draw(Camera* _cam)
	{
		skybox->Draw(_cam);
		//groundRenderer->Draw(_cam);
		terrainRenderer->Draw(_cam);
		water->Draw(_cam);
		houseOneRenderer->Draw(_cam);
		houseTwoRenderer->Draw(_cam);
		houseThreeRenderer->Draw(_cam);
		windmillBase->Draw(_cam);
		windmillFan->Draw(_cam);
		birdOne->Draw(_cam);
		tankRendererOne->Draw(_cam);
		tankRendererTwo->Draw(_cam);

		//DrawHUD
		testSprite->Draw(glm::vec2(5, 5), glm::vec2(200, 200), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	void SceneOne::Shutdown()
	{
		groundRenderer->Destroy();
		terrainRenderer->Destroy();
		houseOneRenderer->Destroy();
		houseTwoRenderer->Destroy();
		houseThreeRenderer->Destroy();
		windmillBase->Destroy();
		windmillFan->Destroy();
		birdOne->Destroy();
		tankRendererOne->Destroy();
		tankRendererTwo->Destroy();
		skybox->Destroy();
		//environmentRenderer->Destroy();

		delete groundRenderer;
		delete ground;
		delete terrainRenderer;
		delete terrainModel;
		delete houseOneRenderer;
		delete houseOne;
		delete houseTwoRenderer;
		delete houseTwo;
		delete houseThreeRenderer;
		delete houseThree;
		delete windmillBase;
		delete windmillFan;
		delete windmillModel;
		delete windmillFanModel;
		delete birdOne;
		delete birdModel;
		delete tankRendererOne;
		delete tankRendererTwo;
		delete tankModel;
		delete skybox;
	}
}

