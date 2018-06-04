#include "Dragon.h"
#include "..\Castle\Tower.h"



Dragon::Dragon(int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp):Enemy(id,FIGHTER,arrTime,heal,firepow,reloadper, ALICEBLUE ,r_region,sp)
{
	Priority = arrTime;  /// make him more prior than Other Enemies but less than shieleded
	K = 0.25;
	MaxFireHeatTime=(FirePower-RLD)>0?(FirePower-RLD):(RLD - FirePower);  // To make Him deal Damge for the absolute of the ( Firepower - Reload Period ) time Steps
	if (MaxFireHeatTime == 0)											  // if 0 set to default 1 ..
		MaxFireHeatTime=1;												  // if it is more than the Reload Time make it less than Reload Time by 1.
	else if ( MaxFireHeatTime >= RLD )
		MaxFireHeatTime = RLD - 1;
	ResetFireHeatTime();
	ResetAttack();
}
void Dragon::ResetAttack()
{
	Attacked = false;
}


void Dragon::Move()
{
	if(Distance-1-TowerOpponent->getUnpavedDistance()>=speed)
		DecrementDist();
}
void Dragon::ResetFireHeatTime()
{
	FireHeatTime=0;
}


void Dragon::Attack()
{
	if ((int)(TimeStep - TimeArrival) % ((int)RLD + 1) == 0)
	{
		double Damage = FirePower/Distance * K;
		TowerOpponent->DecrementHealth(Damage);
		ResetFireHeatTime();
		Attacked = true;
	}
	else if ( FireHeatTime < MaxFireHeatTime && Attacked)					// TimeSteps he will deal Dmg to the Tower after he hit the Tower.
	{															
		double Damage = (FirePower/60.0 * K)/(FireHeatTime+1);//Distance			//it decreases with Time. " As fire decreases with time xD " bytaffohaa :) "
		TowerOpponent->DecrementHealth(Damage);
		FireHeatTime++;
	}
	else
		ResetAttack();
}
void Dragon::AttackAfterDeath()
{
	if ( FireHeatTime < MaxFireHeatTime && Attacked)						
	{															
		double Damage = (FirePower/Distance * K)/(FireHeatTime+1);
		TowerOpponent->DecrementHealth(Damage);
		FireHeatTime++;
	}
	else 
		ResetAttack();
}


void Dragon::Heal(){
	if (State != KILLED)
		Health += getHealthHeal();
}