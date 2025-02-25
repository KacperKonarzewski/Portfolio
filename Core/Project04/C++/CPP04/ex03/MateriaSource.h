#pragma once
#ifndef MATERIASOURCE_H
#define MATERIASOURCE_H

#include "IMateriaSource.h"

class MateriaSource : public IMateriaSource
{
private:
	AMateria *materias[4];
public:
	MateriaSource();
	virtual ~MateriaSource();
	MateriaSource(const MateriaSource &c);
	MateriaSource &operator=(const MateriaSource &c);
	void learnMateria(AMateria *m);
	AMateria* createMateria(std::string const &type);
};

#endif