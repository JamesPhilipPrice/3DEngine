#pragma once
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <vector>
#include <string>
#include "Camera.h"

namespace GE {
	class SkyboxRenderer {
	public:
		SkyboxRenderer(std::string _frontName, std::string _backName,
			std::string _leftName, std::string _rightName, 
			std::string _topName, std::string _bottomName) {
			std::vector<std::string> fileNames;

			fileNames.push_back(_rightName);
			fileNames.push_back(_leftName);
			fileNames.push_back(_topName);
			fileNames.push_back(_bottomName);
			fileNames.push_back(_frontName);
			fileNames.push_back(_backName);

			CreateCubemap(fileNames);
			CreateCubeVBO();
			CreateSkyboxProgram();
		}

		~SkyboxRenderer() {}

		void Draw(Camera* cam);

		void Destroy();

	private:
		void CreateCubemap(std::vector<std::string> _filenames);
		void CreateCubeVBO();
		void CreateSkyboxProgram();

	private:
		GLuint skyboxCubemapName;

		GLuint skyboxProgramId;

		GLint vertexLocation;

		GLuint vboSkybox;

		GLuint viewUniformId;
		GLuint projectionUniformId;
		GLuint samplerId;
	};
}