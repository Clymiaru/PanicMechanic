#pragma once
#include "Debug.h"
#include "Core.h"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class BGMManager : sf::NonCopyable
{
public:
	static BGMManager* GetInstance();
	void LoadAll();
	Ref<sf::Music> GetBGM(const std::string& key);

	void LoadBGM(const std::string& key,
				 const std::string& filepath);

	virtual ~BGMManager();
public:

private:
	std::unordered_map<std::string, Ref<sf::Music>> m_BGMMap;
	static BGMManager* m_Instance;
private:

};