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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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
	}

	void GameEngine::Draw()
	{
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::Shutdown()
	{
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
