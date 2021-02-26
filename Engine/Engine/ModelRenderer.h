#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Terrain.h"
#include "Skydome.h"

namespace GE {
	class ModelRenderer {
	public:
		ModelRenderer(Model* _model, Camera* _cam);
		virtual ~ModelRenderer();

		void Init();

		void Update();

		void Draw(Camera* _cam);
		void DrawTerrain(Terrain* _terrain);
		void DrawSkydome(Skydome* _skydome);

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

		void SetMaterial(Texture* _tex) {
			material = _tex;
		}
	private:
		Camera* camera;

		GLuint programId;
		GLint vertexPos3DLocation;
		GLint vertexUVLocation;
		GLuint vboModel;

		float posX, posY, posZ;
		float rotX, rotY, rotZ;
		float scaleX, scaleY, scaleZ;

		GLuint transformUniformID;
		GLuint viewUniformID;
		GLuint projectionUniformID;
		GLuint samplerID;

		Model* model;

		Texture* material;
	};
}
