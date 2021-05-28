#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Texture.h"
#include "Skydome.h"

namespace GE {
	class EnvironmentRenderer {
	public:
		EnvironmentRenderer();
		~EnvironmentRenderer();

		void InitSkydome(Skydome* _sky) {
			skydome = _sky;

			glGenBuffers(1, &vboSkydome);
			glBindBuffer(GL_ARRAY_BUFFER, vboSkydome);
			glBufferData(GL_ARRAY_BUFFER, skydome->GetNumVerticies() * sizeof(Vertex), skydome->GetVerticies(), GL_STATIC_DRAW);
		}

		void Draw(Camera* _cam) {
			DrawSkydome(_cam);
		}

		void DrawSkydome(Camera* _cam);


		void Destroy();

		//Transformatrion Methods
		void SetSkyPos(float _x, float _y, float _z) {
			s_posX = _x;
			s_posY = _y;
			s_posZ = _z;
		}

		void SetSkyRot(float _x, float _y, float _z) {
			s_rotX = _x;
			s_rotY = _y;
			s_rotZ = _z;
		}

		void SetSkyScale(float _x, float _y, float _z) {
			s_scaleX = _x;
			s_scaleY = _y;
			s_scaleZ = _z;
		}

		void SetTerrainPos(float _x, float _y, float _z) {
			t_posX = _x;
			t_posY = _y;
			t_posZ = _z;
		}

		void SetTerrainRot(float _x, float _y, float _z) {
			t_rotX = _x;
			t_rotY = _y;
			t_rotZ = _z;
		}

		void SetTerrainScale(float _x, float _y, float _z) {
			t_scaleX = _x;
			t_scaleY = _y;
			t_scaleZ = _z;
		}

		void SetSkyTexture(Texture* _tex) {
			skyTexture = _tex;
		}


		void DisplayShaderCompilerError(GLuint _shaderID) {
			GLint msgLen = 0;

			glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &msgLen);

			if (msgLen > 1) {
				GLchar* msg = new GLchar[msgLen + 1];

				glGetShaderInfoLog(_shaderID, msgLen, NULL, msg);

				std::cerr << "Error compiling shader: " << msg << std::endl;

				delete[] msg;
			}
		}
	private:
		Skydome* skydome;
		Texture* skyTexture;

		//Shader related stuff
		GLuint programId;
		GLint vertexPos3DLocation;
		GLint vertexUVLocation;
		GLuint vboSkydome;
		GLuint vboTerrain;

		//Transforms
		//Skydome
		float s_posX, s_posY, s_posZ;
		float s_rotX, s_rotY, s_rotZ;
		float s_scaleX, s_scaleY, s_scaleZ;

		float t_posX, t_posY, t_posZ;
		float t_rotX, t_rotY, t_rotZ;
		float t_scaleX, t_scaleY, t_scaleZ;

		GLuint transformUniformID;
		GLuint viewUniformID;
		GLuint projectionUniformID;
		GLuint samplerID;
	};
}