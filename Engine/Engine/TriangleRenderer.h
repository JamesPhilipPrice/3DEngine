#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {
	class TriangleRenderer {
	public:
		TriangleRenderer();
		virtual ~TriangleRenderer();

		void Init();

		void Update();

		void Draw();

		void Destroy();

	private:
		GLuint programId;
		GLint vertexPos2DLocation;
		GLuint vboTriangle;
	};
}