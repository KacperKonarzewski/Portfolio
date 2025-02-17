#include "FragTrap.h"

FragTrap::FragTrap() : ClapTrap()
{
	this->name = "";
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
	std::cout << "FragTrap Default constractor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->hp = 100;
	this->ep = 100;
	this->ad = 30;
	std::cout << "FragTrap Constractor called" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &c) : ClapTrap(c)
{
	std::cout << "FragTrap Copy constractor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &c)
{
	this->name = c.getName();	
	this->hp = c.getHp();
	this->ep = c.getEp();
	this->ad = c.getAd();
	std::cout << "FragTrap Assignment constractor called" << std::endl;
	return *this;
}

void FragTrap::attack(const std::string& target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	ep--;
	std::cout << "FragTrap " + this->name + " attacks " + target + ", causing " << this->ad << " points of damage!" << std::endl;
}

void	FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << this->name << " wants to high five" << std::endl;
}