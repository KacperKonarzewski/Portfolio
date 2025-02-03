#include "Fixed.h"

Fixed::Fixed() : number(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& f) : number(f.number)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(int const n) : number(roundf(n * (1 << bits)))
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(float const n) : number(roundf(n * (1 << bits)))
{
	std::cout << "Float constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& f)
{
	number = f.number;
	std::cout << "Copy assignment operator called" << std::endl;
	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

float Fixed::toFloat(void) const
{
	return (float)number / (1 << bits);  // Convert fixed-point back to float
}

int Fixed::toInt(void) const
{
	return number >> bits;  // Convert fixed-point back to int
}

// Overloading << operator for easy output
std::ostream& operator<<(std::ostream &out, const Fixed &f)
{
	out << f.toFloat();
	return out;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (number);
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	number = raw;
}