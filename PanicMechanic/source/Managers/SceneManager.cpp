#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::m_Instance = nullptr;

using namespace std;
SceneManager* SceneManager::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new SceneManager();
	}

	return m_Instance;
}

void SceneManager::RegisterScene(Ref<Scene> scene)
{
	m_StoredScenes[scene->GetName()] = scene;
	Debug::Info(" {} has been registered.", scene->GetName());

}

void SceneManager::LoadScene(const std::string& name)
{
	//put a loading screen!

	UnloadScene();
	m_ActiveScene = m_StoredScenes[name];
	m_ActiveScene->LoadResources();
	m_ActiveScene->LoadObjects();

	Debug::Info("To {0} Scene", name);
}

void SceneManager::UnloadScene()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->UnloadObjects();
		m_ActiveScene->UnloadResources();
	}
}

bool SceneManager::IsSceneLoaded(const std::string& name)
{
	return m_ActiveScene->GetName() == name;
}