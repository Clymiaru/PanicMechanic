#pragma once
#include "GameObjects/GameObject.h"
#include "Debug.h"
#include "Core.h"
#include <string>
#include <functional>

class UIButton : public GameObject
{
public:
	UIButton(const std::string& name,
			 const sf::Vector2f& position,
			 Ref<sf::Texture> idleTexture,
			 Ref<sf::Texture> pressedTexture);
	void ProcessInput(Ref<sf::Event> event);
	void Update(const sf::Time& deltaTime);
	void Initialize();

private:
	sf::Vector2f m_Position;
	enum class ButtonState
	{
		Idle,
		Pressed
	} m_State = ButtonState::Idle;

	Ref<sf::Texture> m_IdleTexture;
	Ref<sf::Texture> m_PressedTexture;
};

