#pragma once
#include "ShaderUtility.h"
#include "GeometryUtils.h"
#include "Texture.h"

namespace GE {
	class Skydome {
	public:
		Skydome();
		~Skydome();

		void Init(int _radius, int _resolution);

		void* GetVerticies() {
			return (void*)verticies;
		}

		int GetNumVerticies() {
			return numVerticies;
		}

	private:
		Texture* texture;

		Vertex* verticies;
		int numVerticies;
	};
}
