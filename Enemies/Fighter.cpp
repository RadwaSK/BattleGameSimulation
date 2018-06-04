#include"Fighter.h"
#include "..\Castle\Tower.h"


Fighter::Fighter(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp):Enemy(id,FIGHTER,arrTime,heal,firepow,reloadper, DARKOLIVEGREEN ,r_region,sp)
{
	Priority = arrTime;
	K = 1;
}


void Fighter::Move()
{
	if(Distance-1-TowerOpponent->getUnpavedDistance()>=speed)
		DecrementDist();
}
void Fighter::ResetFireHeatTime()
{}

void Fighter::Attack()
{
	if ((int)(TimeStep - TimeArrival) % ((int)RLD + 1) == 0){
		double Damage = FirePower/Distance * K;
		TowerOpponent->DecrementHealth(Damage);
	}
}

void Fighter::Heal(){
	if (State != KILLED)
		Health += getHealthHeal();
}
