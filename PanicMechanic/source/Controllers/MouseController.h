#pragma once
#include "Debug.h"
#include "Core.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class MouseController : sf::NonCopyable
{
public:
	static MouseController* GetInstance();
	sf::Vector2i GetMousePosition();

	virtual ~MouseController();
public:

private:
	static MouseController* m_Instance;
private:

};
