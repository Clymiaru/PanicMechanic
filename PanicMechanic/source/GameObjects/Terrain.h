#pragma once
#include "GameObject.h"
#include "Debug.h"
#include "Core.h"

class Terrain : public GameObject
{
public:
	Terrain(const std::string& name, 
			const sf::Vector2f& position, 
			const sf::Vector2f& newSize);
	void Initialize();
	void ProcessInput(Ref<sf::Event> event);
	void Update(const sf::Time& deltaTime);

private:
	sf::Vector2f size;
};