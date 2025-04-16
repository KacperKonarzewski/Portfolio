#include "ShrubberyCreationForm.h"
#include <iostream>
#include <string>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), target(target)
{

}
ShrubberyCreationForm::~ShrubberyCreationForm()
{

}
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) : AForm(other), target(other.target)
{

}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other)
{
	if (this != &other)
	{
		this->target = other.target;
	}
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!this->getIsSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getExecuteGrade())
		throw AForm::GradeTooLowException();
	std::ofstream file(this->target + "_shrubbery");
	if (!file)
	{
		std::cerr << "Error: could not create file" << std::endl;
		return;
	}
	file << "       _-_-_\n";
	file << "    _-_-_-_-_\n";
	file << " _-_-_-_-_-_-_\n";
	file << "  _-_-_-_-_-_-_\n";
	file << "    _-_-_-_\n";
	file << "       | |\n";
	file << "       | |\n";
	file << "       |_|\n";
	file.close();
	std::cout << "Shrubbery created in file " << this->target << "_shrubbery" << std::endl;
}
