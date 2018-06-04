#pragma once

#include "ADT\Queue.h"
#include "GUI\GUI.h"
#include "Castle\Castle.h"

//Enemies
#include"Enemies\Fighter.h"
#include"Enemies\Paver.h"
#include "Enemies\ShieldedFighter.h"
#include "Enemies\Healer.h"
#include "Enemies\Dragon.h"
#include<fstream>



// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;							//the actual number of Active enemies in the game

	LinkedQueue BInactiveEnemies;			//A Queue that store all enemies loaded, from which we take one by one
											//depending on the enemy's time stamp and move it to the array of pointers
											//and list of enemies in 4 regions

	Enemy* BActiveEnemies[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	LinkedList KilledEnemies;				//It's filled and deleted at ONE Time Step
											//NOT FOR STORAGE!!
	ofstream OutFile;                       //OutPut file object 
	int TotalKD;                            // Total Kill Delay For All Killed Enemies
 	int TotalFD;                            // Total First Shot Delay For All Killed Enemies

	
	int DeathCount;							// added with the ( -1 ) in the constructor
	string FileName;						//name of loaded file, to be saved to use in output file
	
public:
	
	Battle();

	//Read input file
	bool Load(GUI * pGUI);

	//This function only adds the pointer
	//to the list of ACTIVE Enemies in Battle
	void AddEnemy(Enemy* Ptr);

	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();

	void DrawUnPavedDis(GUI * pGUI);
	void Moving();
	
	//Simulate function for Phase I
	void Simulate(GUI * pGUI,MENUITEM&);

	//Delete an Enemy completely
	void DeleteKilledEnemies();

	//Fight between all Active enemies and Tower
	void Fight() ;
	//Print The Statistic of The Battle 
	void Print(bool) ;

};