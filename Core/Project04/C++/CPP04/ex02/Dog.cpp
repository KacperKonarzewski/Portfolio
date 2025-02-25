#include "Dog.h"

#include <iostream>

Dog::Dog() : Animal("Dog")
{
	this->brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::~Dog()
{
	delete this->brain;
	std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog &c)
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = c;
}

Dog& Dog::operator=(const Dog &c)
{
	std::cout << "Dog assignation operator called" << std::endl;
	if (this != &c)
		this->type = c.type;
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "Woof woof!" << std::endl;
}
