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
	~Fixed();

	Fixed& operator=(const Fixed &f);

	bool operator>(const Fixed &r);
	bool operator<(const Fixed &r);
	bool operator>=(const Fixed &r);
	bool operator<=(const Fixed &r);
	bool operator==(const Fixed &r);
	bool operator!=(const Fixed &r);

	float operator+(const Fixed &r);
	float operator-(const Fixed &r);
	float operator*(const Fixed &r);
	float operator/(const Fixed &r);

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

	float toFloat(void) const;
	int toInt(void) const;
	int getRawBits (void) const;
	void setRawBits (int const raw);
	static Fixed& min(Fixed& f1, Fixed& f2);
	const static Fixed& min(const Fixed& f1, const Fixed& f2);
	static Fixed& max(Fixed& f1, Fixed& f2);
	const static Fixed& max(const Fixed& f1, const Fixed& f2);
};

std::ostream& operator<<(std::ostream &out, const Fixed &f);