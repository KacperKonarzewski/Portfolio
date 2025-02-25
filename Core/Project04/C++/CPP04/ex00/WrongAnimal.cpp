#include "WrongAnimal.h"

WrongAnimal::WrongAnimal() : type("WrongAnimal") {}

WrongAnimal::WrongAnimal(std::string type) : type(type) {}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &c) : type(c.type) {}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &c) {
    if (this != &c) {
        type = c.type;
    }
    return *this;
}

void WrongAnimal::makeSound() const {
    std::cout << "WrongAnimal sound!" << std::endl;
}
