#include "DxLib.h"
#include <string>
#include <list>

using namespace std;
/*
class ScoreObserver
{
public:
	virtual ~ScoreObserver(void) {};
	virtual void initScore() = 0;
	virtual void changeScore(int score) = 0;


	void SetObject(ScoreUI* subject)
	{
		m_scoreSubject = subject;
	}
protected:
	ScoreUI* m_scoreSubject;
};

class ScoreUI : public ScoreObserver
{
private:
	int number[10];
	int scoreBoard;
public:
	ScoreUI(void) {}
	virtual ~ScoreUI(void) {}

	virtual void initScore(void)
	{
		// init score show 
		// char buf[100];
		// DrawGraph(300, 10, scoreBoard, true);
		// int num = sprintf(buf, "%d", 0);
		// for (int i = 0; i < num; i++)
		// {
		// 	DrawGraph(300 + 20 + i * 19, 10, number[(buf[i] - '0')], true);
		// }
	}

	virtual void changeScore(int score)
	{
		// change score show
		// char buf[100];
		// DrawGraph(300, 10, scoreBoard, true);
		// int num = sprintf(buf, "%d", score);
		// for (int i = 0; i < num; i++)
		// {
		// 	DrawGraph(300 + 20 + i * 19, 10, number[(buf[i] - '0')], true);
		// }
	}
};

class ScoreClass
{
private:
	int score;
protected:
	list<ScoreObserver*> m_scoreOvserve;
public:
	ScoreClass(void) {}

	virtual ~ScoreClass(void)
	{
		list<ScoreObserver*>::iterator it;
		for (it = m_scoreOvserve.begin(); it != m_scoreOvserve.end(); it++)
		{
			(*it)->SetObject(NULL);
		}
	}

	virtual void initScore(void)
	{
		list<ScoreObserver*>::iterator it;
		for (it = m_scoreOvserve.begin(); it != m_scoreOvserve.end(); it++)
		{
			(*it)->initScore();
		}
		this->score = 0;
	}

	void addScore(int add)
	{
		score += add;
		list<ScoreObserver*>::iterator it;
		for (it = m_scoreOvserve.begin(); it != m_scoreOvserve.end(); it++)
		{
			(*it)->changeScore(score);
		}
	}

	int getScore()
	{
		return score;
	}
};
*/