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

bool Fixed::operator>(const Fixed& r)
{
	return this->toFloat() > r.toFloat();
}

bool Fixed::operator<(const Fixed& r)
{
	return this->toFloat() < r.toFloat();
}

bool Fixed::operator>=(const Fixed& r)
{
	return this->toFloat() >= r.toFloat();
}

bool Fixed::operator<=(const Fixed& r)
{
	return this->toFloat() <= r.toFloat();
}

bool Fixed::operator==(const Fixed& r)
{
	return this->toFloat() == r.toFloat();
}

bool Fixed::operator!=(const Fixed& r)
{
	return this->toFloat() != r.toFloat();
}

float Fixed::operator+(const Fixed& r)
{
	return this->toFloat() + r.toFloat();
}

float Fixed::operator-(const Fixed& r)
{
	return this->toFloat() - r.toFloat();
}

float Fixed::operator*(const Fixed& r)
{
	return this->toFloat() * r.toFloat();
}

float Fixed::operator/(const Fixed& r)
{
	return this->toFloat() / r.toFloat();
}

Fixed& Fixed::operator++()
{
	number++;;
	return *this;
}

Fixed& Fixed::operator--()
{
	number--;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	number++;
	return temp;
}

Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	number--;
	return temp;
}

Fixed& Fixed::min(Fixed& f1, Fixed& f2)
{
	return (f1 < f2)? f1 : f2;
}
const Fixed& Fixed::min(const Fixed& f1, const Fixed& f2)
{
	return (f1.toFloat() < f2.toFloat())? f1 : f2;
}

Fixed& Fixed::max(Fixed& f1, Fixed& f2)
{
	return (f1 > f2)? f1 : f2;
}
const Fixed& Fixed::max(const Fixed& f1, const Fixed& f2)
{
	return (f1.toFloat() > f2.toFloat())? f1 : f2;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

float Fixed::toFloat(void) const
{
	return (float)number / (1 << bits);
}

int Fixed::toInt(void) const
{
	return number >> bits;
}

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
