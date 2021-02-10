#pragma once
#include "OBJLoader.h"

namespace GE {

	struct Vertex {
		//Vertex location
		float x, y, z;
		//Vertex colour
		float u, v;

		Vertex(float _x, float _y, float _z, float _u, float _v) {
			x = _x;
			y = _y;
			z = _z;

			u = _u;
			v = _v;
		}

		Vertex() {
			x = y = z = 0.0f;
			u = v = 0.0f;
		}
	};

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

		int GetNumVerticies() {
			return numVerticies;
		}

	private:
		AL::OBJLoader* modelLoader;

		Vertex* verticies;
		int numVerticies;
	};
}