#include "Intern.h"
#include <iostream>
#include <string>
#include <exception>

Intern::Intern()
{
}
Intern::~Intern()
{
}
Intern::Intern(Intern const &other)
{
	*this = other;
}
Intern &Intern::operator=(Intern const &other)
{
	(void)other;
	return *this;
}
const char *Intern::FormNotFoundException::what() const throw()
{
	return "Form not found";
}
AForm *createShrubberyCreationForm(std::string target)
{
	return new ShrubberyCreationForm(target);
}
AForm *createRobotomyRequestForm(std::string target)
{
	return new RobotomyRequestForm(target);
}
AForm *createPresidentialPardonForm(std::string target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string formName, std::string target)
{
	AForm *form = nullptr;
	int	i = 0;
	std::string levels[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	while (i < 3)
	{
		if (formName == levels[i])
			break;
		i++;
	}
	switch (i)
	{
	case 0:
		form = createShrubberyCreationForm(target);
		break;
	case 1:
		form = createRobotomyRequestForm(target);
		break;
	case 2:
		form = createPresidentialPardonForm(target);
		break;
	default:
		throw FormNotFoundException();
		break;
	}
	return form;
}