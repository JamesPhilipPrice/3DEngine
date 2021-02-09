#pragma once
#include "OBJLoader.h"

namespace GE {

	struct Vertex {
		//Vertex location
		float x, y, z;
		//Vertex colour
		float r, g, b, a;

		Vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _a) {
			x = _x;
			y = _y;
			z = _z;

			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}

		Vertex() {
			x = y = z = 0.0f;
			r = g = b = a = 0.0f;
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