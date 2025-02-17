#include "Harl.h"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug()
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info()
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning()
{
	std::cout << "I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error()
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
	int i;
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	i = 0;
	while (i < 4)
	{
		if (level == levels[i])
			break;
		i++;
	}
	switch (i)
	{
		case 0:
			std::cout << "[ DEBUG ]" << std::endl;
			Harl::debug();
			std::cout << "[ INFO ]" << std::endl;
			Harl::info();
			std::cout << "[ WARNING ]" << std::endl;
			Harl::warning();
			std::cout << "[ ERROR ]" << std::endl;
			Harl::error();
			break;
		case 1:
			std::cout << "[ INFO ]" << std::endl;
			Harl::info();
			std::cout << "[ WARNING ]" << std::endl;
			Harl::warning();
			std::cout << "[ ERROR ]" << std::endl;
			Harl::error();
			break;
		case 2:
			std::cout << "[ WARNING ]" << std::endl;
			Harl::warning();
			std::cout << "[ ERROR ]" << std::endl;
			Harl::error();
			break;
		case 3:
			std::cout << "[ ERROR ]" << std::endl;
			Harl::error();
			break;
		default:
			std::cout << "[UNKNOWN] Harl does not understand this level of complaint." << std::endl;
			break;
	}
}
