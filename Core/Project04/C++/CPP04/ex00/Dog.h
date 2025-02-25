#pragma once
#ifndef DOG_H
#define DOG_H

#include "Animal.h"

class Dog : public Animal
{
private:

public:
	Dog();
	virtual ~Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	void makeSound() const;
};

#endif