#pragma once

#include <vector>
#include <random>
#include <time.h>
#include <iostream>
#include <cstdlib>

#include "Person.h"

class Computer : public Person {		//Treating computer also as a person, with name.
	std::vector<std::string> ComputerNames;
public:
	Computer();

	std::string giveRandomName();

	void printer() const;

	std::string getName() const;
};
