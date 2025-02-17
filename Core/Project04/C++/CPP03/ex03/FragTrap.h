#pragma once
#ifndef FRAGTRAP_H
#define FRAGTRAP_H

# include "ClapTrap.h"

class FragTrap : virtual public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &c);
	FragTrap& operator=(const FragTrap &c);
	~FragTrap();
	void attack(const std::string& target);
	void highFivesGuys();
};

#endif