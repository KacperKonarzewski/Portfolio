#pragma once
#ifndef FRAGTRAP_H
#define FRAGTRAP_H

# include "ClapTrap.h"

class FragTrap : public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &c);
	FragTrap& operator=(const FragTrap &c);
	virtual ~FragTrap();
	void attack(const std::string& target);
	void highFivesGuys();
};

#endif