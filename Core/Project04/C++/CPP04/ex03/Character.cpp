#include "Character.h"
#include <iostream>

Character::Character() : name("default") {
	for (int i = 0; i < 4; ++i) {
		materias[i] = NULL;
	}
}

Character::Character(std::string name) : name(name) {
	for (int i = 0; i < 4; ++i) {
		materias[i] = NULL;
	}
}

Character::~Character() {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] != NULL) {
			delete materias[i];
		}
	}
}

Character::Character(const Character &c) {
	*this = c;
}

Character &Character::operator=(const Character &c) {
	if (this != &c) {
		name = c.name;
		for (int i = 0; i < 4; ++i) {
			if (materias[i] != NULL) {
				delete materias[i];
			}
			materias[i] = c.materias[i]->clone();
		}
	}
	return *this;
}

const std::string &Character::getName() const {
	return name;
}

void Character::equip(AMateria *m) {
	for (int i = 0; i < 4; ++i) {
		if (materias[i] == NULL) {
			materias[i] = m;
			break;
		}
	}
}

void Character::unequip(int idx) {
	if (idx >= 0 && idx < 4 && materias[idx] != NULL) {
		materias[idx] = NULL;
	}
}

void Character::use(int idx, ICharacter &target) {
	if (idx >= 0 && idx < 4 && materias[idx] != NULL) {
		materias[idx]->use(target);
	}
}
