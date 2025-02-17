#include "ClapTrap.h"

ClapTrap::ClapTrap() : name(""), hp(10), ep(10), ad(0)
{
	this->name = "";
	std::cout << "Default constractor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hp(10), ep(10), ad(0)
{
	std::cout << "Constractor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &c)
{
	this->name = c.getName();	
	this->hp = c.getHp();
	this->ep = c.getEp();
	this->ad = c.getAd();
	std::cout << "Copy constractor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &c)
{
	this->name = c.getName();	
	this->hp = c.getHp();
	this->ep = c.getEp();
	this->ad = c.getAd();
	std::cout << "Assignment constractor called" << std::endl;
	return *this;
}

void ClapTrap::attack(const std::string& target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	ep--;
	std::cout << "ClapTrap " + this->name + " attacks " + target + ", causing " << this->ad << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	this->hp -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (ep <= 0 || hp <= 0)
		return ;
	this->hp += amount;
}

std::string ClapTrap::getName() const
{
	return name;
}

int	ClapTrap::getHp() const
{
	return hp;
}

int	ClapTrap::getEp() const
{
	return ep;
}

int	ClapTrap::getAd() const
{
	return ad;
}
