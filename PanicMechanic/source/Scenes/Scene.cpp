#include "Scene.h"
#include "Managers/GameObjectManager.h"

Scene::Scene(const std::string& sceneName)
{
	SceneName = sceneName;
}

Scene::~Scene()
{

}

void Scene::UnloadObjects()
{
	GameObjectManager::GetInstance()->DeleteAllObjectsInScene();
}

const std::string& Scene::GetName() const
{
	return SceneName;
}

void Scene::RegisterObject(Ref<GameObject> object)
{
	GameObjectManager::GetInstance()->AddObject(object);
}