#include "Zombie.h"

Zombie* zombieHorde(int N, std::string name)
{
	if (N <= 0)
		return (NULL);
	Zombie* newZombies = new Zombie[N];
	for(int i = 0; i < N; i++)
		newZombies[i].setName(name);
	return (newZombies);
}