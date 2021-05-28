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

		std::vector<Vertex> GetVerticies() {
			std::vector<Vertex> verts;
			for (int i = 0; i < indecies.size(); i++) {
				verts.emplace_back(verticies[indecies[i]]);
			}
			return verts;
		}

		Texture* GetTexture() { return texture; }
	private:
		GLuint vboTerrain, iboTerrain;
		Texture* texture;
		std::vector<Vertex> verticies;
		std::vector<unsigned int> indecies;
		float scale;
		float hScale;
	};
}