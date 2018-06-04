#pragma once
#include"Enemy.h"

class ShieldedFighter:public Enemy
{
	double C1, C2, C3; //constants

public:

	ShieldedFighter(int id, double arrTime,double heal,double firepow,double reloadper, char r_region,int sp, double c1, double c2, double c3);
	
	//needed in operator > overloading to sort
	void CalculatePeriorty();

	//virtual functions
	virtual void SetState();
	virtual void ResetFireHeatTime();
	virtual void Move();
	virtual void Attack();
	virtual void Heal();
};