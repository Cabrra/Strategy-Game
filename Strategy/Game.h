// Game class
#pragma once
#include <stdlib.h> 
#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;



struct character{
	char classType;
	short posX;
	short posY;
	char name;
	int HP;
	short team;
};

class Game {

private:
	character Players[7];// 0-2 team one // 3-6 team two;
	int turnOrder[6];
	char gameBoard[6][6];
	int current;

public:

	int* GetTurns() { return turnOrder; }
	character * GetPlayers() { return Players; }

	void Show();
	void Initialize();
	int CheckMove(character c);
	int CheckRange(character c);
	bool Attack(character atk, character &target);
	bool Move(character &c, int x, int y);
	int EndGame();

	void GenerateTurn();
	bool evaluateMove(character c, int x, int y);
	bool evaluateAttack(character atk, character target);
	bool isDead(character c);
};