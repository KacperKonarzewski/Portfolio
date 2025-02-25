#pragma once
#ifndef CURE_H
#define CURE_H

#include <string>
#include "AMateria.h"

class Cure : public AMateria
{
private:
	std::string type;
public:
	Cure();
	Cure(std::string const &type);
	virtual ~Cure();
	Cure(const Cure &c);
	Cure& operator=(const Cure &c);
	std::string const &getType() const;
	virtual AMateria* clone() const;
	virtual void use(ICharacter &target);
};

#endif