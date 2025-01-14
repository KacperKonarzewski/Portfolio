#include "Zombie.h"

int	main(void)
{
	Zombie* zombies = zombieHorde(5, "Foo");
	
	for (int i = 0; i < 5; i++)
		zombies[i].announce();
	delete[] zombies;
	return (0);
}
