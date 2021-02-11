#include "GameEngine.h"
#include <iostream>

namespace GE {
	GameEngine::GameEngine()
	{

	}

	GameEngine::~GameEngine() {

	}

	bool GameEngine::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Unable to initialise SDL! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		window = SDL_CreateWindow("SDL and OpenGL", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		//Check if the window was created
		if (window == nullptr) {
			//Show an error if the window weasn't created
			std::cerr << "Unable to creat the window! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		glContext = SDL_GL_CreateContext(window);

		if (glContext == nullptr) {
			//Display error if the context was not created and assigned
			std::cerr << "SDL could not create the gl context! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		GLenum status = glewInit();

		if (status != GLEW_OK) {
			std::cerr << "Error initialise GLEW! Error: " << glewGetErrorString(status) << std::endl;
			return false;
		}

		if (SDL_GL_SetSwapInterval(1) != 0) {
			std::cerr << "Warning! Unable to set vSync. Error: " << SDL_GetError() << std::endl;
			return false;
		}
		std::cout<< glGetString(GL_VERSION) << std::endl;


		//Create the camera object
		cam = new Camera(glm::vec3(0.0f, 5.0f, 5.0f),
			glm::vec3(0.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

		//Create the triangle renderer (Debug testing)
		modelLoader = new AL::OBJLoader();

		//Debug Model
		model = new Model(modelLoader);
		model->LoadFromFile("assets/models/test.obj");
		
		if (model->GetVerticies() == nullptr) {
			std::cerr << "Failed to load model!" << std::endl;
		}

		material = new Texture("assets/textures/wood.png");
		modelRenderer = new ModelRenderer(model);
		modelRenderer->Init();
		modelRenderer->SetMaterial(material);
		modelRenderer->SetPos(0.0f, 5.0f, 0.0f);
		
		//Ground model
		ground = new Model(modelLoader);
		ground->LoadFromFile("assets/models/Plane.obj");
		if (ground->GetVerticies() == nullptr) {
			std::cerr << "Failed to load ground model!" << std::endl;
		}
		groundMat = new Texture("assets/textures/Grass.jpg");
		groundRenderer = new ModelRenderer(ground);
		groundRenderer->Init();
		groundRenderer->SetMaterial(groundMat);

		//House One model
		houseOne = new Model(modelLoader);
		houseOne->LoadFromFile("assets/models/House_One.obj");
		if (houseOne->GetVerticies() == nullptr) {
			std::cerr << "Failed to load houseOne model!" << std::endl;
		}
		houseOneMat = new Texture("assets/textures/HousesONE.jpg");
		houseOneRenderer = new ModelRenderer(houseOne);
		houseOneRenderer->Init();
		houseOneRenderer->SetMaterial(houseOneMat);
		houseOneRenderer->SetPos(-2, 0, -10);
		return true;
	}

	bool GameEngine::keep_running()
	{
		//Get the event queue up to date
		SDL_PumpEvents();

		SDL_Event evt;

		//Check for quit event
		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			//return false to flag a quit event
			return false;
		}
		return true;
	}

	void GameEngine::Update()
	{
		frameCount++;
		if (SDL_GetTicks() - lastCapUpdate >= 1000) {
			float avgFPS = frameCount / ((SDL_GetTicks() - lastCapUpdate) / 1000.0f);
			std::string fpsString = "FPS: " + std::to_string(avgFPS);
			SDL_SetWindowTitle(window, fpsString.c_str());
			frameCount = 0;
			lastCapUpdate = SDL_GetTicks();
		}
		//modelRenderer->SetRot(modelRenderer->GetRotX(), modelRenderer->GetRotY() + 0.03, modelRenderer->GetRotZ());
		houseOneRenderer->SetRot(houseOneRenderer->GetRotX(), houseOneRenderer->GetRotY() + 0.03, houseOneRenderer->GetRotZ());
	}

	void GameEngine::Draw()
	{
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//modelRenderer->Draw(cam);
		//groundRenderer->Draw(cam);
		houseOneRenderer->Draw(cam);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::Shutdown()
	{
		modelRenderer->Destroy();
		groundRenderer->Destroy();
		houseOneRenderer->Destroy();

		delete modelRenderer;
		delete model;
		delete groundRenderer;
		delete ground;
		delete houseOneRenderer;
		delete houseOne;
		delete cam;

		SDL_DestroyWindow(window);

		window = nullptr;

		SDL_Quit();
	}

	void GameEngine::SetWindowTitle(const char* _newTitle)
	{
		SDL_SetWindowTitle(window, _newTitle);
	}

	void DisplayInfoMessage(const char* _msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Engine", _msg, nullptr);
	}
}
