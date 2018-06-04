#include "Castle.h"

Castle::Castle()
{
	Towers[0].SetRegion(A_REG);
	Towers[0].setNextTower(&Towers[1]);

	Towers[1].SetRegion(B_REG);
	Towers[1].setNextTower(&Towers[2]);

	Towers[2].SetRegion(C_REG);
	Towers[2].setNextTower(&Towers[3]);

	Towers[3].SetRegion(D_REG);
	Towers[3].setNextTower(&Towers[0]);
}

void Castle::SetTowersHealth(double h)
{
	Health=h;
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}

void Castle::SetMaxEnemies(int num){
	//if num is invalid set N to 2 as a default value
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setN(num);
	}
	
}


void Castle::SetTowerFirePower(double pow){
	//if power is invalid set FirePower to 10 as a default value
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setFirePower(pow);
	}
	
}

void Castle::AddEnemy(Enemy * en){
	REGION r = en->GetRegion();
	switch (r){
	case A_REG:
		Towers[0].AddEnemy(en);
		break;
	case B_REG:
		Towers[1].AddEnemy(en);
		break;
	case C_REG:
		Towers[2].AddEnemy(en);
		break;
	case D_REG:
		Towers[3].AddEnemy(en);
		break;
	default:
		break;
	}
}
void Castle::RemoveEnemy(Enemy * en){
	REGION r = en->GetRegion();
	switch (r){
	case A_REG:
		Towers[0].RemoveEnemy(en);
		break;
	case B_REG:
		Towers[1].RemoveEnemy(en);
		break;
	case C_REG:
		Towers[2].RemoveEnemy(en);
		break;
	case D_REG:
		Towers[3].RemoveEnemy(en);
		break;
	default:
		break;
	}
}
string Castle::GetInfoOfTower(int r) const
{
	if (r<NoOfRegions)
		return Towers[r].getStringInfo();
	return "ERROR";
}

//Sorting shielded enemies in towers
void Castle::SortShEnemiesInTowers(){
	for (int i = 0; i<NoOfRegions; i++)
		if (Towers[i].getShieldedCount() > 1)
			Towers[i].SortShielded();
}

void Castle::AttackEnemies() {
	for (int i = 0; i<NoOfRegions; i++)
		if (!Towers[i].isDestroyed())
			Towers[i].AttackEnemies();
}


void Castle::OrganizeTowers() {
	if (isDestroyed()) return;

	for (int i = 0; i<NoOfRegions; i++){
		if (Towers[i].isDestroyed()){
			Towers[i].TransportData();
			/*
			//lw l2et Tower mdmr hn2l l data bta3to le l Tower l b3do
			//loop 3la mn b3d l tower da le l a5r
			for (int j = i+1; j<NoOfRegions; j++)
				if (!Towers[j].isDestroyed()){ //if not destoryed
					Towers[i].TransportData(&Towers[j]);
					noTowers = false;
					break;
				}

			if (noTowers) //y3ni ml2t4 Tower a3mlo transportTo lsa fa ha-loop mn l awl le i
				//loop mn l awl le l tower l mdmr
				for (int j = 0; j<i; j++)
					if (!Towers[j].isDestroyed()){
					Towers[i].TransportData(&Towers[j]);
					noTowers = false;
					break;
				}*/
		}
	}

}

bool Castle::isDestroyed() const {
	int Destroyed = 0;
	for (int i = 0; i<NoOfRegions; i++)
		if (Towers[i].isDestroyed())
			Destroyed++;

	return Destroyed == NoOfRegions;
}
double*  Castle:: GetTotalDamge() const 
{
	double* arr=new double [NoOfRegions];
	for (int i = 0; i<NoOfRegions; i++)
	{
		arr[i]=Health-Towers[i].GetHealth();
	}
	return arr;
	
}
int *  Castle:: GetUnpaved() const 
{
	int * arr=new int[NoOfRegions];
	for (int i = 0; i<NoOfRegions; i++)
	{
		arr[i]=Towers[i].getUnpavedDistance();
	}
	return arr;
	
}