#include "SFXManager.h"

SFXManager* SFXManager::m_Instance = nullptr;

SFXManager* SFXManager::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new SFXManager();
	}
	return m_Instance;
}

void SFXManager::LoadAll()
{
	LoadSFX("explosion", "assets/sfx/Explosion1.wav");
}

void SFXManager::LoadSFX(const std::string& key,
						 const std::string& filepath)
{
	auto buffer = std::make_shared<sf::SoundBuffer>();
	buffer->loadFromFile(filepath);
	m_BufferMap[key] = buffer;

	auto sfx = CreateRef<sf::Sound>();
	sfx->setBuffer(*buffer);
	m_SFXMap[key] = sfx;
}

Ref<sf::Sound> SFXManager::GetSFX(const std::string& key)
{
	if (m_SFXMap[key] != nullptr)
	{
		return m_SFXMap[key];
	}
	else
	{
		Debug::Error("No sound buffer found for {0}!!!", key);
		return nullptr;
	}
}

SFXManager::~SFXManager()
{
	delete m_Instance;
}