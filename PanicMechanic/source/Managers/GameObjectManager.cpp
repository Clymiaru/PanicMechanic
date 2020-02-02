#include "GameObjectManager.h"
#include <algorithm>
GameObjectManager* GameObjectManager::m_Instance = nullptr;

GameObjectManager* GameObjectManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameObjectManager();
		Debug::Info("New instance of GameObjectManager has been created.");
	}
	return m_Instance;
}


Ref<GameObject> GameObjectManager::FindObjectByName(const std::string& name)
{
	if (m_GameObjectMap[name] != nullptr)
	{
		return m_GameObjectMap[name];
	}
	else
	{
		Debug::Error("Object '{0}' not found!!!", name);
		return nullptr;
	}
}

std::vector<Ref<GameObject>> GameObjectManager::GetAllObjects()
{
	return m_GameObjectList;
}

int GameObjectManager::ActiveObjects()
{
	return m_GameObjectList.size();
}


void GameObjectManager::ProcessInput(Ref<sf::Event> event)
{
	for (auto a : m_GameObjectList)
	{
		a->ProcessInput(event);
	}
}

void GameObjectManager::Update(const sf::Time& deltaTime)
{
	for (auto a : m_GameObjectList)
	{
		a->Update(deltaTime);
	}
}


void GameObjectManager::Draw(Ref<sf::RenderWindow> window)
{
	for (auto a : m_GameObjectList)
	{
		a->Draw(window);
	}
}

void GameObjectManager::AddObject(Ref<GameObject> gameObject)
{
	m_GameObjectMap[gameObject->GetName()] = gameObject;
	m_GameObjectList.push_back(gameObject);
	gameObject->Initialize();
	Debug::Info("GameObject: '{0}' has been added to GameObjectManager.", gameObject->GetName());
}


void GameObjectManager::DeleteObject(Ref<GameObject> gameObject)
{
	std::string key = gameObject->GetName();
	gameObject.reset();
	m_GameObjectMap.erase(key);
	m_GameObjectList.erase(std::remove(m_GameObjectList.begin(), m_GameObjectList.end(), gameObject), m_GameObjectList.end());
	m_GameObjectList.shrink_to_fit();
	Debug::Info("GameObject: '{0}' has been deleted from GameObjectManager.", gameObject->GetName());
}

void GameObjectManager::DeleteObjectByName(const std::string& name)
{
	Ref<GameObject> object = FindObjectByName(name);

	if (object.use_count() == 1)
	{
		DeleteObject(object);
	}
}

void GameObjectManager::DeleteAllObjectsInScene()
{
	m_GameObjectList.clear();
	m_GameObjectList.shrink_to_fit();
	m_GameObjectMap.clear();
}
