#include "SceneManager.h"

namespace GE {
	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::ProcessInput()
	{
		activeScene->ProcessInput();
	}

	void SceneManager::Update(float _deltaTime)
	{
		activeScene->Update();
	}

	void SceneManager::Draw(Camera* _cam)
	{
		activeScene->Draw(_cam);
	}

	void SceneManager::Shutdown()
	{
		activeScene->Shutdown();
	}

}
