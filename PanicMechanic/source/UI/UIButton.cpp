#include "UIButton.h"

UIButton::UIButton(const std::string& name, 
				   const sf::Vector2f& position,
				   Ref<sf::Texture> idleTexture,
				   Ref<sf::Texture> pressedTexture) :
	GameObject(name),
	m_Position(position),
	m_IdleTexture(idleTexture),
	m_PressedTexture(pressedTexture)
{

}

void UIButton::ProcessInput(Ref<sf::Event> event)
{
	if (event->type == sf::Event::MouseButtonPressed)
	{

	}
}

void UIButton::Update(const sf::Time& deltaTime)
{

}
void UIButton::Initialize()
{

}
