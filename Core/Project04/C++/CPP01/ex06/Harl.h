#pragma once

#ifndef HARL_H
#define HARL_H

#include <string>
#include <iostream>

class Harl
{
private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
public:
	void complain(std::string level);
	Harl();
	~Harl();
};

#endif