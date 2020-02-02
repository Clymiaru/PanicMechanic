#include "BGMManager.h"

BGMManager* BGMManager::m_Instance = nullptr;

BGMManager* BGMManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new BGMManager();
	}
	return m_Instance;
}

void BGMManager::LoadAll()
{
	LoadBGM("test", "assets/bgm/test.ogg");
}

void BGMManager::LoadBGM(const std::string& key,
						 const std::string& filepath)
{
	auto bgm = std::make_shared<sf::Music>();
	bgm->openFromFile(filepath);
	m_BGMMap[key] = bgm;

}

Ref<sf::Music> BGMManager::GetBGM(const std::string& key)
{
	if (m_BGMMap[key] != nullptr)
	{
		return m_BGMMap[key];
	}
	else
	{
		Debug::Error("No sound buffer found for {0}!!!", key);
		return nullptr;
	}
}

BGMManager::~BGMManager()
{
	delete m_Instance;
}