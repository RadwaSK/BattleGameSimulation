#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Tower;

// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{
	static double HealthHeal;	//continuosly changed, when a Healer is healing other enemies, he sets their HealthHeal with his firepower
								//made static beacuse all enemies would have that same changing value to increase their health by
	static int Sequence;		//sequence of enemy in output file

protected:
	int ID;                //Each enemy has a unique ID (sequence number)
	color Clr;	           //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;         //Region of this enemy
	Tower * TowerOpponent;		//The tower of this Region
	int Distance;	       //Horizontal distance between enemy & the tower of its region
	                       //Always positive (ranges from 2 to 60)
	
	double Health;         //Enemy health
	double FirePower;          //Enemy fire Power
	double RLD;            //Enemy reload period
	
	double TimeArrival;    //Enemy arrival time
	int FirstShoot;			//Time of first shoot on enemy by a tower
	int TimeKilled;			//Time when enemy is killed

	int FD;                //First Shot Delay
	int KD;                //Kill Delay
	int LT;                //Life Time =FD+KD
	double K;					//constant set by 2 for shielded and 1 for others
	
	EnemyType TYP;			//Enemy type
	STATES State;			//Active, Killed, or High Priority
	int speed;				// the speed of the enemy
	
	double Priority;		//I only need it in Shielded, so in others = 0
	
public:
	Enemy(int id, EnemyType type, double arrTime, double heal, double firepow, double reloadper, color , char r_region,int sp, int d = MaxDistance);
	
	//setters
	virtual void SetState();
	void SetHealth(int H);
	void SetDistance(int d);
	void setTower(Tower *t);
	void setHealthHeal(double HH);
	static void IncrementSeq();
	//getters
	color GetColor() const;
	REGION GetRegion() const;
	STATES GetState() const;
	int GetTimeArrival() const;	//Get The Arrival Time of Enemy
	int getKTS() const ;
	double getPriority() const;
	int getFD() const ;
	int getKD() const;
	int getLT() const;
	int GetDistance() const ;
	Tower* getTower() const ;
	double getHealthHeal() const ;
	static int getSequence();

	//Public functions
	void DecrementDist(int t=0);			//handles  the distance when moved
	bool operator > (const Enemy & en) const;		//operator overloading
	string GetInfo() const ;
	virtual void ResetFireHeatTime()=0;

	//functions called from Global functions in Tower.cpp
	void DecrementHealth();	//called when Tower attacks an enemy
	void ChangeInfo() ; //called when enemies are moved from a tower to another
	virtual void Heal() = 0;		//called when a healer is healing enemies

	// Virtual Functions: ----------------
	//virtual string GetInfo() const; //All enemies have same basic info, so not pure virtual function
	
	virtual void Move() = 0;	    //All enemies can move
	virtual void Attack() = 0;	   //All enemies can attack (attacking is paving or shooting)
	
};

