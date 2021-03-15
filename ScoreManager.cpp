#include "DxLib.h"
#include <string>

using namespace std;

class ScoreManager
{
private:
	int score;
public:
	ScoreManager()
	{
		score = 0;
	}

	void addScore(int add)
	{
		score += add;
	}

	int getScore()
	{
		return score;
	}
};