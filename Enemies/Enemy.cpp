#pragma once
#include "Enemy.h"
#include "..\Castle\Tower.h"
#include "Dragon.h"
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

double Enemy::HealthHeal = 0;
int Enemy::Sequence = 0;

Enemy::Enemy(int id, EnemyType type,double arrTime,double heal,double firepow,double reloadper, color r_c,char r_region, int sp,int d )
{
	Clr = r_c;

	if(r_region=='A')
		Region=A_REG;
	else if(r_region=='B')
		Region=B_REG;
	else if(r_region=='C')
		Region=C_REG;
	else
		Region=D_REG;

	SetDistance(d);
	ID=id;
	TYP=type;
	TimeArrival=arrTime;
	Health=heal;
	FirePower=firepow;
	RLD=reloadper;
	speed=sp;
	State=INACTIVE;

	FirstShoot = 0;
	TimeKilled = 0;
}

///////////////////Setters/////////////////////
void Enemy::SetState()
{
	if(Health<=0)
		State=KILLED;
	else
		State=ACTIVE;
}

void Enemy::SetHealth(int H)
{
	Health=H;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

void Enemy::setTower(Tower *t){
	TowerOpponent = t;
}

void Enemy::setHealthHeal(double HH){
	HealthHeal = HH;
}
void Enemy::IncrementSeq()
{
	++Sequence;
}


////////////////////Getters///////////////////
STATES Enemy::GetState() const
{
	return State;
}

int Enemy::getFD() const {
	return FD;
}

int Enemy::getKD() const
{
	return KD;

}

int Enemy::getLT() const
{
	return LT;
}

int Enemy::getSequence() {
	return Sequence;
}


int Enemy::GetTimeArrival() const
{
	return TimeArrival;
}

int Enemy::getKTS() const {
	return TimeKilled;
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

double Enemy::getPriority() const {
	return Priority;
}

int Enemy::GetDistance() const
{
	return Distance;
}

Tower* Enemy::getTower() const {
	return TowerOpponent;
}

double Enemy::getHealthHeal() const {
	return HealthHeal;
}



string Enemy::GetInfo() const { //All enemies have same basic info
	string s = "ID:" + to_string(ID) + " Health:" + to_string(Health) + " "; // + " Type:" + to_string(TYP) + " State:" + to_string(State);
	switch (TYP){
	case PAVER:
		s += "State: Paver";
		break;

	case SHIELDED_FIGHTER:
		s += "State: Shielded";
		break;

	case FIGHTER:
		s += "State: FIGHTER";
		break;
	default:
		break;
	}

	switch (State){
	case ACTIVE:
		s += "State: Active";
		break;

	case HIGH_PERIORITY:
		s += "State: HighPriorityActive";
		break;

	default:
		break;
	}

	return s;
}

void Enemy::DecrementDist(int t)
{
	if(t==0)
		if (Distance-speed > MinDistance+1)
			Distance=Distance-speed;
		else
			Distance = MinDistance+1;
	else
		if (Distance-t > MinDistance+1)
			Distance=Distance-t;
		else
			Distance = MinDistance+1;
}

void Enemy::DecrementHealth(){
	double damage = 1.0 / Distance * (TowerOpponent->getFirePower()) * K;

	if (State == KILLED)
		return;

	Health -= damage;

	if (FirstShoot == 0)
	{//Haven't been hit before
		FirstShoot = TimeStep;
		FD=FirstShoot-TimeArrival;
	}

	if (Health <= 0){
		State = KILLED;
		PlaySound("EnemyDie.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		Health = 0;
		TimeKilled = TimeStep;
		KD=TimeKilled-FirstShoot;
		LT=FD+KD;
	}

}

void Enemy::ChangeInfo() 
{
	//FIX DISTANCE LATER!!
	Tower * nxt = TowerOpponent->getNextTower();
	TowerOpponent = nxt;
	if (dynamic_cast<Dragon*>(this))
	{
		this->ResetFireHeatTime();
		dynamic_cast<Dragon*>(this)->ResetAttack();
	}
	if (nxt)
	{
		Region = nxt->getRegion();
		if(Distance<= nxt->getUnpavedDistance())
 			Distance=nxt->getUnpavedDistance()+1;

	}
}


bool Enemy::operator > (const Enemy & en) const
{
	if (State == KILLED){
		if (TimeKilled == en.TimeKilled)
			return FD > en.FD;
		else
			return TimeKilled > en.TimeKilled;
	}
	return Priority > en.Priority;

}
