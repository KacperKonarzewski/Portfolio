#include "ScalarConverter.h"

#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	t_values	vals;
	std::string str;
	(void)argc;

	if (argc != 2)
		return (-1);
	str = argv[1];
	vals = ScalarConverter::convert(str);
	print_t_values(vals);
	return (0);
}
