#pragma once
#include "OBJLoader.h"
#include "GeometryUtils.h"

namespace GE {

	class Model {
	public:
		Model(AL::OBJLoader* _loader) {
			modelLoader = _loader;
		}

		~Model() {
			delete[] verticies;
		}

		bool LoadFromFile(const char* _filename);

		void* GetVerticies() {
			return (void*)verticies;
		}

		void SetVerticies(std::vector<Vertex> _verts) {
			//NEED TO FIX THIS
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