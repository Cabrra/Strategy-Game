#pragma once

#include "Game.h"

void Game::Show(){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 25, 0 };
	system("cls");

	for (int i = 0; i < 6; i++){
		cout << " _  _  _  _  _  _\n";
		for (int j = 0; j < 6; j++){
			cout << "|" << gameBoard[i][j] << "|";
		}
		cout << "\n";
	}
	cout << "_  _  _  _  _  _";
	SetConsoleCursorPosition(out, position);
	cout << "Turn Order";
	position.Y++;
	for (int i = 0; i < 6; i++){
		SetConsoleCursorPosition(out, position);
		if (Players[turnOrder[i]].HP > 0){
			cout << Players[turnOrder[i]].name;
			position.Y++;
		}
		if (current == i)
			cout << " <--";
	}

	position = { 0, 15 };
	SetConsoleCursorPosition(out, position);

	cout << "P1: " << Players[0].name << ": " << Players[0].HP << "/20, " << Players[1].name << ": " << Players[1].HP << "/20, " << Players[2].name << ": " << Players[2].HP << "/20\n";
	cout << "P2: " << Players[3].name << ": " << Players[3].HP << "/20, " << Players[4].name << ": " << Players[4].HP << "/20, " << Players[5].name << ": " << Players[5].HP << "/20\n\n";
}

void Game::Initialize(){

	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			gameBoard[i][j] = ' ';
		}
	}
	//player 1
	//archer 0
	Players[0].classType = 'A';
	Players[0].HP = 20;
	Players[0].name = 'A';
	Players[0].posX = 0;
	Players[0].posY = 0;
	Players[0].team = 1;

	gameBoard[0][0] = Players[0].name;

	//warrior 1
	Players[1].classType = 'W';
	Players[1].HP = 20;
	Players[1].name = 'W';
	Players[1].posX = 0;
	Players[1].posY = 1;
	Players[1].team = 1;

	gameBoard[0][1] = Players[1].name;

	//sorcerer 2
	Players[2].classType = 'S';
	Players[2].HP = 20;
	Players[2].name = 'S';
	Players[2].posX = 1;
	Players[2].posY = 0;
	Players[2].team = 1;

	gameBoard[1][0] = Players[2].name;

	//player 2
	//archer 3
	Players[3].classType = 'A';
	Players[3].HP = 20;
	Players[3].name = 'a';
	Players[3].posX = 5;
	Players[3].posY = 5;
	Players[3].team = 2;

	gameBoard[5][5] = Players[3].name;

	//warrior 4
	Players[4].classType = 'W';
	Players[4].HP = 20;
	Players[4].name = 'w';
	Players[4].posX = 5;
	Players[4].posY = 4;
	Players[4].team = 2;

	gameBoard[5][4] = Players[4].name;

	//sorcerer 5
	Players[5].classType = 'S';
	Players[5].HP = 20;
	Players[5].name = 's';
	Players[5].posX = 4;
	Players[5].posY = 5;
	Players[5].team = 2;

	gameBoard[4][5] = Players[5].name;

	// ESCAPE
	Players[6].classType = 'E';
	Players[6].HP = 20;
	Players[6].name = 'E';
	Players[6].posX = 0;
	Players[6].posY = 0;
	Players[6].team = 0;

}

bool Game::Move(character &c, int x, int y){

	if (x == -10 && y == -10)
		return false;

	int newX, newY;
	newX = c.posX + x;
	newY = c.posY + y;

	if (x == 0 && y == 0)
		return true;
	if (newX >= 0 && newX < 6 && newY >= 0 && newY < 6 && gameBoard[newX][newY] == ' '){
		gameBoard[c.posX][c.posY] = ' ';
		c.posX = newX;
		c.posY = newY;

		gameBoard[c.posX][c.posY] = c.name;
		return true;
	}
	else{
		return false;
	}
}

bool Game::evaluateMove(character c, int x, int y){
	int newX, newY;
	newX = c.posX + x;
	newY = c.posY + y;
	if (x == 0 && y == 0)
		return true;
	if (newX >= 0 && newX < 6 && newY >= 0 && newY < 6 && gameBoard[newX][newY] == ' ')
		return true;
	else
		return false;
}

int Game::CheckMove(character c){

	// -1 . dead    0. No moves    1. there is moves

	if (c.HP <= 0){
		current++;
		return -1;
	}
	if ((c.posX - 1) >= 0 && gameBoard[c.posX - 1][c.posY] == ' ') // Left
		return 1;
	if ((c.posY - 1) >= 0 && gameBoard[c.posX][c.posY - 1] == ' ') // Up
		return 1;
	if ((c.posX + 1) < 6 && gameBoard[c.posX + 1][c.posY] == ' ') // right
		return 1;
	if ((c.posY + 1) < 6 && gameBoard[c.posX][c.posY + 1] == ' ') // down
		return 1;

	return 0;
}

int Game::CheckRange(character c){

	int distance;

	switch (c.classType){
	case 'A':
	{
				for (int i = 0; i < 6; i++){
					if (c.name != Players[i].name){
						distance = abs(Players[i].posX - c.posX) + abs(Players[i].posY - c.posY);
						if (distance <= 4 && Players[i].team != c.team && Players[i].HP > 0)
							return 1;
					}
				}
				current++;
				return 0;
				break;
	}
	case 'W':
	{
				for (int i = 0; i < 6; i++){
					if (c.name != Players[i].name){
						distance = abs(Players[i].posX - c.posX) + abs(Players[i].posY - c.posY);
						if (distance == 1 && Players[i].team != c.team && Players[i].HP > 0)
							return 1;
					}
				}
				current++;
				return 0;
				break;
	}
	case 'S':
	{
				for (int i = 0; i < 6; i++){
					if (c.name != Players[i].name){
						distance = abs(Players[i].posX - c.posX) + abs(Players[i].posY - c.posY);
						if (distance <= 2 && Players[i].team != c.team && Players[i].HP > 0)
							return 1;
					}
				}
				current++;
				return 0;
				break;
	}
	}
	return 0;
}

bool Game::evaluateAttack(character atk, character target){
	int distance;

	if (atk.name != target.name && atk.team != target.team && target.HP > 0){

		switch (atk.classType){
		case 'A':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance <= 4){
						return true;
					}
		}
		case 'W':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance == 1){
						return true;
					}
		}
		case 'S':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance <= 2){
						return true;
					}

		}
		}
	}
	return false;
}


bool Game::Attack(character atk, character &target){

	int distance;
	if (target.classType == 'E'){
		current++;
		return true;
	}

	if (atk.name != target.name && atk.team != target.team && target.HP > 0){

		switch (atk.classType){
		case 'A':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance <= 4){
						int damage = (rand() % 6) + 2;
						if (damage == 7){
							damage += 2;
							cout << "CRITICAL!! dealed " << damage << " damage (+2 critical)...\n";
							Sleep(900);
						}
						else{
							cout << "Dealed " << damage << " damage...\n";
							Sleep(900);
						}
						target.HP -= damage;
						if (target.HP <= 0){
							target.HP = 0;
							if (target.team == 1)
								gameBoard[target.posX][target.posY] = 'D';
							else
								gameBoard[target.posX][target.posY]=  'd';

							cout << "KILLING THE ENEMY!!...\n";
							Sleep(900);
						}
						current++;;

						return true;
					}

					break;
		}
		case 'W':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance == 1){
						int damage = (rand() % 8) + 7;
						if (damage == 14){
							damage += 2;
							cout << "CRITICAL!! dealed " << damage << " damage (+2 critical)...\n";
							Sleep(900);
						}
						else{
							cout << "Dealed " << damage << " damage...\n";
							Sleep(900);
						}
						target.HP -= damage;
						if (target.HP <= 0){
							target.HP = 0;
							if (target.team == 1)
								gameBoard[target.posX][target.posY] = 'D';
							else
								gameBoard[target.posX][target.posY] = 'd';

							cout << "KILLING THE ENEMY!!...\n";
							Sleep(900);
						}
						current++;
						return true;
					}

					break;
		}
		case 'S':
		{
					distance = abs(target.posX - atk.posX) + abs(target.posY - atk.posY);
					if (distance <= 2){
						int damage = (rand() % 10) + 1;
						if (damage == 10){
							damage += 2;
							cout << "CRITICAL!! dealed " << damage << " damage (+2 critical)...\n";
							Sleep(900);
						}
						else{
							cout << "Dealed " << damage << " damage...\n";
							Sleep(900);
						}
						target.HP -= damage;
						if (target.HP <= 0){
							target.HP = 0;
							if (target.team == 1)
								gameBoard[target.posX][target.posY] = 'D';
							else
								gameBoard[target.posX][target.posY] = 'd';

							cout << "KILLING THE ENEMY!!...\n";
							Sleep(900);
						}
						current++;
						return true;
					}

					break;
		}
		}
	}
	return false;
}

void Game::GenerateTurn(){
	int aux[6] = { 1, 2, 3, 4, 5, 6 };
	int turn;

	for (int i = 0; i < 6; i++){
		do{
			turn = rand() % 6;
			turnOrder[i] = turn;
		} while (aux[turn] == 0);
		aux[turn] = 0;
	}
	current = 0;
}

int Game::EndGame(){
	short countA = 3;
	short countB = 3;

	for (int i = 0; i < 3; i++){
		if (Players[i].HP == 0)
			countA--;
	}

	if (countA == 0)
		return 2; // team 2 won

	for (int i = 3; i < 6; i++){
		if (Players[i].HP == 0)
			countB--;
	}

	if (countB == 0)
		return 1; // team 1 won

	return 0;
}

bool Game::isDead(character c) {

	if (c.HP <= 0){
		current++;
		return true;
	}
	else{
		return	false;
	}
}