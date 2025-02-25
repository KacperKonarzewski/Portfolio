#pragma once
#ifndef ICE_H
#define ICE_H

#include <string>
#include "AMateria.h"

class Ice : public AMateria
{
private:
	std::string type;
public:
	Ice();
	Ice(std::string const &type);
	virtual ~Ice();
	Ice(const Ice &c);
	Ice& operator=(const Ice &c);
	std::string const &getType() const;
	virtual AMateria* clone() const;
	virtual void use(ICharacter &target);
};

#endif