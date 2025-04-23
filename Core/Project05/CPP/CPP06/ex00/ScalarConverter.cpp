#include "ScalarConverter.h"

#include <iostream>
#include <bits/stdc++.h> 
#include <string>

ScalarConverter::~ScalarConverter()
{

}

ScalarConverter::ScalarConverter()
{

}

size_t	ft_strlen(std::string str)
{
	size_t	i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}

int	ft_strchr(std::string str, char c)
{
	int i;

	for (i = 0; str[i] && str[i] != c; i++)
		;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

bool	ft_strcmp(std::string str, std::string str2)
{
	size_t i;

	for (i = 0; str[i] && str2[i] && str[i] == str2[i]; i++)
		;
	if (ft_strlen(str) == i && ft_strlen(str2) == i)
		return (true);
	else
		return (false);
}

t_values ScalarConverter::convert(std::string str)
{
	t_values	vals;
	size_t		length;

	length = ft_strlen(str);
	if (ft_strcmp(str, "inf"))
	{
		
	}
	if (length == 3 && str[0] == '\'' && str[2] == '\'')
	{
		vals.char_val = str[1];
		vals.int_val = static_cast<int>(str[1]);
		vals.float_val = static_cast<float>(str[1]);
		vals.double_val = static_cast<double>(str[1]);
		return (vals);
	}
	if (ft_strchr(str, '.') != -1)
	{
		if (ft_strchr(str, 'f') != -1)
		{
			str[ft_strchr(str, 'f')] = 0;
			vals.float_val = static_cast<float>(atof(str.c_str()));
			vals.int_val = static_cast<int>(vals.float_val);
			vals.double_val = static_cast<double>(vals.float_val);
		}
		else
		{
			vals.double_val = static_cast<double>(atof(str.c_str()));
			vals.int_val = static_cast<int>(vals.double_val);
			vals.float_val = static_cast<float>(vals.double_val);
		}
	}
	else
	{
		vals.int_val = static_cast<int>(atoi(str.c_str()));
		vals.double_val = static_cast<double>(vals.int_val);
		vals.float_val = static_cast<float>(vals.int_val);
	}
	vals.char_val = static_cast<char>(vals.int_val);
	return (vals);
}

void	print_t_values(t_values vals)
{
	std::cout << "char: '" << vals.char_val << "'" << std::endl;
	std::cout << "int: " << vals.int_val << std::endl;
	std::cout << "float: " << vals.float_val << "f" << std::endl;
	std::cout << "double: " << vals.double_val << std::endl;
}
