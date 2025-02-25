#pragma once
#ifndef BRAIN_H
#define BRAIN_H

#include <string>

class Brain
{
private:
	std::string ideas[100];
public:
	Brain();
	Brain(const Brain &c);
	Brain& operator=(const Brain &c);
	~Brain();
	void setIdea(int index, std::string idea);
	std::string getIdea(int index) const;
};

#endif