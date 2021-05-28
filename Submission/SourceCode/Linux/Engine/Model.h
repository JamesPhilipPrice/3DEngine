#pragma once
#include "OBJLoader.h"
#include "GeometryUtils.h"

namespace GE {

	class Model {
	public:
		Model(AL::OBJLoader* _loader) {
			modelLoader = _loader;
		}

		Model() {}

		~Model() {
			delete[] verticies;
		}

		bool LoadFromFile(const char* _filename);

		void* GetVerticies() {
			return (void*)verticies;
		}

		void SetVerticies(std::vector<Vertex> _verts) {
			numVerticies = _verts.size();

			verticies = new Vertex[numVerticies];

			std::copy(_verts.begin(), _verts.end(), verticies);
		}

		int GetNumVerticies() {
			return numVerticies;
		}

	private:
		AL::OBJLoader* modelLoader;

		Vertex* verticies;
		int numVerticies;
	};
}
