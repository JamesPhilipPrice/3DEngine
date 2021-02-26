#pragma once
#include "Scene.h"
#include <string>
#include <map>
#include <iostream>

namespace GE {
	class SceneManager {
	public:
		//Constructors and deconstructors
		SceneManager();
		~SceneManager();

		//Base functionality
		void ProcessInput();
		void Update(float _deltaTime);
		void Draw(Camera* cam);
		void Shutdown();

		//Scene manager specific functionality
		void AddSceneToMap(std::string _refferenceName, Scene* _scenePointer) {
			stringToScenePointer.insert(std::pair<std::string, Scene*>(_refferenceName, _scenePointer));
			if (stringToScenePointer.size() == 1) {
				//This is the first item to be added to the list. For safety sake, maker the first one the active scene to avoid nullptr refference
				activeScene = _scenePointer;
				std::cout << "Setting " << _refferenceName << " as default active scene" << std::endl;
			}
		}

		void ChangeScene(std::string _refferenceName) {
			activeScene = stringToScenePointer[_refferenceName];
			std::cout << "Setting " << _refferenceName << " to the active scene" << std::endl;
		}

	private:
		std::map<std::string, Scene*> stringToScenePointer;

		Scene* activeScene;
	};
}
