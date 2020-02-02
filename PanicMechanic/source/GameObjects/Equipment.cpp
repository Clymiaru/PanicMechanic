#include "Equipment.h"
#include "Managers/TextureManager.h"
#include "Game.h"

Equipment::Equipment(std::string name, sf::Keyboard::Key key, bool state, Equipment_Type equipmentType, sf::Vector2f position) :
	GameObject(name),
	keyToRepair(key),
	isRepaired(state),
	isKiller(false),
	equipmentType(equipmentType),
	position(position)
{
	switch (equipmentType)
	{
	case Equipment_Type::Grinder:
		isKiller = true;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	case Equipment_Type::Conveyor_Belt:
		isKiller = true;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	case Equipment_Type::Forge:
		isKiller = false;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	case Equipment_Type::Ballistic_Separator:
		isKiller = true;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	case Equipment_Type::Magnet:
		isKiller = false;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	case Equipment_Type::Fuse_Box:
		isKiller = false;
		m_Rectangle->setSize({ 2 * tileSize.x, 2 * tileSize.y });
		break;
	}
	m_Rectangle->setPosition(position);
	m_Rectangle->setFillColor(sf::Color::Red);
}

void Equipment::Initialize() {
	
	switch (equipmentType)
	{
	case Equipment_Type::Grinder:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("grinder"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	case Equipment_Type::Conveyor_Belt:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("conveyor_belt"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	case Equipment_Type::Forge:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("forge"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	case Equipment_Type::Ballistic_Separator:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("ballistic_separator"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	case Equipment_Type::Magnet:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("magnet"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	case Equipment_Type::Fuse_Box:
		m_Sprite = CreateRef<sf::Sprite>(*TextureManager::GetInstance()->GetTexture("fuse_box"));
		m_Sprite->setScale(64 * 2 / m_Sprite->getGlobalBounds().width,
						   64 * 2 / m_Sprite->getGlobalBounds().height);
		m_Sprite->setPosition(position);
		break;
	}

}

void Equipment::SetPosition(sf::Vector2f position)
{
	
}
void Equipment::Update(const sf::Time& deltaTime) {
	if (!isRepaired)
		m_Sprite->setColor(sf::Color(100, 100, 100, 255));
	else
		m_Sprite->setColor(sf::Color(255, 255, 255, 255));
}

void Equipment::ProcessInput(Ref<sf::Event> event) {

}

bool Equipment::GetCondition()
{
	return isKiller;
}

void Equipment::setState(bool state) {
	isRepaired = state;
}

bool Equipment::getState() {
	return isRepaired;
}