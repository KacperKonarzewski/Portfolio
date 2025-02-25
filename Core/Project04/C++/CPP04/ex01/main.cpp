#include <iostream>
#include "WrongCat.h"
#include "Dog.h"
#include "Cat.h"

int main()
{
	const int numAnimals = 10;
	Animal *animals[numAnimals];

	for (int i = 0; i < numAnimals / 2; ++i)
	{
		animals[i] = new Dog();
	}
	for (int i = numAnimals / 2; i < numAnimals; ++i)
	{
		animals[i] = new Cat();
	}

	for (int i = 0; i < numAnimals; ++i)
	{
		std::cout << animals[i]->getType() << " ";
		animals[i]->makeSound();
	}

	for (int i = 0; i < numAnimals; ++i)
	{
		delete animals[i];
	}

	return 0;
}