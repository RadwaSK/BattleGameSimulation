#pragma once
#include"Enemy.h"


class Fighter:public Enemy
{
	
public:
	Fighter(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp);

	//virtual functions
	virtual void Move();
	virtual void ResetFireHeatTime();
	virtual void Attack();
	virtual void Heal();
};