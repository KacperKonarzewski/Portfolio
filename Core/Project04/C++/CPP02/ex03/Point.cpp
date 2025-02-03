#include "Point.h"

Point::Point(const Fixed x, const Fixed y) : x(x), y(y)
{
	std::cout << "Fixed constructor called" << std::endl;
}

Point& Point::operator=(const Point& p)
{
	if (this == &p)
		return *this;
	return *this;
}

Point::Point() : x(0), y(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Point::Point(const Point& p) : x(p.getX()), y(p.getY())
{
	std::cout << "Copy constructor called" << std::endl;
}

const Fixed& Point::getX() const
{
	return x;
}

const Fixed& Point::getY() const
{
	return y;
}

Point::~Point()
{
	std::cout << "Destructor called" << std::endl;
}