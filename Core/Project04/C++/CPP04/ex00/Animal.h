#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal
{
protected:
	std::string type;
public:
	Animal();
	Animal(std::string type);
	virtual ~Animal();
	Animal(const Animal &c);
	Animal& operator=(const Animal &c);
	virtual void makeSound() const;
	std::string getType() const;
};

#endif