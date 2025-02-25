#include "Cure.h"

#include <iostream>

Cure::Cure() : AMateria("cure") {
	std::cout << "Cure default constructor called" << std::endl;
}

Cure::Cure(std::string const &type) : AMateria(type) {
	std::cout << "Cure constructor called" << std::endl;
}

Cure::~Cure() {
	std::cout << "Cure destructor called" << std::endl;
}

Cure::Cure(const Cure &c) : AMateria(c) {
	std::cout << "Cure copy constructor called" << std::endl;
	*this = c;
}

Cure& Cure::operator=(const Cure &c) {
	std::cout << "Cure assignation operator called" << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return *this;
}

std::string const &Cure::getType() const {
	return type;
}

AMateria* Cure::clone() const {
	return new Cure(*this);
}

void Cure::use(ICharacter &target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}