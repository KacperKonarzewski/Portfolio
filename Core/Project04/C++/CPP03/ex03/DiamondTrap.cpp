#include "DiamondTrap.h"

DiamondTrap::DiamondTrap() : ClapTrap()
{
	this->name = "";
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
	std::cout << "FragTrap Default constractor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name)
{
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
	std::cout << "FragTrap Constractor called" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &c) : ClapTrap(c)
{
	std::cout << "FragTrap Copy constractor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &c)
{
	this->name = c.getName();	
	this->hp = c.getHp();
	this->ep = c.getEp();
	this->ad = c.getAd();
	std::cout << "FragTrap Assignment constractor called" << std::endl;
	return *this;
}
