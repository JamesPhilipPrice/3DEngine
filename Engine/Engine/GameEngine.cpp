#include "GameEngine.h"
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

namespace GE {
	bool keyState[4] = { 0, 0, 0, 0 };

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
		
		window = SDL_CreateWindow("SDL and OpenGL", 50, 50, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

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

		if (SDL_GL_SetSwapInterval(0) != 0) {
			std::cerr << "Warning! Unable to set vSync. Error: " << SDL_GetError() << std::endl;
			return false;
		}
		std::cout<< glGetString(GL_VERSION) << std::endl;


		//Create the camera object
		cam = new Camera(glm::vec3(0.0f, 10.0f, 5.0f),
			glm::vec3(0.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			90.0f, 640.0f / 480.0f, 0.1f, 100.0f);

		//Create the triangle renderer (Debug testing)
		modelLoader = new AL::OBJLoader();

		//Scene management
		sceneManager = new SceneManager();
		sceneOne = new SceneOne(modelLoader);
		sceneOne->Init(cam);
		sceneManager->AddSceneToMap("MainGameScene", sceneOne);
		SDL_WarpMouseInWindow(window, WIDTH / 2, HEIGHT / 2);
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

	void GameEngine::ProcessInput()
	{
		//Process mouse input
		const float camSpeed = 2.0f;
		const float mouseSens = 0.1f;

		//Get mouse x and y
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);


		float diffX = mouseX - cam->GetOldMouseX();
		float diffY = cam->GetOldMouseY() - mouseY;

		cam->SetYaw(cam->GetYaw() + (diffX * mouseSens));
		cam->SetPitch(cam->GetPitch() + (diffY * mouseSens));

		glm::vec3 direction;
		direction.x = cos(glm::radians(cam->GetYaw())) * cos(glm::radians(cam->GetPitch()));
		direction.y = sin(glm::radians(cam->GetPitch()));
		direction.z = sin(glm::radians(cam->GetYaw())) * cos(glm::radians(cam->GetPitch()));
		cam->SetTarget(glm::normalize(direction));

		//Keyboard input process
		int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;

		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
					keyState[UP] = true;
					break;
				case SDL_SCANCODE_S:
					keyState[DOWN] = true;
					break;
				case SDL_SCANCODE_A:
					keyState[LEFT] = true;
					break;
				case SDL_SCANCODE_D:
					keyState[RIGHT] = true;
					break;
				default:
					break;
				}
			}
			else if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
					keyState[UP] = false;
					break;
				case SDL_SCANCODE_S:
					keyState[DOWN] = false;
					break;
				case SDL_SCANCODE_A:
					keyState[LEFT] = false;
					break;
				case SDL_SCANCODE_D:
					keyState[RIGHT] = false;
					break;
				default:
					break;
				}
			}
		}

		if (keyState[UP]) {
			cam->SetPos(cam->GetPos() + cam->GetTarget() * camSpeed * deltaTime);
		}
		if (keyState[DOWN]) {
			cam->SetPos(cam->GetPos() - cam->GetTarget() * camSpeed * deltaTime);
		}
		if (keyState[LEFT]) {
			cam->SetPos(cam->GetPos() - glm::normalize(glm::cross(cam->GetTarget(), cam->GetUpDir())) * camSpeed * deltaTime);
		}
		if (keyState[RIGHT]) {
			cam->SetPos(cam->GetPos() + glm::normalize(glm::cross(cam->GetTarget(), cam->GetUpDir())) * camSpeed * deltaTime);
		}

		cam->UpdateCameraMatricies();

		cam->SetOldMouseX(WIDTH / 2);
		cam->SetOldMouseY(HEIGHT / 2);
		SDL_WarpMouseInWindow(window, WIDTH / 2, HEIGHT / 2);

		sceneManager->ProcessInput();
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
		//vvv All game based update logic MUST GO IN HERE to be tied to realworld time, not frame speed vvv
		int currentTick = SDL_GetTicks();
		deltaTime = (float)((currentTick - lastTick) / 1000.0f);
		sceneManager->Update(deltaTime);
		lastTick = currentTick;
		//^^^ All game based update logic MUST GO IN HERE to be tied to realworld time, not frame speed ^^^
	}

	void GameEngine::Draw()
	{
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw the skybox firsty as it must always be at the back
		//skybox->Draw(cam);

		sceneManager->Draw(cam);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::Shutdown()
	{
		sceneManager->Shutdown();

		delete sceneManager;
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
