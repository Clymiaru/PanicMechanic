#include "Terrain.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Managers/TextureManager.h"

using namespace std;
using namespace sf;

Terrain::Terrain(const std::string& name,
				 const sf::Vector2f& position,
				 const sf::Vector2f& newSize) :
	GameObject(name)
{
	m_Sprite->setPosition(position);
	m_Rectangle->setPosition(position);
	size = newSize;
	m_Rectangle->setSize(size);
}

void Terrain::Initialize()
{
	m_Texture = TextureManager::GetInstance()->GetTexture("platform");
	m_Sprite->setTexture(*m_Texture);
	m_Sprite->setScale({ size.x / m_Sprite->getGlobalBounds().width,  size.y / m_Sprite->getGlobalBounds().height });
}

void Terrain::ProcessInput(Ref<sf::Event> event)
{

}

void Terrain::Update(const sf::Time& deltaTime)
{

}