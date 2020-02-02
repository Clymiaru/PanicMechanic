#pragma once
#include <SFML/Graphics.hpp>
class ScoreManager
{
	static int Score;
	static sf::Clock Clock;
	static int Fixed;
public:
	static void AddScore(int score);
	static void Reset();
	static int GetScore();

	static void StartClock();
	static float GetElapsedTime();

	static void AddFixed();
	static bool IsAllFixed();
};

