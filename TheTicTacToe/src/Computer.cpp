#include "Computer.h"
#include <random>
#include <ctime>
#include <thread>

Computer::Computer() {
	ComputerNames = {
		// "CD Projekt Red", "Techland", "EA", "Rockstar", "2K", "Sony", "Take 2", "Marvel", "Bioware", "Ubisoft", "Square Enix", "Popcap", "Bethesda", "Blizzard"
		"Dr. Dhara Bhatt", "Ms. Manali Brahmbhatt", "Ms. Nithya Nadar", "XICA", "Ms. Khushboo Shah", "Ms. Cecil Johny", "Fr. David"
	};
	this->name = giveRandomName();
	printer();
}

std::string Computer::giveRandomName() {
	std::mt19937 randGen(std::time(0));
	std::uniform_int_distribution<int> possibleNames(0, ComputerNames.size() - 1);

	std::string randomName = this->ComputerNames.at(possibleNames(randGen));

	return randomName;
}

void Computer::printer() const {
	std::cout << "\nWelcome computer " << this->name << " to the game!\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

std::string Computer::getName() const {
	return this->name;
}