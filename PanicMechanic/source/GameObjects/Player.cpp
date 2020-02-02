#include "GameObjects/GameObject.h"
#include "SFML/Graphics.hpp"
#include "Managers/TextureManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/FontManager.h"
#include "Managers/ScoreManager.h"
#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(string name) :
	GameObject(name)
{
	velocity.x = 0;
	velocity.y = 0;
	m_Sprite->setPosition({ 32,0 });
	m_Rectangle->setPosition({ 32,0 });
	m_Rectangle->setFillColor(Color::Blue);

	m_Cooldown.setFont(*FontManager::GetInstance()->GetFont("sansation"));
	m_Cooldown.setFillColor(sf::Color::White);
	m_Cooldown.setCharacterSize(26);
}

void Player::Initialize()
{
	m_Texture = TextureManager::GetInstance()->GetTexture("player");
	m_Sprite->setTexture(*m_Texture);
	m_Rectangle->setSize(playerSize);
	FloatRect bounds = m_Sprite->getGlobalBounds();
	m_Sprite->setOrigin(bounds.width / 2, bounds.height / 2);
	m_Sprite->setScale(32 / bounds.width,
		32 / bounds.height);
	bounds = m_Rectangle->getGlobalBounds();
	m_Rectangle->setOrigin({ bounds.width / 2, bounds.height / 2 });
}

void Player::ProcessInput(Ref<sf::Event> event)
{

	auto checkSideCollision = [&](Ref<GameObject> obj) -> bool
	{
		return GetPosition().x + getGlobalBounds().width / 2 + collisionLimit > obj->GetPosition().x&& GetPosition().x - getGlobalBounds().width / 2 - collisionLimit < obj->GetPosition().x + obj->getGlobalBounds().width
			&& GetPosition().y + getGlobalBounds().height / 2 + collisionLimit > obj->GetPosition().y && GetPosition().y - getGlobalBounds().height / 2 - collisionLimit < obj->GetPosition().y + obj->getGlobalBounds().height;
	};

	switch (event->type)
	{
	case Event::KeyPressed:
		switch (event->key.code)
		{
		case Keyboard::Space:
		case Keyboard::W:
			if (velocity.y == 0)
				velocity.y = -verticalSpeed;
			break;
		case Keyboard::A:
			velocity.x = -horizontalSpeed;
			break;
		case Keyboard::D:
			velocity.x = horizontalSpeed;
			break;
		case Wrench:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (checkSideCollision(obj) && !obj->getState()
					&& (obj->GetName() == "grinder" || obj->GetName() == "conveyor_belt")) {
					cout << "Intersects"<<endl;
					Repairing = true;
					break;
				}
			}
			break;
		case Pliers:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (checkSideCollision(obj) && !obj->getState()
					&& (obj->GetName() == "forge" || obj->GetName() == "fuse_box")) {
					cout << "Intersects" << endl;
					Repairing = true;
					break;
				}
			}
			break;
		case Screwdriver:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (checkSideCollision(obj) && !obj->getState()
					&& (obj->GetName() == "ballistic_separator" || obj->GetName() == "magnet")) {
					cout << "Intersects" << endl;
					Repairing = true;
					break;
				}
			}
			break;
		}
		break;
	case Event::KeyReleased:
		switch (event->key.code)
		{
		case Keyboard::A:
			if (velocity.x < 0)
				velocity.x = 0;
			break;
		case Keyboard::D:
			if (velocity.x > 0)
				velocity.x = 0;
			break;
		case Wrench:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (GetPosition().x + getGlobalBounds().width / 2 - collisionLimit > obj->GetPosition().x&& GetPosition().x - getGlobalBounds().width / 2 + collisionLimit < obj->GetPosition().x + obj->getGlobalBounds().width
					&& (obj->GetName() == "grinder" || obj->GetName() == "conveyor_belt")) {
					Repairing = false;
					break;
				}
				else if (GetPosition().y + getGlobalBounds().height / 2 - collisionLimit > obj->GetPosition().y&& GetPosition().y - getGlobalBounds().height / 2 + collisionLimit < obj->GetPosition().y + obj->getGlobalBounds().height
					&& (obj->GetName() == "grinder" || obj->GetName() == "conveyor_belt")) {
					Repairing = false;
					break;
				}
			}
			break;
		case Pliers:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (GetPosition().x + getGlobalBounds().width / 2 - collisionLimit > obj->GetPosition().x&& GetPosition().x - getGlobalBounds().width / 2 + collisionLimit < obj->GetPosition().x + obj->getGlobalBounds().width
					&& (obj->GetName() == "forge" || obj->GetName() == "fuse_box")) {
					Repairing = false;
					break;
				}
				else if (GetPosition().y + getGlobalBounds().height / 2 - collisionLimit > obj->GetPosition().y&& GetPosition().y - getGlobalBounds().height / 2 + collisionLimit < obj->GetPosition().y + obj->getGlobalBounds().height
					&& (obj->GetName() == "forge" || obj->GetName() == "fuse_box")) {
					Repairing = false;
					break;
				}
			}
			break;
		case Screwdriver:
			for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
				if (GetPosition().x + getGlobalBounds().width / 2 - collisionLimit > obj->GetPosition().x && GetPosition().x - getGlobalBounds().width / 2 + collisionLimit < obj->GetPosition().x + obj->getGlobalBounds().width
					&& (obj->GetName() == "ballistic_separator" || obj->GetName() == "magnet")) {
					Repairing = false;
					break;
				}
				else if (GetPosition().y + getGlobalBounds().height / 2 - collisionLimit > obj->GetPosition().y&& GetPosition().y - getGlobalBounds().height / 2 + collisionLimit < obj->GetPosition().y + obj->getGlobalBounds().height
					&& (obj->GetName() == "ballistic_separator" || obj->GetName() == "magnet")) {
					Repairing = false;
					break;
				}
			}
			break;
		}
		break;

	}
}

void Player::Move(const sf::Time& deltaTime)
{
	m_Sprite->move(velocity * deltaTime.asSeconds());
	m_Rectangle->move(velocity * deltaTime.asSeconds());
}

void Player::Update(const sf::Time& deltaTime)
{
	velocity.y += Gravity * deltaTime.asSeconds();

	if (!Repairing)
	{
		Move(deltaTime);
		CollisionDetection();
	}
	
	if (cooldown.asSeconds() >= 1.0f) {
		for (auto obj : GameObjectManager::GetInstance()->GetAllObjects()) {
			
				if ((GetPosition().x + getGlobalBounds().width / 2 + collisionLimit > obj->GetPosition().x && GetPosition().x - getGlobalBounds().width / 2 - collisionLimit < obj->GetPosition().x + obj->getGlobalBounds().width
					&& GetPosition().y + getGlobalBounds().height / 2 + collisionLimit > obj->GetPosition().y && GetPosition().y - getGlobalBounds().height / 2 - collisionLimit < obj->GetPosition().y + obj->getGlobalBounds().height )
					&& (obj->GetName() == "ballistic_separator" || 
						obj->GetName() == "magnet" || 
						obj->GetName() == "forge" || 
						obj->GetName() == "fuse_box" || 
						obj->GetName() == "grinder" || 
						obj->GetName() == "conveyor_belt") ) {
					Repairing = false;
					cooldown = sf::Time::Zero;
					ScoreManager::AddScore(100 * ScoreManager::GetElapsedTime());
					ScoreManager::AddFixed();
					obj->setState(true);
					break;
				}
		}
	}
	else if (Repairing) {
		cooldown += deltaTime;
	}
	else if (!Repairing) {
		cooldown = sf::Time::Zero;
	}
}

void Player::CollisionDetection()
{
	FloatRect playerBounds = getGlobalBounds();

	for (auto object : GameObjectManager::GetInstance()->GetAllObjects())
	{
		FloatRect temp = object->getGlobalBounds();
		if (playerBounds.intersects(temp) && object->GetName() != "Player")
		{
			DisplacePlayer(object);
		}
	}
}

void Player::DisplacePlayer(Ref<GameObject> object)
{
	Vector2f playerPos = GetPosition();
	FloatRect playerBounds = getGlobalBounds();
	Vector2f objectPos = object->GetPosition();
	FloatRect objectBounds = object->getGlobalBounds();

	if (playerPos.x + playerBounds.width / 2 - collisionLimit > objectPos.x&& playerPos.x - playerBounds.width / 2 + collisionLimit < objectPos.x + objectBounds.width)
	{
		if (playerPos.y < objectPos.y + objectBounds.height)
		{
			m_Rectangle->setPosition({ playerPos.x, objectPos.y - playerBounds.height / 2 });
			velocity.y = 0;
			if (object->GetName() != "Player" && object->GetName() != "platform")
			{
				if (object->GetCondition() && object->getState())
					respawn();
			}
			else
			{
				respawnPoint = m_Rectangle->getPosition();

			}
		}
		else if (playerPos.y > objectPos.y)
		{
			m_Rectangle->setPosition({ playerPos.x, objectPos.y + objectBounds.height + playerBounds.height / 2 });
			velocity.y = 0;
		}

	}
	else if (playerPos.y + playerBounds.height / 2 - collisionLimit > objectPos.y&& playerPos.y - playerBounds.height / 2 + collisionLimit < objectPos.y + objectBounds.height)
	{
		if (playerPos.x < objectPos.x)
		{
			m_Rectangle->setPosition({ objectPos.x - playerBounds.width / 2, playerPos.y });
		}
		else if (playerPos.x > objectPos.x)
		{
			m_Rectangle->setPosition({ objectPos.x + playerBounds.width / 2 + objectBounds.width, playerPos.y });
		}
	}
	m_Sprite->setPosition(m_Rectangle->getPosition());
}

void Player::Draw(Ref<sf::RenderWindow> window)
{
	window->draw(*m_Sprite);

}

bool Player::GetCondition() {
	return Repairing;
}