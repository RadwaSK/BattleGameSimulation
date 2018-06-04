#pragma once
#include "Enemy.h"


class Dragon:public Enemy
{
	int MaxFireHeatTime; // the duration of the Dmg he can deal after hitting the tower.
	int FireHeatTime;    // the Step at which he is from hitting tower to reach " MaxFireHeatTime.
	bool Attacked;		 // to make the fire deals damage to towers been hit only.
public:
	Dragon(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp);
	void ResetFireHeatTime();  // Start from 0 till it reach MaxFirHeatTime.
	//virtual functions
	virtual void Move();
	virtual void Attack();
	virtual void AttackAfterDeath(); // for the dmg of the fire on the towers after death.
	void ResetAttack();				// to set attacked = false
	virtual void Heal();

};