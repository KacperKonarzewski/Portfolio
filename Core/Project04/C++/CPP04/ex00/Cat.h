#pragma once
#ifndef CAT_H
#define CAT_H

#include "Animal.h"

class Cat : public Animal
{
private:

public:
	Cat();
	Cat(std::string type);
	virtual ~Cat();
	Cat(const Cat &c);
	Cat& operator=(const Cat &c);
	void makeSound() const;
};

#endif