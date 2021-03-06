#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

void GenerateMap(std::vector<std::vector<std::string>> & board) {
	const int SIZE_BOARD = 3;
	for (int i = 0; i < SIZE_BOARD; i++) {
		std::vector<std::string> line;
		for (int j = 0; j < SIZE_BOARD; j++) {
			line.push_back("_");
		}
		board.push_back(line);
	}
}

void ShowMap(std::vector<std::vector<std::string>> board) {
	for (auto& line : board) {
		for (int i = 0; i < line.size(); i++) {
			std::cout << line[i] << ((i == line.size() - 1) ? "" : "|");
		}
		std::cout << std::endl;
	}
}

void SetNewPosition(std::vector<std::vector<std::string>> & board, std::string player) {
	//This code does not check if the entered position hasn't been chosen in the game
	//This code does not check if the number entered is between 1 and 3 (if not it ill crash so it should give you a hint)
	int row=0;
	int column=0;
	std::cout << "Player " << player<< " choose where you want to play." << std::endl << "at row (1-3): ";
	std::cin >> row;
	std::cout << "at column (1-3): ";
	std::cin >> column;
	board[row-1][column-1] = player;
}

bool CheckWin(std::vector<std::vector<std::string>> board, std::string player) {
	//diag1 and diag2 check if there is a diagonale that is completed
	int diag1 = 0;
	int diag2 = 0;
	bool tempWin = false;

	for (int i = 0; i < board.size(); i++) {
		//hori and verti check if there is an row or column that is completed
		int hori = 0;
		int verti = 0;
		for (int j = 0; j < board.size(); j++) {
			if (player.compare(board[i][j]) == 0) {
				hori++;
			}
			if (player.compare(board[j][i]) == 0) {
				verti++;
			}
		}
		if (hori == board.size() || verti == board.size()) {
			tempWin = true;
		}
		if (player.compare(board[i][i]) == 0) {
			diag1++;
		}
		if (player.compare(board[board.size() - 1 - i][i]) == 0) {
			diag2++;
		}
	}
	if (diag1 == board.size() || diag2 == board.size()) {
		tempWin = true;
	}
	return tempWin;
}

void PlayGame(std::vector<std::vector<std::string>> & board, std::string player) {
	ShowMap(board);
	SetNewPosition(board, player);
}

int main()
{
	std::vector<std::vector<std::string>> board;
	std::string player1 = "X";
	std::string player2 = "O";
	std::string currentPlayer;
	bool player1Active=false;
	bool gameEnded = false;

	GenerateMap(board);
	while (!gameEnded){
		if(player1Active){
			currentPlayer = player1;
		}
		else {
			currentPlayer=player2;
		}
		PlayGame(board, currentPlayer);
		if (CheckWin(board, currentPlayer)) {
			ShowMap(board);
			std::cout << "Omedetou " << currentPlayer << " !" << std::endl;
			gameEnded = true;
		}
		player1Active = !player1Active;
	}

	system("pause");
	return 0;
}