#include "Paver.h"
#include "..\Castle\Tower.h"


Paver::Paver( int id,double arrTime,double heal,double firepow,double reloadper, char r_region,int sp):Enemy(id,PAVER,arrTime,heal,firepow,reloadper,DARKBLUE,r_region,sp)
{
	Priority = arrTime;
	K = 1;
}
void Paver::ResetFireHeatTime()
{}

void Paver::Move()
{
	
	if (Distance-1 == TowerOpponent->getUnpavedDistance())
	{ 
		if ( int(TimeStep - TimeArrival ) % int(RLD+1) ==0)
			DecrementDist(FirePower);
	}
	else
	{
		
		if(int (TimeStep-TimeArrival)% int (RLD+1)==0)
			DecrementDist(FirePower);
		else if(Distance-1-TowerOpponent->getUnpavedDistance()>=speed)
			DecrementDist();
	}

}

void Paver::Attack()
{
	if (Distance-1 == TowerOpponent->getUnpavedDistance())
	{ //because if he is in an ALREADY-PAVED area, he shall do nothing
		if ( int(TimeStep - TimeArrival ) % int(RLD+1) ==0)
			TowerOpponent->DecrementunPavedDist(FirePower);
	}
	else 
	{
		if ( int(TimeStep - TimeArrival ) % int(RLD+1) ==0)
			if(Distance-1-TowerOpponent->getUnpavedDistance()<FirePower)
				TowerOpponent->DecrementunPavedDist(FirePower-(Distance-1-TowerOpponent->getUnpavedDistance()));
	}
}

void Paver::Heal(){
	if (State != KILLED)
		Health += getHealthHeal();
}