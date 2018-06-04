#include "Battle.h"

#include<fstream>
#include<string>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")


Battle::Battle()
{
	EnemyCount = 0;
	TimeStep = 0;
	DeathCount=0;
	TotalFD=0;
	TotalKD=0;
	FileName = "";
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BActiveEnemies[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BActiveEnemies, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

bool Battle::Load(GUI * pGUI)
{
	ifstream input;
	FileName = pGUI->GetString();

	input.open(FileName + ".txt");

	double In, C1, C2, C3;
	int N, speed;
	double ArrTime, Health, EnemyFP, Reload_Period;
	int Type, EnemyNum;
	char Region;

	if(input.is_open())
	{
		input>>In;							//In is just any double in the file we want to read
		BCastle.SetTowersHealth(In);

		input>>N;							
		BCastle.SetMaxEnemies(N);          //Max number of enemies can be attacked by Towers (( Fn in Castle ))

		input>>In;
		BCastle.SetTowerFirePower(In);      //The Fire Power of Each Tower ((Fn in Castle))

		input>>C1>>C2>>C3;
		Enemy* temp;

		while(!input.eof())	//while file is open
		{	
			input>>EnemyNum;
			if (EnemyNum==-1)	//reached end of file
			{
				pGUI->PrintMessage("File Loaded Successfully.");
				input.close();
				return true;
			}

			input>>Type>>ArrTime>>Health>>EnemyFP>>Reload_Period>>Region>>speed;
			switch (Type)
			{
			case PAVER:
				temp = new Paver(EnemyNum, ArrTime,Health,EnemyFP,Reload_Period,Region,speed);
				BInactiveEnemies.enqueue(temp);
				break;

			case FIGHTER:
				temp = new Fighter(EnemyNum,ArrTime,Health,EnemyFP,Reload_Period,Region,speed);
				BInactiveEnemies.enqueue(temp);
				break;

			case SHIELDED_FIGHTER:	//shielded fighter's constructor take additional 3 constants; C1, C2, C3
				temp = new ShieldedFighter(EnemyNum, ArrTime,Health,EnemyFP,Reload_Period,Region, speed, C1, C2, C3);
				BInactiveEnemies.enqueue(temp);
				break;

			case HEALER:
				temp = new Healer(EnemyNum,ArrTime,Health,EnemyFP,Reload_Period,Region,speed);
				BInactiveEnemies.enqueue(temp);
				break;
			case DRAGON:
				temp = new Dragon(EnemyNum,ArrTime,Health,EnemyFP,Reload_Period,Region,speed);
				BInactiveEnemies.enqueue(temp);
				break;


			default:
				break;
			}
		}
	}
	else
	{
		pGUI->PrintMessage("File is not loaded Successfully, please check the file's name. ");
		return false;
	}
}

void Battle::Moving()
{
	for(int i=0;i<EnemyCount;i++)
		if(BActiveEnemies[i]->GetTimeArrival()!=TimeStep)
			BActiveEnemies[i]->Move();

}

void Battle::Fight() {
	BCastle.OrganizeTowers();

	if (BCastle.isDestroyed()) 
	{
		return;
	}
	for (int i = 0; i<EnemyCount; i++)
		if (BActiveEnemies[i]->GetState() != KILLED)
			BActiveEnemies[i]->Attack();

	BCastle.AttackEnemies();

	DeleteKilledEnemies();

}

void Battle::DrawUnPavedDis(GUI * pGUI)
{
	pGUI->DrawUnPavedDis(BCastle);
}

void Battle::Simulate(GUI * pGUI, MENUITEM & Act){

	OutFile.open(FileName + "Output.txt");
	OutFile<<"KTS\tS\tFD\tKD\tLT";
	OutFile<<"\n";
	Point p;
	MENUITEM tempMenuItem;
	while( (!BInactiveEnemies.isEmpty() || EnemyCount>0) && !BCastle.isDestroyed() )
	{
		if(Act==InterActive_Mode)
		{
			tempMenuItem = pGUI->GetUserAction();
			if(tempMenuItem==MENU_EXIT)
				return;
		}
		else if(Act==StepByStep_Mode)
			Sleep(1000);
		TimeStep++;
		while (BInactiveEnemies.peekFront()!=nullptr && BInactiveEnemies.peekFront()->GetTimeArrival() == TimeStep)
		{
			Enemy * en;
			if (BInactiveEnemies.dequeue(en))
			{
				PlaySound("EnemyArrival.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
				en->SetState();
				AddEnemy(en);
				BCastle.AddEnemy(en);
			}

		}
		BCastle.SortShEnemiesInTowers();
		Fight();
		Moving();

		if(Act!=Silent_Mode)
		{
			pGUI->ClearStatusBar();
			pGUI->ClearBattleArea();
			pGUI->DrawUnPavedDis(BCastle);
			pGUI->DrawCastle();
			DrawEnemies(pGUI);

			pGUI->PrintMessage("Time Step = " + to_string(TimeStep));
			for (int i = 0; i<4; i++){
				string s = BCastle.GetInfoOfTower(i);
				pGUI->PrintMessage(s, i+1);
			}
		}

	}
	if(BCastle.isDestroyed())
		PlaySound("EnemiesWin.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	else 
		PlaySound("CastleWins.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	
	Print(!BCastle.isDestroyed());

	Act=MENU_EXIT;

}

void Battle::DeleteKilledEnemies() {
	for (int i = 0; i<EnemyCount; i++){
		Enemy * en = BActiveEnemies[i];
		if (en->GetState() == KILLED){	
			DeathCount++;
			TotalFD+=en->getFD();
			TotalKD+=en->getKD();
			KilledEnemies.add(en);
			BActiveEnemies[i] = BActiveEnemies[EnemyCount-1];
			BActiveEnemies[EnemyCount-1] = nullptr;
			i--; EnemyCount--;
			BCastle.RemoveEnemy(en);	//remove enemy from its linked list in towers
		}
	}
	KilledEnemies.PrintAndClear(OutFile);
}
void Battle::Print(bool Won) 
{
	OutFile<<"\n";
	for(int i=1;i<=4;i++)
		OutFile<<"T"<<i<<"_Total_Damge"<<"\t";
	double* damges=BCastle.GetTotalDamge();
	OutFile<<"\n";
	OutFile<<"\n";
	for(int i=0;i<NoOfRegions;i++)
		OutFile<<damges[i]<<"\t\t";
	delete damges;
	OutFile<<"\n";
	OutFile<<"\n";
	for(int i=1;i<=4;i++)
		OutFile<<"R"<<i<<"_Unpaved_Dist"<<"\t";
	OutFile<<"\n";
	OutFile<<"\n";
	int * Unpaved=BCastle.GetUnpaved();
	for(int i=0;i<NoOfRegions;i++)
		OutFile<<Unpaved[i]<<"\t\t";
	OutFile<<"\n";
	OutFile<<"\n";
	delete Unpaved;
	if(Won)//means Castle Won ALl Enemies are dead
	{
		OutFile<<"Game is WIN \n";
		OutFile<<"Total Enemies \t="<<DeathCount<<"\n";
		OutFile<<"Average First-Shot Delay \t="<<1.0*TotalFD/DeathCount<<"\n";
		OutFile<<"Average Kill Delah \t="<<1.0*TotalKD/DeathCount<<"\n";
	}
	else
	{
		OutFile<<"Game is LOSS \n";
		OutFile<<"Killed Enemies \t="<<DeathCount<<"\n";
		OutFile<<"Number Of Alive Enemies \t="<<EnemyCount+BInactiveEnemies.GetSize()<<"\n";
		OutFile<<"Average First-Shot Delay \t="<<1.0*TotalFD/DeathCount<<"\n";
		OutFile<<"Average Kill Delay \t="<<1.0*TotalKD/DeathCount<<"\n";
	}
}