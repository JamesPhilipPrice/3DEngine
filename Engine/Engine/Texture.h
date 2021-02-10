#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace GE {
	class Texture {
	public:
		Texture(std::string _filename) {
			width = 0;
			height = 0;

			textureName = 0;

			LoadTexture(_filename);
		}

		~Texture() {

		}

		int GetWidth() {
			return width;
		}

		int GetHeight() {
			return height;
		}

		Uint32 GetFormat() {
			return format;
		}

		GLuint GetTextureName() {
			return textureName;
		}

	private:
		void LoadTexture(std::string _filename);

		int width, height;

		Uint32 format;

		GLuint textureName;
	};
}