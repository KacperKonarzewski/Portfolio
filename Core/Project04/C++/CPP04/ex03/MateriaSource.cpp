#include "MateriaSource.h"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; ++i) {
		materias[i] = NULL;
	}
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] != NULL) {
			delete materias[i];
		}
	}
}

MateriaSource::MateriaSource(const MateriaSource &c) {
	*this = c;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &c) {
	if (this != &c) {
		for (int i = 0; i < 4; ++i) {
			if (materias[i] != NULL) {
				delete materias[i];
			}
			materias[i] = c.materias[i]->clone();
		}
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria *m) {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] == NULL) {
			materias[i] = m->clone();
			break;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const &type) {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] != NULL && materias[i]->getType() == type) {
			return materias[i]->clone();
		}
	}
	return NULL;
}
