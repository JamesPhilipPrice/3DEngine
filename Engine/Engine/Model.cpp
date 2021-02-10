#include <vector>
#include <time.h>
#include "Model.h"

namespace GE {
	bool Model::LoadFromFile(const char* _filename) {
		std::vector<Vertex> loadedVerticies;
		std::vector<std::vector<float>> sortedVertBuffer;

		modelLoader->LoadOBJFile(_filename, &sortedVertBuffer);
		std::srand(time(NULL));
		for (int i = 0; i < sortedVertBuffer.size(); i++) {
			loadedVerticies.push_back(Vertex(sortedVertBuffer[i][0], sortedVertBuffer[i][1], sortedVertBuffer[i][2], (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, 1.0f));
		}

		numVerticies = loadedVerticies.size();

		verticies = new Vertex[numVerticies];

		std::copy(loadedVerticies.begin(), loadedVerticies.end(), verticies);

		return true;
	}
}