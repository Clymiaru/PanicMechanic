#pragma once
#include "Debug.h"
#include "Core.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class FontManager : sf::NonCopyable
{
public:
	static FontManager* GetInstance();
	void LoadAll();
	Ref<sf::Font> GetFont(const std::string& key);

	void LoadFont(const std::string& key,
				  const std::string& filepath);

	virtual ~FontManager();
public:

private:
	std::unordered_map<std::string, Ref<sf::Font>> m_FontMap;
	static FontManager* m_Instance;
private:

};

