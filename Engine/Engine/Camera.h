#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE {
	class Camera {
	public:
		Camera(glm::vec3 _camPos, glm::vec3 _camTarget, glm::vec3 _upDir, float _fov, float _ar, float _near, float _far) {
			pos = _camPos;
			target = _camTarget;
			up = _upDir;

			fovY = _fov;
			aspectRatio = _ar;
			nearClip = _near;
			farClip = _far;

			UpdateCameraMatricies();
		}
		~Camera() {

		}

		//Accessor methods
		float getPosX() {
			return pos.x;
		}

		float getPosY() {
			return pos.y;
		}

		float getPosZ() {
			return pos.z;
		}

		glm::vec3 getTarget() {
			return target;
		}

		glm::vec3 GetUpDir() {
			return up;
		}

		glm::mat4 GetViewMatrix() {
			return viewMatrix;
		}

		glm::mat4 GetProjectMatrix() {
			return projectionMatrix;
		}

		//Mutator methods
		void SetPosX(float _newX) {
			pos = glm::vec3(_newX, pos.y, pos.z);
			UpdateCameraMatricies();
		}

		void SetPosY(float _newY) {
			pos = glm::vec3(pos.x, _newY, pos.z);
			UpdateCameraMatricies();
		}

		void SetPosZ(float _newZ) {
			pos = glm::vec3(pos.x, pos.y, _newZ);
			UpdateCameraMatricies();
		}

		void SetPos(float _newX, float _newY, float _newZ) {
			pos = glm::vec3(_newX, _newY, _newZ);
			UpdateCameraMatricies();
		}

		void SetTarget(glm::vec3 _newTarget) {
			target = _newTarget;

			UpdateCameraMatricies();
		}

		void SetUpDir(glm::vec3 _newUp) {
			up = _newUp;
			UpdateCameraMatricies();
		}

		void SetFOV(float _newFOV) {
			fovY = _newFOV;
			UpdateCameraMatricies();
		}

		void SetAspectRatio(float _newAR) {
			aspectRatio = _newAR;
			UpdateCameraMatricies();
		}

		void SetNearClip(float _newNearClip) {
			nearClip = _newNearClip;
			UpdateCameraMatricies();
		}

		void SetFarClip(float _newFarClip) {
			farClip = _newFarClip;
			UpdateCameraMatricies();
		}

	private:
		glm::vec3 pos;
		glm::vec3 target;
		glm::vec3 up;

		float fovY;
		float aspectRatio;
		float nearClip;
		float farClip;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		void UpdateCameraMatricies() {
			viewMatrix = glm::lookAt(pos, target, up);
			projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearClip, farClip);
		}
	};
}