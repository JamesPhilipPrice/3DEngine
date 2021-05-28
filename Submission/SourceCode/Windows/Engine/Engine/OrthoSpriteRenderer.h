#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

#define WIDTH 1280
#define HEIGHT 720

namespace GE {
	class OrthoSpriteRenderer {
	public:
		OrthoSpriteRenderer(Texture* _tex) : texture(_tex) {
			orthProjection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
		}
		virtual ~OrthoSpriteRenderer() {}

		void Init();
		void Update();
		void Draw(glm::vec2 _position, glm::vec2 _size, float _rotation, glm::vec3 _colour);
		void Destroy();

	private:
		GLuint programID;
		GLuint vertexLocation;
		GLuint modelUniformLocation;
		GLuint projectionUniformLocation;

		GLuint imageUniformLocation;
		GLuint spriteColourUniformLocation;

		GLuint quadVAO;
		glm::mat4 orthProjection;
		Texture* texture;
	};
}
