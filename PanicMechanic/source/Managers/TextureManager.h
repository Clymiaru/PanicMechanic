#pragma once
#include "Debug.h"
#include "Core.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager : sf::NonCopyable
{
public:
	static TextureManager* GetInstance();
	void LoadAll();
	Ref<sf::Texture> GetTexture(const std::string& key);

	void LoadTexture(const std::string& key,
					 const std::string& filepath);

	virtual ~TextureManager();
public:

private:
	std::unordered_map<std::string, Ref<sf::Texture>> m_TextureMap;
	static TextureManager* m_Instance;
private:

};

