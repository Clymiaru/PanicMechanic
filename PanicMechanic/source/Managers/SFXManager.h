#pragma once
#include "Debug.h"
#include "Core.h"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SFXManager : sf::NonCopyable
{
public:
	static SFXManager* GetInstance();
	void LoadAll();
	Ref<sf::Sound> GetSFX(const std::string& key);

	void LoadSFX(const std::string& key,
						 const std::string& filepath);

	virtual ~SFXManager();
public:

private:
	std::unordered_map<std::string, Ref<sf::Sound>> m_SFXMap;
	std::unordered_map<std::string, Ref<sf::SoundBuffer>> m_BufferMap;
	static SFXManager* m_Instance;
private:

};