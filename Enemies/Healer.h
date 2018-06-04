#pragma once
#include "Enemy.h"

class Healer : public Enemy
{
	int N; //number of enemies to heal each time
public:
	Healer(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp);

	//virtual functions
	virtual void Move();
	virtual void Attack();
	virtual void Heal();
	virtual void ResetFireHeatTime();
};
