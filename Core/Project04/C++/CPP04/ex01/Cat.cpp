#include "Cat.h"

#include <iostream>

Cat::Cat() : Animal("Cat")
{
	this->brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::~Cat()
{
	delete this->brain;
	std::cout << "Cat destructor called" << std::endl;
}

Cat::Cat(const Cat &c)
{
	std::cout << "Cat copy constructor called" << std::endl;
	*this = c;
}

Cat& Cat::operator=(const Cat &c)
{
	std::cout << "Cat assignation operator called" << std::endl;
	if (this != &c)
		this->type = c.type;
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "Meow meow!" << std::endl;
}
