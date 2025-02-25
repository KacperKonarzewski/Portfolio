#include "Brain.h"

#include <iostream>

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain &c)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = c;
}

Brain& Brain::operator=(const Brain &c)
{
	std::cout << "Brain assignation operator called" << std::endl;
	if (this != &c)
	{
		for (int i = 0; i < 100; i++)
			ideas[i] = c.ideas[i];
	}
	return *this;
}
