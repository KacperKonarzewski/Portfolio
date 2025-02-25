#include "AMateria.h"
#include <iostream>

AMateria::AMateria() : type("") {
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const &type) : type(type) {
	std::cout << "AMateria constructor called" << std::endl;
}

AMateria::~AMateria() {
	std::cout << "AMateria destructor called" << std::endl;
}

AMateria::AMateria(const AMateria &c) {
	std::cout << "AMateria copy constructor called" << std::endl;
	*this = c;
}

AMateria& AMateria::operator=(const AMateria &c) {
	std::cout << "AMateria assignation operator called" << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return *this;
}

std::string const &AMateria::getType() const {
	return type;
}

void AMateria::use(ICharacter &target) {
	(void)target;
}