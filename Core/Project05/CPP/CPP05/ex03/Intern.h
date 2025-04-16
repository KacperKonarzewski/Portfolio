#pragma once
#ifndef INTERN_H
#define INTERN_H
#include <iostream>
#include <string>
#include "AForm.h"
#include "Bureaucrat.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"

class Intern
{
public:
	Intern();
	~Intern();
	Intern(Intern const &other);
	Intern &operator=(Intern const &other);
	AForm *makeForm(std::string formName, std::string target);
	class FormNotFoundException : public std::exception
	{
		virtual const char *what() const throw();
	};
};
std::ostream &operator<<(std::ostream &out, Intern const &intern);
AForm *createShrubberyCreationForm(std::string target);
AForm *createRobotomyRequestForm(std::string target);
AForm *createPresidentialPardonForm(std::string target);

#endif