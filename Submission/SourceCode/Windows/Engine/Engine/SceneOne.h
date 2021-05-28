#pragma once
#include "Scene.h"
#include "Camera.h"
#include "ModelRenderer.h"
#include "Model.h"
#include "OBJLoader.h"
#include "SkyBoxRenderer.h"
#include "Skydome.h"
#include "EnvironmentRenderer.h"
#include "Texture.h"
#include "Terrain.h"
#include "OrthoSpriteRenderer.h"
#include "WaterRenderer.h"

namespace GE {
	class SceneOne : public Scene {
	public:
		SceneOne(AL::OBJLoader* _modelLoader) {
			modelLoader = _modelLoader;
		}
		~SceneOne() {}

		bool Init(Camera* _cam) override;
		void ProcessInput() override;
		void Update(float _deltaTime) override;
		void Draw(Camera* _cam) override;
		void Shutdown() override;

	private:
		AL::OBJLoader* modelLoader;

		//Don't bother reading after this point it's just a bunch of delcalarations
		Skydome* skydome;
		SkyboxRenderer* skybox;
		Texture* skydomeTexture;

		EnvironmentRenderer* environmentRenderer;

		//GUI HUD
		Texture* checkerTexture;
		OrthoSpriteRenderer* testSprite;
		
		//GameObjects
		//Ground
		Model* ground;
		Texture* groundMat;
		ModelRenderer* groundRenderer;

		//Terrain
		Texture* terrainMat;
		Terrain* terrainTool;
		Model* terrainModel;
		ModelRenderer* terrainRenderer;

		//Water
		Texture* waterMat;
		WaterRenderer* water;

		Texture* houseMatOne;
		Texture* houseMatTwo;

		//House One
		Model* houseOne;
		ModelRenderer* houseOneRenderer;

		//House Two
		Model* houseTwo;
		ModelRenderer* houseTwoRenderer;

		//House Three
		Model* houseThree;
		ModelRenderer* houseThreeRenderer;

		//Misc buildings
		Model* windmillModel;
		Model* windmillFanModel;
		Texture* windmillTexture;
		Texture* windmillFanTexture;
		ModelRenderer* windmillBase;
		ModelRenderer* windmillFan;

		float windmillFanSpeed = (float)(360 / 5);
		float windmillAngle = 0.0f;

		//Tanks
		Texture* tankTexture;
		Model* tankModel;
		ModelRenderer* tankRendererOne;
		ModelRenderer* tankRendererTwo;

		//Birds
		Model* birdModel;
		Texture* birdTexture;
		ModelRenderer* birdOne;

		float birdRadiusFromOrigin = 20.0f;
		float birdAngle = 0.0f;
		//birdSpeed is 360 degrees divided by how many second you want it to tank to complete a full revolution
		float birdSpeed = (float)(360 / 10);

	};
}