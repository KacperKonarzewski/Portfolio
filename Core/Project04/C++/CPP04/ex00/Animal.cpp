#include "Animal.h"

#include <iostream>

Animal::Animal()
{
	type = "";
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type)
{
	this->type = type;
	std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const Animal &c)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = c;
}

Animal& Animal::operator=(const Animal &c)
{
	std::cout << "Animal assignation operator called" << std::endl;
	if (this != &c)
		this->type = c.type;
	return *this;
}

std::string Animal::getType() const
{
	return type;
}