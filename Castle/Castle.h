#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"
class GUI;

class Castle
{
	Tower Towers[NoOfRegions];

	//number of enemies that a tower can hit at a time-stamp
	int N;

	//fire power of towers
	double FirePower;
	//Health Of Tower
	double Health;
	
public:
	Castle();

	//setters
	void SetTowersHealth(double h);
	void SetMaxEnemies(int num);
	void SetTowerFirePower(double pow);

	//handling ADT's
	void AddEnemy(Enemy * en);
	void RemoveEnemy(Enemy* en);

	//Getting info of tower #r
	string GetInfoOfTower(int r) const ;
	//returns array of total damged on towers 
	double* GetTotalDamge() const ;
	//returns array of total unpaved distance towers 
	int * GetUnpaved() const ;

	//This function is temporary to be used in simulator phase I only to be able to sort Shielded Enemies in Towers
	//through simulator function in Battle
	void SortShEnemiesInTowers(); //Sorting shielded enemies in towers
	
	//makes every Tower attack its enemies
	void AttackEnemies() ;

	//this function loops on towers, if it found a destroyed tower,
	//if transports its data to the next
	void OrganizeTowers() ;

	//returns True if the WHOLE CASTLE is destroyed
	bool isDestroyed() const ;
};
