#include "Zombie.h"

Zombie* newZombie(std::string name)
{
	Zombie* newZ = new Zombie(name);
	return (newZ);
}
