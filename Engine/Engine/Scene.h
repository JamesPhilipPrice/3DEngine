#pragma once
#include "Camera.h"
namespace GE {
	class Scene {
	public:
		Scene() {}
		~Scene(){}

		virtual bool Init() {
			return false;
		}
		virtual void ProcessInput() {}
		virtual void Update() {}
		virtual void Draw(Camera* _cam) {}
		virtual void Shutdown() {}
	};
}
