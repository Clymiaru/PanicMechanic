#pragma once
#include "Core.h"
#include "Debug.h"
#include <string>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	explicit GameObject(const std::string& name);

	virtual void Initialize() = 0;
	virtual void ProcessInput(Ref<sf::Event> event) = 0;
	virtual void Update(const sf::Time& deltaTime) = 0;

	virtual void Draw(Ref<sf::RenderWindow> window);
	
	virtual void setState(bool)
	{}
	virtual bool getState()
	{
		return false;
	}

	virtual bool GetCondition()
	{
		return false;
	}


	sf::FloatRect getGlobalBounds()
	{
		return m_Rectangle->getGlobalBounds();
	}
	const std::string& GetName() const;
	const sf::Vector2f GetPosition() const
	{
		return m_Sprite->getPosition();
	}
public:

protected:
	std::string m_Name;
	Ref<sf::Sprite> m_Sprite;
	Ref<sf::Texture> m_Texture;
	Ref<sf::RectangleShape> m_Rectangle;
	Ref<sf::RectangleShape> m_Hitbox;
protected:

private:

private:
};
