/*#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include "Camera.h"

namespace GE {
	class TriangleRenderer {
	public:
		TriangleRenderer();
		virtual ~TriangleRenderer();

		void Init();

		void Update();

		void Draw(Camera* _cam);

		void Destroy();

		float GetPosX() {
			return posX;
		}

		float GetPosY() {
			return posY;
		}

		float GetPosZ() {
			return posZ;
		}

		float GetRotX() {
			return rotX;
		}

		float GetRotY() {
			return rotY;
		}

		float GetRotZ() {
			return rotZ;
		}

		float GetScaleX() {
			return scaleX;
		}

		float GetScaleY() {
			return scaleY;
		}

		float GetScaleZ() {
			return scaleZ;
		}

		void SetPos(float _x, float _y, float _z) {
			posX = _x;
			posY = _y;
			posZ = _z;
		}

		void SetRot(float _x, float _y, float _z) {
			rotX = _x;
			rotY = _y;
			rotZ = _z;
		}

		void SetScale(float _x, float _y, float _z) {
			scaleX = _x;
			scaleY = _y;
			scaleZ = _z;
		}
	private:
		GLuint programId;
		GLint vertexPos3DLocation;
		GLint vertexFragmentColourLocation;
		GLuint vboTriangle;

		float posX, posY, posZ;
		float rotX, rotY, rotZ;
		float scaleX, scaleY, scaleZ;

		GLuint transformUniformID;
		GLuint viewUniformID;
		GLuint projectionUniformID;
	};
}
*/