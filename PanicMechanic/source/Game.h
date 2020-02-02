#pragma once
#include "Core.h"
#include "Debug.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
	const unsigned int WindowWidth = 1280;
	const unsigned int WindowHeight = 720;
	const char* WindowName = "Panic Mechanic";
public:
	Game();
	~Game();
	void Run();
private:
	Ref<sf::RenderWindow> m_Window;
	Ref<sf::Event> m_Event;
	sf::Clock TimeElapsed;
	sf::Clock CD_Timer;

	// Menu Scene
	sf::Text m_GameTitle;
	sf::Text m_PressToPlay;
	sf::Text m_PressToExit;

	// Game Scene
	sf::Text m_ElapsedTimeLabel;
	sf::Sprite m_Background;
	sf::View m_GameView;
	sf::View m_MiniMapView;
	sf::View m_DefaultView;
	sf::RectangleShape m_BGMinimap;
	sf::Text m_Cooldown;
	sf::Text m_ScoreText;
	sf::Sprite m_BackGround;

	// Results Screen
	sf::Text m_Prompt;

private:
	void ProcessEvents();
	void Update(const sf::Time& deltaTime);
	void Render();

	void HandleWindowCloseByEscapeKey(const sf::Keyboard::Key key);
};