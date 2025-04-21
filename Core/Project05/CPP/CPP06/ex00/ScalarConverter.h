#pragma once
#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include "string"

typedef struct s_values
{
	char	char_val;
	int		int_val;
	float	float_val;
	double	double_val;
}	t_values;


class ScalarConverter
{
private:
	ScalarConverter();
	~ScalarConverter();
public:
	ScalarConverter(const ScalarConverter &cpy) = delete;
	ScalarConverter& operator=(const ScalarConverter& other) = delete;
	static t_values convert(std::string str);
};

#endif