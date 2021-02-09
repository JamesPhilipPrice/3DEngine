#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace AL {
	class OBJLoader {
	public:
		//Constructor currently does nothing
		OBJLoader() {

		}
		//Deconstructor currently does nothing
		~OBJLoader() {

		}

		bool LoadOBJFile(const char* _location, std::vector<std::vector<float>>* _targetContainer) {
			std::ifstream fileIn(_location);

			if (!fileIn) {
				std::cerr << "Couldn't load file: " << _location << std::endl;
				return false;
			}

			std::vector<std::string> fileBuffer;

			while (!fileIn.eof()) {
				std::string s;
				getline(fileIn, s);

				s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());

				fileBuffer.push_back(s);
			}
			fileIn.close();

			//Sort through the information in the obj file buffer and place items into buffer lists
			std::vector<std::vector<float>> vertexBuffer;
			std::vector<std::vector<int>> faceBuffer;

			for (int i = 0; i < fileBuffer.size(); i++) {
				if (fileBuffer[i].substr(0, 2) == "v ") {
					//This line contains vertex information
					std::vector<float> tempVertBuffer;
					//Strip away the now redundant information and break down the buffer line into separate floats
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					tempVertBuffer.push_back(stof(fileBuffer[i].substr(0, fileBuffer[i].find(" "))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					tempVertBuffer.push_back(stof(fileBuffer[i].substr(0, fileBuffer[i].find(" "))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					tempVertBuffer.push_back(stof(fileBuffer[i].substr(0, fileBuffer[i].find(" "))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					vertexBuffer.push_back(tempVertBuffer);
				}
				else if (fileBuffer[i].substr(0, 2) == "f ") {
					std::vector<int> tempFaceBuffer;
					//Strip away now redundant information and sort through faces to generate a vertex order
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					//Get first vertex
					tempFaceBuffer.push_back(stoi(fileBuffer[i].substr(0, fileBuffer[i].find("/"))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					tempFaceBuffer.push_back(stoi(fileBuffer[i].substr(0, fileBuffer[i].find("/"))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					tempFaceBuffer.push_back(stoi(fileBuffer[i].substr(0, fileBuffer[i].find("/"))));
					fileBuffer[i].erase(0, fileBuffer[i].find(" ") + 1);
					faceBuffer.push_back(tempFaceBuffer);
				}
			}

			for (int i = 0; i < faceBuffer.size(); i++) {
				_targetContainer->push_back(vertexBuffer[faceBuffer[i][0]-1]);
				_targetContainer->push_back(vertexBuffer[faceBuffer[i][1]-1]);
				_targetContainer->push_back(vertexBuffer[faceBuffer[i][2]-1]);
			}


			return true;
		}
	};
}