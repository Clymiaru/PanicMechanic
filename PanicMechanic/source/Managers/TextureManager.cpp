#include "TextureManager.h"

TextureManager* TextureManager::m_Instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new TextureManager();
		Debug::Info("New instance of TextureManager has been created.");
	}
	return m_Instance;
}

void TextureManager::LoadAll()
{
	LoadTexture("player", "assets/textures/Mechanic.png");
	LoadTexture("platform", "assets/textures/Terrain.png");

	LoadTexture("grinder", "assets/textures/Grinder.png");
	LoadTexture("conveyor_belt", "assets/textures/Converyor.png");
	LoadTexture("forge", "assets/textures/furnace.png");
	LoadTexture("ballistic_separator", "assets/textures/Ballistic Separator.png");
	LoadTexture("magnet", "assets/textures/Magnetic lifter.png");
	LoadTexture("fuse_box", "assets/textures/fusebox.png");
	LoadTexture("wrench", "assets/textures/Wrench.png");
	LoadTexture("pliers", "assets/textures/Pliers.png");
	LoadTexture("screwdriver", "assets/textures/Screwriver.png");
	LoadTexture("background", "assets/textures/BackGround.png");

}

void TextureManager::LoadTexture(const std::string& key,
								 const std::string& filepath)
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile(filepath);
	m_TextureMap[key] = texture;
	Debug::Info("Texture: '{0}' ({1}) has been loaded.", key, filepath);
}

std::shared_ptr<sf::Texture> TextureManager::GetTexture(const std::string& key)
{
	if (m_TextureMap[key] != nullptr)
	{
		return m_TextureMap[key];
		
	}
	else
	{
		Debug::Error("No texture found for '{0}'!!!", key);
		return nullptr;
	}
}

TextureManager::~TextureManager()
{
	delete m_Instance;
	Debug::Info("Instance of TextureManager has been destroyed.");
}