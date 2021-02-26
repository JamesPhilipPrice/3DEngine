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

namespace GE {
	class SceneOne : public Scene {
	public:
		SceneOne(AL::OBJLoader* _modelLoader) {
			modelLoader = _modelLoader;
		}
		~SceneOne() {}

		bool Init(Camera* _cam) override;
		void ProcessInput() override;
		void Update() override;
		void Draw(Camera* _cam) override;
		void Shutdown() override;

	private:
		AL::OBJLoader* modelLoader;

		//Don't bother reading after this point it's just a bunch of delcalarations
		Skydome* skydome;
		Texture* skydomeTexture;

		EnvironmentRenderer* environmentRenderer;

		//GameObjects
		//Ground
		Model* ground;
		Texture* groundMat;
		ModelRenderer* groundRenderer;

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
	};
}