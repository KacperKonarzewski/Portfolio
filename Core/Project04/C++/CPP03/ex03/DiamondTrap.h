#pragma once
#ifndef DIAMONDTRAP_H
#define DIAMONDTRAP_H

# include "FragTrap.h"
# include "ScavTrap.h"

class DiamondTrap : public FragTrap, public ScavTrap
{
private:
	std::string name;
public:
	DiamondTrap();
	DiamondTrap(std::string name);
	DiamondTrap(const DiamondTrap &c);
	DiamondTrap& operator=(const DiamondTrap &c);
	~DiamondTrap();
	void attack(const std::string& target);
	void highFivesGuys();
};

#endif