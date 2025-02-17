#pragma once
#ifndef CLAPTRAP_H
#define CLAPTRAP_H

#include <string>
#include <iostream>

class ClapTrap
{
	protected:
		std::string name;
		int			hp;
		int			ep;
		int			ad;
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &c);
		ClapTrap& operator=(const ClapTrap &c);
		~ClapTrap();
		std::string getName( void ) const;
		int getHp( void ) const;
		int getEp( void ) const;
		int getAd( void ) const;
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif
