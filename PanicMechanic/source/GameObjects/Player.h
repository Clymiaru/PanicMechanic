#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObjects/GameObject.h"

class Player : public GameObject
{

	float const Gravity = 1300;
	float const horizontalSpeed = 350;
	float const verticalSpeed = 900;
	float const collisionLimit = 16;
	sf::Vector2f const playerSize = { 32, 32 };
private:
	sf::Vector2f velocity;
	bool Repairing = false;
	sf::Vector2f respawnPoint;
	sf::Text m_Cooldown;


private:
	void Move(const sf::Time& deltaTime);

public:
	sf::Time cooldown = sf::Time::Zero;
	Player(std::string);
	void ProcessInput(Ref<sf::Event> event);
	void Update(const sf::Time& deltaTime);
	void Initialize();
	void CollisionDetection();
	void DisplacePlayer(Ref<GameObject> object);
	void Draw(Ref<sf::RenderWindow> window);
	void SetPosition(sf::Vector2f position)
	{
		m_Sprite->setPosition(position);
		m_Rectangle->setPosition(position);
	}
	void respawn()
	{
		SetPosition(respawnPoint);
		CollisionDetection();
	}
	bool GetCondition();

	enum Tool_Type
	{
		Wrench = sf::Keyboard::J, Pliers = sf::Keyboard::K, Screwdriver = sf::Keyboard::L
	};
	
};