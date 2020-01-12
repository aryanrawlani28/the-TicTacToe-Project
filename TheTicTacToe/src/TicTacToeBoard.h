#pragma once

/*
_|_|_  _  ~|~o _~|~ _  _~|~ _  _  |~)._ _  o _ __|_
 | | |}_   | |(_ | (_|(_ | (_)}_  |~ | (_)_|}_(_ | 
 */

#include <iostream>
#include <string>
#include <vector>
#include <thread>

#define Log(x) std::cout << (x) << std::endl

class TicTacToeBoard {
private:
	inline static int MovesMade = 0;
	int counter;
	std::vector<std::vector<char>> Board1;
	const inline static std::string mainTitle = R"(
 _   _            _____ _     _____          _____           
| |_| |__   ___  /__   (_) __/__   \__ _  __/__   \___   ___ 
| __| '_ \ / _ \   / /\/ |/ __|/ /\/ _` |/ __|/ /\/ _ \ / _ \
| |_| | | |  __/  / /  | | (__/ / | (_| | (__/ / | (_) |  __/
 \__|_| |_|\___|  \/   |_|\___\/   \__,_|\___\/   \___/ \___|
                                                             
   ___           _           _   
  / _ \_ __ ___ (_) ___  ___| |_ 
 / /_)/ '__/ _ \| |/ _ \/ __| __|
/ ___/| | | (_) | |  __/ (__| |_ 
\/    |_|  \___// |\___|\___|\__|
              |__/               

	)";

public:
	TicTacToeBoard();

	const void static getTitle();

	void PrintBoard(const TicTacToeBoard& B1) const;

	friend std::ostream& operator<<(std::ostream& out, const TicTacToeBoard& B1);

	int getMoves() const;

	void setMoves();

	bool setBoard(TicTacToeBoard& B1, const int& who, int& x, int& y);

	bool checkBoardForResult(const TicTacToeBoard& B1) const;


	std::pair<int, int> specialCheckForAIComputer(const TicTacToeBoard& B1, const int& who);

	~TicTacToeBoard();
};