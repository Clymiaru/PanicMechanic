#include "FontManager.h"

FontManager* FontManager::m_Instance = nullptr;

FontManager* FontManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new FontManager();
		Debug::Info("New instance of FontManager has been created.");
	}
	return m_Instance;
}

void FontManager::LoadAll()
{
	LoadFont("sansation", "assets/font/Sansation.ttf");
}

void FontManager::LoadFont(const std::string& key,
						   const std::string& filepath)
{
	auto font = CreateRef<sf::Font>();
	font->loadFromFile(filepath);
	m_FontMap[key] = font;
	Debug::Info("Font: '{0}' ({1}) has been loaded.", key, filepath);
}

Ref<sf::Font> FontManager::GetFont(const std::string& key)
{
	if (m_FontMap[key] != nullptr)
	{
		return m_FontMap[key];

	}
	else
	{
		Debug::Error("No font found for '{0}'!!!", key);
		return nullptr;
	}
}

FontManager::~FontManager()
{
	delete m_Instance;
	Debug::Info("Instance of FontManager has been destroyed.");
}