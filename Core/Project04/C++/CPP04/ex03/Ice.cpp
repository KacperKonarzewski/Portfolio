#include "Ice.h"

#include <iostream>

Ice::Ice() : AMateria("ice") {
	std::cout << "Ice default constructor called" << std::endl;
}

Ice::Ice(std::string const &type) : AMateria(type) {
	std::cout << "Ice constructor called" << std::endl;
}

Ice::~Ice() {
	std::cout << "Ice destructor called" << std::endl;
}

Ice::Ice(const Ice &c) : AMateria(c) {
	std::cout << "Ice copy constructor called" << std::endl;
	*this = c;
}

Ice& Ice::operator=(const Ice &c) {
	std::cout << "Ice assignation operator called" << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return *this;
}

std::string const &Ice::getType() const {
	return type;
}

AMateria* Ice::clone() const {
	return new Ice(*this);
}

void Ice::use(ICharacter &target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
