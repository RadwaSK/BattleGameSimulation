#include"ShieldedFighter.h"
#include "..\Castle\Tower.h"


ShieldedFighter::ShieldedFighter(int id, double arrTime,double heal,double firepow,double reloadper, char r_region, int sp, double c1, double c2, double c3):Enemy(id,SHIELDED_FIGHTER,arrTime,heal,firepow,reloadper,ORANGERED,r_region,sp)
{
	C1 = c1; C2 = c2; C3 = c3;
	CalculatePeriorty();
	K = 2;
}

void ShieldedFighter::CalculatePeriorty()
{
	Priority = (FirePower/Distance)*C1+(C2/(RLD+1))+Health*C3;
}
void ShieldedFighter::ResetFireHeatTime()
{}
void ShieldedFighter::Move()
{
	if(Distance-1-TowerOpponent->getUnpavedDistance()>=speed)
		DecrementDist();
}
void ShieldedFighter::Attack()
{
	if ((int)(TimeStep - TimeArrival) % ((int)RLD + 1) == 0){
		double Damage = FirePower/Distance * K;
		TowerOpponent->DecrementHealth(Damage);
	}
}

void  ShieldedFighter::SetState()
{
	if(Health <= 0)
		State=KILLED;
	else
		State=HIGH_PERIORITY;
}

void ShieldedFighter::Heal(){
	if (State != KILLED)
		Health += getHealthHeal();
}
