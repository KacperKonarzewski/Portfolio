#pragma once

#include <iostream>
#include <string>

class Zombie
{
	private:
		std::string name;
	public:
		Zombie(std::string name);
		Zombie();
		~Zombie();
		void setName(std::string name);
		void announce( void );
};

Zombie* zombieHorde(int N, std::string name);

