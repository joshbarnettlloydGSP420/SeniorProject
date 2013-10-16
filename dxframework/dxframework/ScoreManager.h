#pragma once



#include <string>
#include <Windows.h>

class ScoreManager
{
	private:
		static ScoreManager* instance;
		ScoreManager(void);
		ScoreManager& operator= (const ScoreManager&){}
		ScoreManager(const ScoreManager&){}
public:

	 int score;

	
	~ScoreManager(void);
	static ScoreManager* Get();
	// ScoreManager* GetInstance();
	 void DestroyInstance();

	void Init();

	 void SetScore(int score);
	 int  getScore();
};

