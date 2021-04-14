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

		// �O�����̒藝�ŉ~�`�����蔻��
		return (length * length >= xLen * xLen + yLen * yLen);
	}
};