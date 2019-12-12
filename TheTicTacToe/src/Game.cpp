/*
	==============================================================================
							The TicTacToe Project!
	==============================================================================

	A small project to demonstrate some of the main areas of OOP using C++. I've also created a small AI Path to follow for the PC in PvC!

	It features 2 modes, the classics PvP and PvC.

	The PvC AI is developed by my logic, and it might not be a 100% consistent rate for the AI to win. That was the purpose, since the minimax algorithm,
	one widely used for things/games like this, is simply a thing where the player could never win.

	Made By: Aryan Rawlani
			 aryanrawlani007@gmail.com
*/

#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <random>
#include <ostream>
#include <iterator>
#include <utility>
#include <map>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>

// My files
#include "Computer.h"
#include "Person.h"
#include "Player.h"
#include "TicTacToeBoard.h"

#define Log(x) std::cout << (x) << std::endl
#define Max_Size 3
#define Max_Moves_Made 9

inline void empty_board() {
	std::cout << "==============================================================" << std::endl;

	std::cout << "\t\t _|_|_ \n";
	std::cout << "\t\t _|_|_ \n";
	std::cout << "\t\t  | |  \n";

	std::cout << "==============================================================" << std::endl;
}

void PvP();
void PvC();

std::string PvCToss();
std::string PvPToss(Player&, Player&);

std::vector<std::pair<int, int>> availableMoves;
std::vector<std::pair<int, int>> priorityMoves;
std::vector<std::pair<int, int>> computerMoves;
std::vector<std::pair<int, int>> userMoves;

void setAvailableMoves(std::vector<std::pair<int, int>>& availableMoves) {
	availableMoves.emplace_back(0, 0);
	availableMoves.emplace_back(1, 1);
	availableMoves.emplace_back(2, 2);
	availableMoves.emplace_back(2, 0);
	availableMoves.emplace_back(0, 2);

	availableMoves.emplace_back(0, 1);
	availableMoves.emplace_back(1, 0);
	availableMoves.emplace_back(1, 2);
	availableMoves.emplace_back(2, 1);
}

void setPriorityMoves(std::vector<std::pair<int, int>>& priorityMoves) {
	priorityMoves.emplace_back(0, 0); 	//Priority moves means corners of the board, and the center.
	priorityMoves.emplace_back(1, 1);
	priorityMoves.emplace_back(2, 2);

	priorityMoves.emplace_back(2, 0);
	priorityMoves.emplace_back(0, 2);
}


std::ostream& operator<< (std::ostream& out, const TicTacToeBoard& B1) {			//Printing the board.
	std::cout << "  | 0 | 1 | 2 |" << std::endl;
	std::cout << "----------------" << std::endl;
	for (int i = 0; i < Max_Size; i++) {
		//std::cout << "";
		for (int j = 0; j < Max_Size; j++) {
			if (j == 0) {
				std::cout << i << " | ";
			}
			out << B1.Board1[i][j] << " | ";
		}
		std::cout << std::endl;
	}

	std::cout << "=======================================================" << std::endl;
	return out;
}


int main()
{
	int playerChoice;

	while (true) {
		std::cout << "################################################################################\n";
		Log("\t\t\tWelcome to the TicTacToe Project!!");
		std::cout << "################################################################################\n";

		Log("\tStart playing now!");

		Log("\n\t1. PvP\n\t2. PvC\n\t3. Exit\t");
		std::cin >> playerChoice;
		switch (playerChoice)
		{
		case 1:
			PvP();
			break;
		case 2:
			PvC();
			break;
		case 3:
			exit(0);
		default:
			break;
		}
	}
}

void PvP() {
	Log("\tYou have selected Player vs Player Mode!");

	Log("\n\tGet ready, Game will start soon.");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	Log("\n\tInitializing board...\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	Log("\tDusting up....\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "\tApplying finishing touches...\n\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));

	int x, y;
	int count = 0;
	int who = 0;
	std::vector<std::pair<int, int>> MovesMade;

	Log("\tGame is now ready, lets begin! \n\n");

	TicTacToeBoard B1;

	Player p1;
	std::cout << std::endl << p1.getName() << " has entered the game. Are you ready to step up, Player2?\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	Player p2;
	std::cout << std::endl << p2.getName() << " has now entered the game. Starting the game soon!\n\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	//empty_board();
	std::string tossWinner = PvPToss(p1, p2);
	std::cout << "\nLooks like " << tossWinner << " has won the toss! Go first. Your letter is X." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	B1.PrintBoard(B1);
	while (B1.getMoves() < Max_Moves_Made) {

		while (true) {
			if (who % 2 == 0 || who == 0) {
				std::cout << "It's your chance, " << p1.getName() << " !" << std::endl << std::flush;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else {
				std::cout << "It's your chance, " << p2.getName() << " !" << std::endl << std::flush;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			Log("\nPlease enter coordinates: ");		// Zero based indexing.
			std::cin >> x >> y;

			auto it = std::find(MovesMade.begin(), MovesMade.end(), std::make_pair(x, y)); // Incase the user enters same coords, this will warn, and prompt to enter again.

			if (x < 0 || x > 2 || y < 0 || y > 2) {
				Log("Looks like you made a mistake. Try entering the coords again!\n\n");
				continue;
			}
			else if (it != MovesMade.end()) {
				Log("You entered a duplicate set of coords coords. Try again.");
				continue;
			}
			else {
				MovesMade.emplace_back(x, y);
				break;
			}

		}

		if (B1.setBoard(B1, who, x, y)) {					//	The function setBoard returns true if it finds that a winner exists on board.
			B1.PrintBoard(B1);
			int winner = p1.WinnerDeclaration(who);

			if (winner == 0) {
				std::cout << p1.getName() << ", congratulations! You beat " << p2.getName() << "!";
			}
			else {
				std::cout << p2.getName() << ", congratulations! You beat " << p1.getName() << "!";
			}

			break;
		}
		B1.PrintBoard(B1);
		B1.setMoves();
		who++;

		if (B1.getMoves() == Max_Moves_Made) {
			Log("Well played, this looks like a tie. Play again to decide the ultimate champ!");
		}
	}

	return;
}

std::string PvPToss(Player& p1, Player& p2)		// A 50-50 chance of either players winning the toss. Returns directly the name of the toss winner.
{
	std::cout << "\nI'm Tossing now!\n";
	std::mt19937 randomGen(std::time(0));

	std::uniform_real_distribution<float> toss(0.0f, 1.0f);

	if (toss(randomGen) <= 0.5f) {
		return p1.getName();
	}
	else {
		return p2.getName();
	}
}

void PvC() {
	std::cout << "\n\n\tPlayer vs Computer Mode!\n\n";

	int moveNo = 0;
	int who = 0;

	Log("\tCleaning up the board.......\n\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	TicTacToeBoard B1;
	Player player1;
	std::cout << "\n";

	Log("Let's see who will battle you today...");
	std::this_thread::sleep_for(std::chrono::seconds(5));
	Computer computer1;

	std::vector<std::pair<int, int>> availableMoves;
	setAvailableMoves(availableMoves);


	std::vector<std::pair<int, int>> computerMoves;
	std::vector<std::pair<int, int>> userMoves;

	std::vector<std::pair<int, int>> priorityMoves;
	setPriorityMoves(priorityMoves);

	std::pair<int, int> selected;
	std::string TossWinner = PvCToss();
	std::cout << "I'm tossing now. Aaaand the winner is....................." << TossWinner << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	int x, y;
	int xy;
	B1.PrintBoard(B1);
	if (TossWinner == "Computer") {
		//Different AI Path if Computer has the first chance. PS - Not following the minimax algorithm, using my own AI logic based on the assumption
		//that diagonals are more powerful for winning.

		/*
			If Toss has been won by Computer, the following path is followed:

			Move #)
					1) Computer chooses at random a priority move (corners and center). Choosing a PM (Priority move) leads to a better chance of winning.
					2) Player chooses.

					3) PC chooses, a PM.
					4) Player chooses.

					5) Computer first checks if any square available to win. If so, do it. Otherwise check if user can win.
					   If yes, play that move. If even player cannot win, choose random and place your own, preferably from PM.
					6) Player chooses.

					7) Repeat step 5.
					8) Player chooses.

					9) Repeat step 5.
		*/

		std::cout << computer1.getName() << ", you have won the toss!!\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));

		while (B1.getMoves() < Max_Moves_Made)
		{

			if (who == 0 || who % 2 == 0) {		// Computer moves

				std::cout << computer1.getName() << " is now thinking what to do.\n\n";
				std::this_thread::sleep_for(std::chrono::seconds(3));

				if (moveNo == 0) {
					srand(time(0));
					xy = rand() % priorityMoves.size();			//index genereated acc to PM.

					selected = priorityMoves.at(xy);		//select a move from the available indexes

					B1.setBoard(B1, who, selected.first, selected.second);
					B1.PrintBoard(B1);

					computerMoves.emplace_back(selected);	// Computer makes this move, so added to his vector

					// Erase this move from both: AM (Available Moves) & PM (Priority Moves)
					availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
					priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());
				}
				else if (moveNo == 2) {
					srand(time(0));
					xy = rand() % priorityMoves.size();
					selected = priorityMoves.at(xy);

					B1.setBoard(B1, who, selected.first, selected.second);
					B1.PrintBoard(B1);

					computerMoves.emplace_back(selected);

					availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
					priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());
				}
				else {
					//	In here, this path is followed:
					//	First, check if I (computer) can win.
					selected = B1.specialCheckForAIComputer(B1, who);	//	If I can win, this will return a valid pair. Like (1,2) or something.

					if (selected.first == -1 && selected.second == -1) {	//	If I cannot win, it returns me (-1,-1)

						//Since I cannot win, I now check if user can win.
						//Next, I check if user can win. If yes, obstruct his path.
						++who;
						selected = B1.specialCheckForAIComputer(B1, who);	// Gotta increment who, since I'm actually checking for player - if he can win or not.
						--who;

						if (selected.first == -1 && selected.second == -1) {			// If player cannot win, it'll return me (-1,-1)

							//	Since now even user cannot win, I check if priority moves are available. If yes, insert element from priority moves.
							if (priorityMoves.size() != 0) {	// But first, check if the size of PM is not zero. If it is, choose from AM instead.
								srand(time(0));
								xy = rand() % priorityMoves.size();
								selected = priorityMoves.at(xy);

								if (B1.setBoard(B1, who, selected.first, selected.second)) {
									B1.PrintBoard(B1);
									int winner = player1.WinnerDeclaration(who);

									if (winner == 0) {
										std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!" << std::endl;
									}
									else {
										std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!" << std::endl;
									}
									break;
								}
								B1.PrintBoard(B1);

								computerMoves.emplace_back(selected);
								availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
								priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());

							}
							else {					// If I'm here, I found out that PM is empty. So I will choose a random from AM.
								srand(time(0));
								xy = rand() % availableMoves.size();
								selected = availableMoves.at(xy);

								if (B1.setBoard(B1, who, selected.first, selected.second)) {
									B1.PrintBoard(B1);
									int winner = player1.WinnerDeclaration(who);

									if (winner == 0) {
										std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!" << std::endl;
									}
									else {
										std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!" << std::endl;
									}
									break;
								}
								B1.PrintBoard(B1);
								computerMoves.emplace_back(selected);
								availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
							}
						}
						else {											//If I'm here, it means I found that user is winning. I will now obstruct him.
							computerMoves.emplace_back(selected);

							availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());

							auto it = std::find(priorityMoves.begin(), priorityMoves.end(), selected);		//If exists in PM, remove.
							if (it != priorityMoves.end()) {
								priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());
							}

							if (B1.setBoard(B1, who, selected.first, selected.second)) {
								B1.PrintBoard(B1);
								int winner = player1.WinnerDeclaration(who);

								if (winner == 0) {
									std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!" << std::endl;
								}
								else {
									std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!" << std::endl;
								}
								break;
							}
							B1.PrintBoard(B1);
						}
					}
					else {											// If I'm here, I found a path to win!!! Kudos to me :D
						computerMoves.emplace_back(selected);

						availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
						auto it = std::find(priorityMoves.begin(), priorityMoves.end(), selected);
						if (it != priorityMoves.end()) {
							priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());
						}

						if (B1.setBoard(B1, who, selected.first, selected.second)) {
							B1.PrintBoard(B1);
							int winner = player1.WinnerDeclaration(who);

							if (winner == 0) {
								std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!" << std::endl;
							}
							else {
								std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!" << std::endl;
							}

							break;
						}
						B1.PrintBoard(B1);
					}
				}
			}
			else {				//	Player moves
				while (true) {	//	Keep asking until enter correct coords
					std::cout << std::endl << player1.getName() << ", it's your turn. Please enter coordinates: ";		// 0 based indexing.
					std::cin >> x >> y;

					auto it = std::find(availableMoves.begin(), availableMoves.end(), std::make_pair(x, y));

					if (x < 0 || x > 2 || y < 0 || y > 2)
					{
						Log("Looks like you made a mistake. Try entering the coords again!\n\n");
						continue;
					}
					else if (it == availableMoves.end()) {
						Log("Hey, are you trying to cheat or what? You can't do that. Enter coords which are empty.\n\n");
						continue;
					}
					else
					{
						break;
					}
				}

				if (B1.setBoard(B1, who, x, y)) {
					B1.PrintBoard(B1);
					int winner = player1.WinnerDeclaration(who);

					if (winner == 0) {
						std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!";
					}
					else {
						std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!";
					}
					break;
				}
				B1.PrintBoard(B1);
				userMoves.emplace_back(x, y);

				availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), std::make_pair(x, y)), availableMoves.end());
				auto it = std::find(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y));
				if (it != priorityMoves.end()) {
					priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y)), priorityMoves.end());
				}
			}


			who++;
			moveNo++;
			B1.setMoves();

			if (who == 9) {
				std::cout << "Looks like the game has come to a tie." << std::endl;
				break;
			}

		}


	}


	else if (TossWinner == "Player") {
		std::cout << player1.getName() << ", you won! Start the game!!" << std::endl;

		who = 0;

		while (B1.getMoves() < Max_Moves_Made) {
			if (who == 0 || who % 2 == 0) {					//	Player move
				while (true) {								//	Keep asking until enter correct coords
					Log("\nPlease enter coordinates: ");		//	Zero based indexing.
					std::cin >> x >> y;

					auto it = std::find(availableMoves.begin(), availableMoves.end(), std::make_pair(x, y));

					if (x < 0 || x > 2 || y < 0 || y > 2)
					{
						Log("Looks like you made a mistake. Try entering the coords again!\n\n");
						continue;
					}
					else if (it == availableMoves.end()) {
						Log("Hey, are you trying to cheat or what? You can't do that. Enter coords which are empty.\n\n");
						continue;
					}
					else
					{
						break;
					}
				}

				userMoves.emplace_back(x, y);
				availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), std::make_pair(x, y)), availableMoves.end());

				auto it = std::find(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y));
				if (it != priorityMoves.end()) {
					priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y)), priorityMoves.end());
				}

				if (B1.setBoard(B1, who, x, y)) {
					B1.PrintBoard(B1);
					int winner = player1.WinnerDeclaration(who);

					if (winner == 0) {
						std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!";
					}
					else {
						std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!";
					}

					break;
				}

				B1.PrintBoard(B1);
			}
			else {												//	Computer move;
				/*
				If the computer has lost the toss, AI takes on a bit of a different path.
				Steps #)
						1) Player move.
						2) AI moves according to random PM. (PM -> Priority Move)

						3) Player move.
						4) AI first checks if user can win. If yes, obstruct his path. Otherwise choose a random PM.

						5) Player move.
						6) AI now first checks if itself can win. If yes, do it & win. Otherwise check if player can win. If yes, obstruct.
						Otherwise perform a PM if available, otherwise choose from AM.

						7) Player move.
						8) Same as step 6.

						9) Player move.
				*/
				if (moveNo == 1) {
					std::cout << computer1.getName() << " is now thinking what to do.\n" << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));

					srand(time(0));
					xy = rand() % priorityMoves.size();			//	Index generated acc to priority indexes (corners and center)

					selected = priorityMoves.at(xy);
					computerMoves.emplace_back(selected);

					availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
					priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());

					B1.setBoard(B1, who, selected.first, selected.second);

					B1.PrintBoard(B1);
				}
				else if (moveNo == 3) {
					//	First i check if user wins. If yes, obstruct his path.
					std::cout << computer1.getName() << " is now thinking what to do.\n" << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));
					++who;
					selected = B1.specialCheckForAIComputer(B1, who);
					--who;

					if (selected.first == -1 && selected.second == -1) {
						// If I'm here, it means user cannot win in this move. Now I take a PM.

						srand(time(0));
						xy = rand() % priorityMoves.size();
						selected = priorityMoves.at(xy);

						computerMoves.emplace_back(selected);
						availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
						priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());

						B1.setBoard(B1, who, selected.first, selected.second);
						B1.PrintBoard(B1);
					}
					else {
						//	If im here, I found a move where user is winning. I'm now blocking him.
						computerMoves.emplace_back(selected);

						availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end()); //erase from AM
						auto it = std::find(priorityMoves.begin(), priorityMoves.end(), selected);
						if (it != priorityMoves.end()) {
							priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end()); //if exist, rem from AM
						}

						B1.setBoard(B1, who, selected.first, selected.second);
						B1.PrintBoard(B1);
					}
				}
				else {
					//	If I'm here, I'll follow a specific path each time I get a play.
					//	Now onwards, I will always check if I (PC) can win. If so, do it.
					std::cout << computer1.getName() << " is now thinking what to do.\n" << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));

					selected = B1.specialCheckForAIComputer(B1, who);

					if (selected == std::make_pair(-1, -1)) {
						// If I'm here, it means I can't win. Since I cant win, I now check if user can win.
						++who;		// Increasing who -> means computer will check if user can win in next move.
						selected = B1.specialCheckForAIComputer(B1, who);
						--who;

						if (selected == std::make_pair(-1, -1)) {
							//	If I'm here, it means that user cannot also win, I now try to get a PM.
							if (priorityMoves.size() != 0) {
								//	If here, it means there's a PM available.

								srand(time(0));
								xy = rand() % priorityMoves.size();

								selected = priorityMoves.at(xy);
								computerMoves.emplace_back(selected);

								availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());
								priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), selected), priorityMoves.end());

								if (B1.setBoard(B1, who, selected.first, selected.second)) {
									B1.PrintBoard(B1);
									int winner = player1.WinnerDeclaration(who);

									if (winner == 0) {
										std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!";
									}
									else {
										std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!";
									}
									break;
								}

								B1.PrintBoard(B1);
							}
							else {
								//	If I'm here, this means theres no PM available, I select one from AM.
								srand(time(0));
								xy = rand() % availableMoves.size();

								selected = availableMoves.at(xy);
								availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());

								if (B1.setBoard(B1, who, selected.first, selected.second)) {
									B1.PrintBoard(B1);
									int winner = player1.WinnerDeclaration(who);

									if (winner == 0) {
										std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!";
									}
									else {
										std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!";
									}

									break;
								}

								B1.PrintBoard(B1);
							}

						}
						else {
							//this else block means user can win.
							computerMoves.emplace_back(selected);
							availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());

							auto it = std::find(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y));
							if (it != priorityMoves.end()) {
								priorityMoves.erase(std::remove(priorityMoves.begin(), priorityMoves.end(), std::make_pair(x, y)), priorityMoves.end());
							}

							B1.setBoard(B1, who, selected.first, selected.second);
							B1.PrintBoard(B1);
						}
					}
					else {
						//this else block means computer can win.

						computerMoves.emplace_back(selected);
						availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), selected), availableMoves.end());

						if (B1.setBoard(B1, who, selected.first, selected.second)) {
							B1.PrintBoard(B1);
							int winner = player1.WinnerDeclaration(who);

							if (winner == 0) {
								std::cout << player1.getName() << ", congratulations! You beat " << computer1.getName() << "!";
							}
							else {
								std::cout << computer1.getName() << ", congratulations! You beat " << player1.getName() << "!";
							}

							break;
						}
						B1.PrintBoard(B1);

					}
				}
			}

			moveNo++;
			B1.setMoves();
			who++;
		}
	}
}

std::string PvCToss() {
	std::mt19937 randomGen(std::time(0));

	std::uniform_real_distribution<float> toss(0.0f, 1.0f);

	if (toss(randomGen) <= 0.5f) {
		return "Player";
	}
	else {
		return "Computer";
	}
}