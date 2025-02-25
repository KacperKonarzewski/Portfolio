#pragma once
#ifndef DOG_H
#define DOG_H

#include "Animal.h"
#include "Brain.h"

class Dog : public Animal
{
private:
	Brain *brain;
public:
	Dog();
	virtual ~Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	void makeSound() const;
};

#endif