#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {
	class GameEngine {
	public:
		GameEngine();

		virtual ~GameEngine();

		bool init();
		bool keep_running();
		void Update();
		void Draw();
		void Shutdown();

		void SetWindowTitle(const char*);

	private:
		SDL_Window* window;
		SDL_GLContext glContext;
	};

	void DisplayInfoMessage(const char*);
}