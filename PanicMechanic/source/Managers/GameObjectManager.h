#pragma once
#include "Debug.h"
#include "Core.h"
#include <unordered_map>
#include <vector>
#include <SFML/System.hpp>
#include "GameObjects/GameObject.h"

class GameObjectManager : sf::NonCopyable
{
public:
	static GameObjectManager* GetInstance();

	Ref<GameObject> FindObjectByName(const std::string& name);
	std::vector<Ref<GameObject>> GetAllObjects();
	int ActiveObjects();
	void ProcessInput(Ref<sf::Event> event);
	void Update(const sf::Time& deltaTime);
	void Draw(Ref<sf::RenderWindow> window);
	void AddObject(Ref<GameObject> gameObject);
	void DeleteObject(Ref<GameObject> gameObject);
	void DeleteObjectByName(const std::string& name);
	void DeleteAllObjectsInScene();
public:

protected:

protected:

private:
	static GameObjectManager* m_Instance;
	std::unordered_map<std::string, Ref<GameObject>> m_GameObjectMap;
	std::vector<Ref<GameObject>> m_GameObjectList;
private:


};

