#pragma once

#include <string>
#include <iostream>
#include <cmath> 

class Fixed
{
private:
	int number;
	static const int bits = 8;
public:
	Fixed();
	Fixed(int const n);
	Fixed(float const n);
	Fixed(const Fixed &f);
	Fixed& operator=(const Fixed &f);
	~Fixed();
	float toFloat(void) const;
	int toInt(void) const;
	int getRawBits (void) const;
	void setRawBits (int const raw);
};

std::ostream& operator<<(std::ostream &out, const Fixed &f);