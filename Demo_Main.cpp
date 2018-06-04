#include "Battle.h"
#include "GUI\GUI.h"

int TimeStep;
void main(){
	//Demo

	Battle* pGameBattle = new Battle;

	GUI * pGUI = new GUI;

	pGUI->PrintMessage("This is Phase II simulator. Please load a file to get started");
	MENUITEM CurrentItem = MENU_ITM_COUNT;

	bool done = false;

	do{
		CurrentItem = pGUI->GetUserAction();
		switch(CurrentItem){
		case MENU_LOAD:
			pGUI->PrintMessage("Please enter name of the file to be loade");
			Sleep(1000);
			pGUI->ClearStatusBar();
			done = pGameBattle->Load(pGUI);
			pGUI->PrintMessage("Now select one of the three modes");
			break;

		case MENU_EXIT:
			break;

		case StepByStep_Mode:
			if(!done)
				pGUI->PrintMessage("Cant Start Simulation , Pleas load File First ");
			else {
				pGameBattle->Simulate(pGUI,CurrentItem);
				pGUI->PrintMessage("Game Ended! Click anywhere to close.");
				pGUI->GetUserAction();
				return;
			}
			break;

		case InterActive_Mode:
			if(!done)
				pGUI->PrintMessage("Cant Start Simulation , Pleas load File First ");
			else {
				pGameBattle->Simulate(pGUI,CurrentItem);
				pGUI->PrintMessage("Game Ended! Click anywhere to close.");
				pGUI->GetUserAction();
				return;
			}
			break;

		case Silent_Mode:
			if(!done)
				pGUI->PrintMessage("Cant Start Simulation , Pleas load File First ");
			else {
				pGameBattle->Simulate(pGUI,CurrentItem);
				pGUI->PrintMessage("Game Ended! Click anywhere to close.");
				pGUI->GetUserAction();
				return;
			}
			break;


		default:
			break;
		}
	} while (CurrentItem != MENU_EXIT);
	
	
}


