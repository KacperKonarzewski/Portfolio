#pragma once
#ifndef AMATERIA_H
#define AMATERIA_H

#include <string>
#include "ICharacter.h"

class AMateria
{
protected:
	std::string type;
public:
	AMateria();
	AMateria(std::string const &type);
	virtual ~AMateria();
	AMateria(const AMateria &c);
	AMateria& operator=(const AMateria &c);
	std::string const &getType() const;
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter &target);
};

#endif