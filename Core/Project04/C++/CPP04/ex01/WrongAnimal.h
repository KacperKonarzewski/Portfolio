#pragma once
#ifndef WRONGANIMAL_H
#define WRONGANIMAL_H

#include <string>
#include <iostream>

class WrongAnimal
{
protected:
    std::string type;
public:
    WrongAnimal();
    WrongAnimal(std::string type);
    ~WrongAnimal();
    WrongAnimal(const WrongAnimal &c);
    WrongAnimal& operator=(const WrongAnimal &c);
    void makeSound() const; // Not virtual
};

#endif
