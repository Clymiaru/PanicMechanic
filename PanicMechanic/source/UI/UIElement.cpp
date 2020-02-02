#include "UIElement.h"

UIElement::UIElement(const std::string& name) : GameObject(name)
{

}

UIElement::~UIElement()
{
	GameObject::~GameObject();
}