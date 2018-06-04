#pragma once
#include "../Defs.h";
#include "../Enemies/ShieldedFighter.h"
#include "../Enemies/Fighter.h"
#include "../ADT/LinkedList.h";


class Tower
{
	//Health of tower
	double Health;

	//region of tower
	REGION region;

	//Points to the next NOT DESTROYED tower
	Tower *nextTower;

	//check if destroyed or not false if not
	bool destroyed;

	//number of enemies hit at a time step
	int MaxNToHit;

	//Fire Power of the hit
	double FirePower;
	
	//enemies in this region
	LinkedList enemies;

	//High-Priority enemies
	LinkedList ShieldedEnemies;
	int ShieldedCount;

	//number of unpaved steps
	//to be decreased later when Pavers pave
	int unpaved;

	//number of Active enemies in the tower's region
	int numActive;
	//number of killed enemies in the tower's region
	int numKilled;


public:
	Tower();	//default consstructor (needed)

	//setters
	void SetHealth(double h);
	void SetRegion(REGION R);
	void setFirePower(double pow);
	void setN(int num);
	void setNextTower(Tower * nxt);

	//getters
	double GetHealth() const;
	int getShieldedCount() const;
	double getFirePower() const;
	REGION getRegion() const ;
	Tower* getNextTower() const ;
	int getUnpavedDistance() const ;

	//Handling Enemies ADT in Tower
	void AddEnemy(Enemy * enemy);
	void RemoveEnemy(Enemy* enemy);

	//To be removed after phase I, I just implemeneted it to sort the shielded enemies list from Battle now
	//Later, I will probably make the sorting happen in each timeStep as the priority of Shielded enemies change
	void SortShielded();

	//Get info of tower and enemies in this region
	string getStringInfo() const ;

	//Attacks the enemies according to their priority
	void AttackEnemies() ;

	//Called when an Enemy attacks a Tower
	void DecrementHealth(double Damage);

	//Called when a paver paves
	void DecrementunPavedDist(double Pv);

	bool isDestroyed() const ;

	//When Tower is destroyed this function is used to transport
	//the enemies of this tower to the next not-destroyed tower
	bool TransportData();

	//Used when a Healer is healing enemies in a specific region
	void HealEnemies(int n); //n is the number of enemies to heal
};


