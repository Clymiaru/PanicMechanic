#pragma once
#include "Debug.h"
#include "Core.h"
#include "Scenes/Scene.h"

class SceneManager : sf::NonCopyable
{
public:
	static SceneManager* GetInstance();
	void RegisterScene(Ref<Scene> scene);
	void LoadScene(const std::string& name);
	void UnloadScene();
	bool IsSceneLoaded(const std::string& name);

private:
	static SceneManager* m_Instance;
	
	std::unordered_map<std::string, Ref<Scene>> m_StoredScenes;
	Ref<Scene> m_ActiveScene;
};

