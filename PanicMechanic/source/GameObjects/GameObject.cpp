#include "GameObject.h"

GameObject::GameObject(const std::string& name) :
	m_Name(name),
	m_Sprite(CreateRef<sf::Sprite>()),
	m_Texture(CreateRef<sf::Texture>()),
	m_Rectangle(CreateRef<sf::RectangleShape>()),
	m_Hitbox(CreateRef<sf::RectangleShape>())
{
}

void GameObject::Draw(Ref<sf::RenderWindow> window)
{
	window->draw(*m_Sprite);
	//window->draw(*m_Rectangle);
}

const std::string& GameObject::GetName() const
{
	return m_Name;
}