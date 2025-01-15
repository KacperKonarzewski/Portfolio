#include <iostream>
#include <string>

char	ft_toupper(char c)
{
	return (c - ((c >= 'a') && (c <= 'z')) * 32);
}

int main(int argc, char **argv)
{
	std::string str;
	int			len;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; i++)
	{
		str = argv[i];
		len = str.length();
		for (int j = 0; j < len; j++)
			std::cout << ft_toupper(str[j]);
		std::cout << " ";
	}
	std::cout << std::endl;
}
