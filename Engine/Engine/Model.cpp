#include <vector>
#include <time.h>
#include "Model.h"

namespace GE {
	bool Model::LoadFromFile(const char* _filename) {
		std::vector<Vertex> loadedVerticies;
		std::vector<std::vector<float>> sortedVertBuffer;
		std::vector<std::vector<float>> sortedUVBuffer;
		std::vector<std::vector<float>> sortedVNBuffer;

		modelLoader->LoadOBJFile(_filename, &sortedVertBuffer, &sortedUVBuffer, &sortedVNBuffer);
		std::srand(time(NULL));
		for (int i = 0; i < sortedVertBuffer.size(); i++) {
			loadedVerticies.push_back(Vertex(
				sortedVertBuffer[i][0], sortedVertBuffer[i][1], sortedVertBuffer[i][2], 
				sortedUVBuffer[i][0], -sortedUVBuffer[i][1], 
				sortedVNBuffer[i][0], sortedVNBuffer[i][2], sortedVNBuffer[i][2]));
		}

		numVerticies = loadedVerticies.size();

		verticies = new Vertex[numVerticies];

		std::copy(loadedVerticies.begin(), loadedVerticies.end(), verticies);
		std::cout << "Loaded " << _filename << " with " << loadedVerticies.size() << " verts!" << std::endl;
		return true;
	}
}