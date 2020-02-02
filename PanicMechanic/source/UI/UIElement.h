#pragma once
#include "Debug.h"
#include "Core.h"
#include "GameObjects/GameObject.h"

class UIElement : public GameObject
{
public:
	UIElement(const std::string& name);
	~UIElement();
};

