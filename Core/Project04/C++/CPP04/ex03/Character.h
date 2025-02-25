#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "ICharacter.h"
#include "AMateria.h"

class Character : public ICharacter
{
private:
	std::string name;
	AMateria *materias[4];
public:
	Character();
	Character(std::string name);
	Character(const Character &c);
	Character &operator=(const Character &c);
	virtual ~Character();
	const std::string &getName() const;
	void equip(AMateria *m);
	void unequip(int idx);
	void use(int idx, ICharacter &target);
};

#endif