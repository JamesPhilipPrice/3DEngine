#pragma once
#include "Camera.h"
namespace GE {
	class Scene {
	public:
		Scene() {}
		~Scene(){}

		virtual bool Init(Camera* _cam) {
			return false;
		}
		virtual void ProcessInput() {}
		virtual void Update(float _deltaTime) {}
		virtual void Draw(Camera* _cam) {}
		virtual void Shutdown() {}
	};
}
