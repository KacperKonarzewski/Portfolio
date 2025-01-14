#include "Zombie.h"

int	main(void)
{
	Zombie* zom = newZombie("Foo");
	zom->announce();
	randomChump("Foo2");
	delete(zom);
	return (0);
}
