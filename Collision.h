#pragma once
#include "Pos.h"

class Collision
{
public:
	bool isCollision(Pos p, Pos q, double dp, double dq)
	{
		double length = dp + dq;
		double xLen = p.x - q.x;
		double yLen = p.y - q.y;

		// ŽO•½•û‚Ì’è—‚Å‰~Œ`“–‚½‚è”»’è
		return (length * length >= xLen * xLen + yLen * yLen);
	}
};