#pragma once
#include <SDL.h>
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
			SDL_GetMouseState(&oldMouseX, &oldMouseY);
		}
		~Camera() {

		}

		//Accessor methods
		float GetPosX() {
			return pos.x;
		}

		float GetPosY() {
			return pos.y;
		}

		float GetPosZ() {
			return pos.z;
		}

		glm::vec3 GetPos() {
			return pos;
		}

		glm::vec3 GetTarget() {
			return target;
		}

		glm::vec3 GetUpDir() {
			return up;
		}

		float GetPitch() {
			return pitch;
		}

		float GetYaw() {
			return yaw;
		}

		float GetOldMouseX() {
			return oldMouseX;
		}

		float GetOldMouseY() {
			return oldMouseY;
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

		void SetPos(glm::vec3 _newPos) {
			pos = _newPos;
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

		void SetPitch(float _newPitch) {
			pitch = _newPitch;

			if (pitch > 70.0f) {
				pitch = 70.0f;
			}
			if (pitch < -70.0f) {
				pitch = -70.0f;
			}
		}

		void SetYaw(float _newYaw) {
			yaw = _newYaw;
		}

		void SetOldMouseX(float _newOldMouseX) {
			oldMouseX = _newOldMouseX;
		}

		void SetOldMouseY(float _newOldMouseY) {
			oldMouseY = _newOldMouseY;
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

		void UpdateCameraMatricies() {
			viewMatrix = glm::lookAt(pos, pos + target, up);
			projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearClip, farClip);
		}

	private:
		glm::vec3 pos;
		glm::vec3 target;
		glm::vec3 up;

		float fovY;
		float aspectRatio;
		float nearClip;
		float farClip;

		//Pitch and yaw
		float pitch = 0.0f;
		float yaw = -90.0f;

		//Mouse related variables
		int oldMouseX, oldMouseY;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}