#include "Tower.h"
//PUBLIC FUNCTION
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

//Global Function to decrement health of enemy passed to it, used in Traverse, when Tower attacks
void Hit(Enemy * en){
	en->DecrementHealth();
}

//Global Function to change the info (region and Tower pointer) of enemy passed to it, used in Traverse
void ChangeEnemiesData(Enemy* en){
	en->ChangeInfo();
}

void HealEnemy(Enemy * en){
	en->Heal();
}


Tower::Tower(){
	Health = 0;
	destroyed = false;
	unpaved = 30;
	ShieldedCount = 0;
	numActive=0;
	numKilled=0;
	MaxNToHit = 2;
	FirePower = 10;
}

void Tower::SetRegion(REGION R)
{
	region=R;
}

void Tower::setFirePower(double pow){
	FirePower = (pow>0)? pow: 10;
}

void Tower::setN(int num){
	MaxNToHit = (num>0)? num : 2;
}

void Tower::setNextTower(Tower * nxt){
	nextTower = nxt;
}


string Tower::getStringInfo()const
{
	string R;

	switch (region){

	case A_REG:
		R="A";
		break;

	case B_REG:
		R="B";
		break;

	case C_REG:
		R="C";
		break;

	case D_REG:
		R="D";
		break;

	default:
		break;
	}

	string s = "Tower "+R+" Health = "+ to_string(Health)+" Active enemies number = "+to_string(numActive)+" killed enemies number = "+to_string(numKilled) + "Unpaved distance = " + to_string(unpaved);

	return s;
}

void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const {
	return Health;
}

int Tower::getShieldedCount() const {
	return ShieldedCount;
}

double Tower::getFirePower() const {
	return FirePower;
}

REGION Tower::getRegion() const {
	return region;
}

Tower* Tower::getNextTower() const {
	return nextTower;
}

int Tower::getUnpavedDistance() const {
	return unpaved;
}


void Tower::AddEnemy(Enemy * enemy)
{
	numActive++;
	//if Shielded
	if (dynamic_cast<ShieldedFighter*>(enemy)){
		ShieldedEnemies.add(enemy);
		ShieldedCount++;
	}
	else
		enemies.add(enemy);
	
	enemy->setTower(this);
}

void Tower::RemoveEnemy(Enemy * enemy)
{
	numKilled++;
	numActive--;

	//if shielded
	if (dynamic_cast<ShieldedFighter*>(enemy)){
		ShieldedEnemies.remove(enemy);
		ShieldedCount--;
	}
	else
		enemies.remove(enemy);
}



void Tower::SortShielded(){
	if (!ShieldedEnemies.isEmpty())
		ShieldedEnemies.sort();
}

void Tower::AttackEnemies() {
	if (MaxNToHit > ShieldedCount){
		ShieldedEnemies.TraverseHeadFirst(Hit, ShieldedCount);
		int remindedEnemies = MaxNToHit - ShieldedCount;
		enemies.TraverseHeadFirst(Hit, remindedEnemies);
	}
	else {
		ShieldedEnemies.TraverseHeadFirst(Hit, MaxNToHit);
	}
}

void Tower::DecrementHealth(double Damage){
	if (isDestroyed()) return;

	Health -= Damage;

	//Destory Tower
	if (Health <= 0){
		Health = 0;
		destroyed = true;
		PlaySound("TowerDestroyed.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);

		//Handle NextTower pointer
		Tower * tempNext = nextTower;

		while (tempNext && tempNext->getNextTower() != this)  //To reach the Tower whose next is this tower
			tempNext = tempNext->getNextTower();

		if (!tempNext) return;	//if no Towers left

		tempNext->setNextTower(nextTower);

		if (tempNext->getNextTower() == tempNext) //last Tower
			tempNext->setNextTower(nullptr);
	}

}

void Tower::DecrementunPavedDist(double Pv)
{
	unpaved -= Pv;

	if (unpaved >= 2)
	PlaySound("Paving.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	
	if(unpaved<MinDistance)
		unpaved=MinDistance;
}

bool Tower::isDestroyed() const {
	return destroyed;
}


bool Tower::TransportData(){
	if (nextTower == nullptr)
		return false;

	enemies.TraverseHeadFirst(ChangeEnemiesData, numActive-ShieldedCount);
	ShieldedEnemies.TraverseHeadFirst(ChangeEnemiesData, ShieldedCount);

	if (!nextTower->isDestroyed()){
		nextTower->enemies.appendLinkedLists(&enemies);
		nextTower->ShieldedEnemies.appendLinkedLists(&ShieldedEnemies);
	

		nextTower->ShieldedCount += this->ShieldedCount;
		ShieldedCount = 0;
		nextTower->numActive += this->numActive;
		numActive = 0;
	}

	return true;
}

void Tower::HealEnemies(int n){
	enemies.TraverseHeadFirst(HealEnemy, n);
	int EnemiesCount = numActive - ShieldedCount;
	if (n - EnemiesCount > 0)
		ShieldedEnemies.TraverseHeadFirst(HealEnemy, n-EnemiesCount);
}

