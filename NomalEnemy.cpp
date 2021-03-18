#include "Enemy.h"

class NomalEnemy : public Enemy
{
public:
	void move(int frame) override
	{
		Enemy::move(frame);
	}
};