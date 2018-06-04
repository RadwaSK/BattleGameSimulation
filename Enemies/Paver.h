#pragma once
#include"Enemy.h"

class Paver :public Enemy
{
	
public:
	Paver(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp);
	
	//virtual functions
	virtual void ResetFireHeatTime();
	virtual void Move();
	virtual void Attack();
	virtual void Heal();
};