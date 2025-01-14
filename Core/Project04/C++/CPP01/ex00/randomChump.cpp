#include "Zombie.h"

void	randomChump(std::string name)
{
	Zombie newZ(name);
	newZ.announce();
}
