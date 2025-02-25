#include "WrongCat.h"

WrongCat::WrongCat() : WrongAnimal("WrongCat") 
{
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(std::string type) : WrongAnimal(type) 
{
	std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &c) : WrongAnimal(c) {}

WrongCat &WrongCat::operator=(const WrongCat &c)
{
	if (this != &c)
	{
		WrongAnimal::operator=(c);
	}
	return *this;
}

void WrongCat::makeSound() const
{
	std::cout << "WrongCat sound!" << std::endl;
}