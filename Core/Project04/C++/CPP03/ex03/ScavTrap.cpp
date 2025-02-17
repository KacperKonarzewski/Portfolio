#include "ScavTrap.h"

ScavTrap::ScavTrap() : ClapTrap()
{
	this->name = "";
	this->guarding = false;
	this->hp = 100;
	this->ep = 50;
	this->ad = 20;
	std::cout << "ScavTrap Default constractor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->hp = 100;
	this->guarding = false;
	this->ep = 50;
	this->ad = 20;
	std::cout << "ScavTrap Constractor called" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &c) : ClapTrap(c)
{
	this->guarding = c.guarding;
	std::cout << "ScavTrap Copy constractor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &c)
{
	this->name = c.getName();	
	this->hp = c.getHp();
	this->ep = c.getEp();
	this->ad = c.getAd();
	this->guarding = c.guarding;
	std::cout << "ScavTrap Assignment constractor called" << std::endl;
	return *this;
}

void ScavTrap::attack(const std::string& target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	ep--;
	std::cout << "ScavTrap " + this->name + " attacks " + target + ", causing " << this->ad << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate()
{
	if (this->guarding == false)
	{
		this->guarding = true;
		std::cout << "ScavTrap " << this->name << " is now guarding the gate." << std::endl;
	}
	else
		std::cout << "ScavTrap " << this->name << " is already guarding the gate." << std::endl;
}