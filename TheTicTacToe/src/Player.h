#pragma once

#include <iostream>
#include "Person.h"

class Player : public Person {
public:
	Player();

	std::string getName() const;

	int WinnerDeclaration(const int& who) const;

	void setName();

	void printer() const;
};

