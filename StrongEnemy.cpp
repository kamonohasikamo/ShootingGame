#include "Enemy.h"

class StrongEnemy : public Enemy
{
public:
	void move(int frame) override
	{
		Enemy::move(frame);
	}
};