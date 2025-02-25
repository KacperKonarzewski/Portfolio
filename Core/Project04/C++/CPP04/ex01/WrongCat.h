#pragma once
#ifndef WRONGCAT_H
#define WRONGCAT_H

#include "WrongAnimal.h"

class WrongCat : public WrongAnimal
{
public:
    WrongCat();
    WrongCat(std::string type);
    ~WrongCat();
    WrongCat(const WrongCat &c);
    WrongCat& operator=(const WrongCat &c);
    void makeSound() const;
};

#endif