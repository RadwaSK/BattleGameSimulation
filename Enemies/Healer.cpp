#include "Healer.h"
#include "..\Castle\Tower.h"


Healer::Healer(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp) : Enemy(id,HEALER,arrTime,heal,firepow,reloadper, DARKVIOLET ,r_region,sp){
	Priority = arrTime;
	K = 0.5;
	N = FirePower/2;
	if (N == 0) N = 1; //Lowest value for N
}
void Healer::ResetFireHeatTime()
{}

//virtual functions
void Healer::Move()
{
	if(Distance-1-TowerOpponent->getUnpavedDistance()>=speed)
		DecrementDist();
}

void Healer::Attack(){
	if ((int)(TimeStep - TimeArrival) % ((int)RLD + 1) == 0){
		setHealthHeal(FirePower);
		TowerOpponent->HealEnemies(N);
	}
}

void Healer::Heal(){
	//NOTHING, Healer can't heal other Healers
}
