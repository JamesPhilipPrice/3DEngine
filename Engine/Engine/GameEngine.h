#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Camera.h"
#include "ModelRenderer.h"
#include "Model.h"
#include "OBJLoader.h"
#include "SkyBoxRenderer.h"
#include "SceneManager.h"
#include "SceneOne.h"

namespace GE {
	class GameEngine {
	public:
		GameEngine();

		virtual ~GameEngine();

		bool init();
		bool keep_running();
		void ProcessInput();
		void Update();
		void Draw();
		void Shutdown();

		void SetWindowTitle(const char*);

	private:
		SDL_Window* window;
		SDL_GLContext glContext;

		AL::OBJLoader* modelLoader;
		AL::OBJLoader* modelLoaderTwo;

		Camera* cam;

		SceneManager* sceneManager;
		Scene* sceneOne;

		unsigned int lastTick;
		float deltaTime;

		unsigned int lastCapUpdate = 0;
		int frameCount = 0;

		//Testing model stuff
		Model* model;
		Texture* material;
		ModelRenderer* modelRenderer;

		//Ground stuff
		Model* ground;
		Texture* groundMat;
		ModelRenderer* groundRenderer;

		//House One
		Model* houseOne;
		Texture* houseOneMat;
		ModelRenderer* houseOneRenderer;

		//House Two
		Model* houseTwo;
		Texture* houseTwoMat;
		ModelRenderer* houseTwoRenderer;

		//House Three
		Model* houseThree;
		Texture* houseThreeMat;
		ModelRenderer* houseThreeRenderer;

		//Skybox
		SkyboxRenderer* skybox;
	};

	void DisplayInfoMessage(const char*);
}