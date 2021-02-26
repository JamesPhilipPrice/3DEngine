#pragma once
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Model.h"
#include "Texture.h"

namespace GE {
	class Terrain {
	public:
		Terrain(std::string _filename, Texture* _texture, float _scale, float _hScale);
		~Terrain();

		unsigned int GetVBO() { return vboTerrain; }
		unsigned int GetIBO() { return iboTerrain; }
		Texture* GetTexture() { return texture; }
	private:
		GLuint vboTerrain, iboTerrain;
		Texture* texture;
		float scale;
		float hScale;
	};
}