// leaks

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <ctime>
#include <windows.h>
#include "Game.h"

void Tittle();

int main(int argc, char ** argv)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(static_cast<unsigned int>(time(nullptr)));
	////////////////////////////////////////////////////////////////////////////////////////////////
	// LEAK DETECTION
	////////////////////////////////////////////////////////////////////////////////////////////////
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
	//_CrtSetBreakAlloc();

	Game battle;
	bool bRunning = true;
	bool endGame = false;

	int winner;
	int* turns;
	character *Players;
	//char gameBoard[6][6];

	Tittle();

	while (!endGame){

		battle.GenerateTurn();
		turns = battle.GetTurns();
		battle.Initialize();
		Players = battle.GetPlayers();
		while (bRunning){

			battle.Show();
			for (int i = 0; i < 6; i++){
				winner = battle.EndGame();
				if (winner != 0){
					bRunning = false;
					break;
				}
				if (battle.isDead(Players[turns[i]]))
					continue;
				if (battle.CheckMove(Players[turns[i]]) == 1){
					int x = -10;
					int y = -10;


					cout << "Use arrows to move and ESC to skip movement\n";
					do {
						bool valid = false;
						if (_kbhit()){
							if (GetAsyncKeyState(VK_UP) & 0x8000){
								x = -1;
								y = 0;
								valid = true;
							}
							if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
								x = 0;
								y = +1;
								valid = true;
							}
							if (GetAsyncKeyState(VK_DOWN) & 0x8000){
								x = +1;
								y = 0;
								valid = true;
							}

							if (GetAsyncKeyState(VK_LEFT) & 0x8000){
								x = 0;
								y = -1;
								valid = true;
							}
							if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){
								x = 0;
								y = 0;
								valid = true;
							}


							if (!battle.evaluateMove(Players[turns[i]], x, y) && valid){
								cout << "Can't move there...\n";
								Sleep(900);
								LockWindowUpdate(GetConsoleWindow());
								system("cls");

								battle.Show();
								cout << "Use arrows to move and ESC to skip movement\n";
								LockWindowUpdate(NULL);
								Sleep(10);

								x = -10;
								y = -10;
								valid = false;
							}
						}

					} while (!battle.Move(Players[turns[i]], x, y));
				}
				else{

					cout << "you can't move...\n";
					Sleep(900);
				}

				LockWindowUpdate(GetConsoleWindow());
				system("cls");

				battle.Show();
				LockWindowUpdate(NULL);
				Sleep(10);

				if (battle.CheckRange(Players[turns[i]]) == 1){
					character *a = &Players[turns[i]];

					cout << "1 = A || 2 = W || 3 = S || 4 = a || 5 = w || 6 = s...\n";
					cout << "or use keys aws (AWS) jkl(aws)... Or Esc to skip\n";

					do {
						bool valid = false;
						if (_kbhit()){
							if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('1') & 0x8000)){
								a = &Players[0];
								valid = true;
							}
							if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('2') & 0x8000)){
								a = &Players[1];
								valid = true;
							}
							if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState('3') & 0x8000)){
								a = &Players[2];
								valid = true;
							}
							if ((GetAsyncKeyState('J') & 0x8000) || (GetAsyncKeyState('4') & 0x8000)){
								a = &Players[3];
								valid = true;
							}
							if ((GetAsyncKeyState('K') & 0x8000) || (GetAsyncKeyState('5') & 0x8000)){
								a = &Players[4];
								valid = true;
							}
							if ((GetAsyncKeyState('L') & 0x8000) || (GetAsyncKeyState('6') & 0x8000)){
								a = &Players[5];
								valid = true;
							}
							if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){
								a = &Players[6];
								valid = true;
							}
								

							if (!battle.evaluateAttack(Players[turns[i]], *a) && valid && a->classType != 'E'){
								cout << "Target out of range...\n";
								Sleep(900);
								LockWindowUpdate(GetConsoleWindow());
								system("cls");

								battle.Show();
								cout << "1 = A || 2= W || 3= S || 4 = a || 5 = w || 6 = s...\n";
								cout << "or use keys aws (AWS) jkl(aws)... Or Esc to skip\n";
								LockWindowUpdate(NULL);
								Sleep(10);
								valid = false;
							}
						}

					} while (!battle.Attack(Players[turns[i]], *a));
				}
				else{

					cout << "You can't attack...\n";
					Sleep(900);
				}

				LockWindowUpdate(GetConsoleWindow());
				system("cls");

				battle.Show();
				LockWindowUpdate(NULL);
				Sleep(10);
				winner = battle.EndGame();
				if (winner != 0){
					bRunning = false;
					break;
				}
			}


			battle.GenerateTurn();
			turns = battle.GetTurns();

		}
		system("cls");

		cout << "The battle is over... PLAYER " << winner << " WON!!\n\n";

		cout << "Do you want to play again? <Y>es/<N>o ";
		while (true){
			char ch = _getch();

			if (ch == 'Y' || ch == 'y'){
				endGame = false;
				bRunning = true;
				break;
			}
			if (ch == 'N' || ch == 'n'){
				endGame = true;
				break;
			}
		}

	}

	system("cls");
	cout << "YOU BROUGHT SHAME TO MY DOJO.... \n\n...just kidding, have a nice day (: \n\n";

	system("pause");

	return 0;
}

void Tittle(){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << " ____     ______  ______  ______  __       ____      \n";
	cout << "/\\  _`\\  /\\  _  \\/\\__  _\\/\\__  _\\/\\ \\     /\\  _`\\ \n";
	cout << "\\ \\ \\L\\ \\\\ \\ \\L\\ \\/_/\\ \\/\\/_/\\ \\/\\ \\ \\    \\ \\ \\L\\_\\  \n";
	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << " \\ \\  _ <'\\ \\  __ \\ \\ \\ \\   \\ \\ \\ \\ \\ \\  __\\ \\  _\\L  \n";
	cout << "  \\ \\ \\L\\ \\\\ \\ \\/\\ \\ \\ \\ \\   \\ \\ \\ \\ \\ \\L\\ \\\\ \\ \\L\\ \\\n";
	cout << "   \\ \\____/ \\ \\_\\ \\_\\ \\ \\_\\   \\ \\_\\ \\ \\____/ \\ \\____/\n";
	SetConsoleTextAttribute(out, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "    \\/___/   \\/_/\\/_/  \\/_/    \\/_/  \\/___/   \\/___/ \n\n";

	cout << "                  __       _____   ____    ____    ____     \n";
	cout << "                 /\\ \\     /\\  __`\\/\\  _`\\ /\\  _`\\ /\\  _`\\     \n";
	SetConsoleTextAttribute(out, FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "                 \\ \\ \\    \\ \\ \\/\\ \\ \\ \\L\\ \\ \\ \\/\\ \\ \\,\\L\\_\\   \n";
	cout << "                  \\ \\ \\  __\\ \\ \\ \\ \\ \\ ,  /\\ \\ \\ \\ \\/_\\__ \\   \n";
	cout << "                   \\ \\ \\L\\ \\\\ \\ \\_\\ \\ \\ \\\\ \\\\ \\ \\_\\ \\/\\ \\L\\ \\ \n";
	SetConsoleTextAttribute(out, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "                    \\ \\____/ \\ \\_____\\ \\_\\ \\_\\ \\____/\\ `\\____\\ \n";
	cout << "                     \\/___/   \\/_____/\\/_/\\/ /\\/___/  \\/_____/ \n\n";

	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "Welcome to the epic battles!!\nTwo teams fighting in a extreme deathmatch...\n";
	cout << "Lead your team to victory and get the absolut glory...\n";

	SetConsoleTextAttribute(out, FOREGROUND_RED);
	cout << "Only the strongests survive...\n\n";

	SetConsoleTextAttribute(out, 0 | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("pause");
}