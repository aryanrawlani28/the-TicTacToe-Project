#include "Player.h"

Player::Player() {
	setName();
}

std::string Player::getName() const {
	return this->name;
}

int Player::WinnerDeclaration(const int& who) const {
	if (who % 2 == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void Player::setName() {
	std::string typedName;
	std::cout << "Please enter player name: ";
	std::cin >> typedName;

	this->name = typedName;
	printer();
}

void Player::printer() const {
	std::cout << "Welcome " << this->name << " to the game!" << std::endl;
}
