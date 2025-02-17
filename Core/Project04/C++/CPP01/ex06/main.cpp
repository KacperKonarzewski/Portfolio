#include "Harl.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	Harl harl = Harl();
	std::string converted = argv[1];
	harl.complain(converted);
}
