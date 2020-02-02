#include "ScoreManager.h"
#include "Debug.h"
int ScoreManager::Score = 0;
sf::Clock ScoreManager::Clock; 
int ScoreManager::Fixed = 0;

void ScoreManager::AddScore(int score)
{
	Score += score;
}

void ScoreManager::Reset()
{
	Score = 0;
	Fixed = 0;
	Clock.restart();
}

int ScoreManager::GetScore()
{
	return Score;
}

void ScoreManager::StartClock()
{
	Clock.restart();
}
float ScoreManager::GetElapsedTime()
{
	return Clock.getElapsedTime().asSeconds();
}

void ScoreManager::AddFixed()
{
	Fixed++;
}

bool ScoreManager::IsAllFixed()
{
	return (Fixed == 5);
}