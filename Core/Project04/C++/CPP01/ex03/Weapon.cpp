#include "Weapon.h"

Weapon::Weapon()
{
	type = "";
}

Weapon::Weapon(std::string type)
{
	this->type = type;
}

Weapon::~Weapon()
{
}

const std::string& Weapon::getType(void)
{
	return (type);
}

void Weapon::setType(std::string type)
{
	this->type = type;
}