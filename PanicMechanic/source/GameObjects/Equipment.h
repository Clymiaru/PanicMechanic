#pragma once
#include "GameObject.h"
class Equipment : public GameObject
{
	sf::Vector2f const tileSize = { 64, 64 };
public:
	enum class Equipment_Type
	{
		Grinder, Conveyor_Belt, Forge, Ballistic_Separator, Magnet, Fuse_Box
	} equipmentType;

public:
	Equipment(std::string, sf::Keyboard::Key, bool, Equipment::Equipment_Type, sf::Vector2f);
	void Initialize();
	void ProcessInput(Ref<sf::Event> event);
	void Update(const sf::Time& deltaTime);
	void SetPosition(sf::Vector2f);
	bool GetCondition();
	void setState(bool);
	bool getState();

private:
	bool isRepaired;
	bool isKiller = false;
	sf::Keyboard::Key keyToRepair;
	sf::Vector2f position;

	
};

