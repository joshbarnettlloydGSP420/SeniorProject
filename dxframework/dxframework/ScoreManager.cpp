#include "ScoreManager.h"


ScoreManager* ScoreManager::instance = NULL;

ScoreManager::ScoreManager(void)
{
}


ScoreManager::~ScoreManager(void)
{
}

ScoreManager* ScoreManager::Get()
{
	if ( instance == 0)
		instance = new ScoreManager();
	return instance;
}

void ScoreManager::DestroyInstance()
{
	if ( instance)
	{
		delete instance;
		instance = NULL;
	}
}

void ScoreManager::Init()
{
	score = 0;
}

void ScoreManager::SetScore(int newScore)
{
	score = newScore;
}

int  ScoreManager::getScore()
{
	return score;
}