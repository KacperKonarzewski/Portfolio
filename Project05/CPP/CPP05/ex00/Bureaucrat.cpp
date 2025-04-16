#include "Bureaucrat.h"

Bureaucrat::Bureaucrat(std::string const name, int grade) : name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat::Bureaucrat(Bureaucrat const &other) : name(other.name)
{
	*this = other;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other)
{
	this->grade = other.grade;
	return *this;
}

std::string Bureaucrat::getName() const
{
	return this->name;
}

int Bureaucrat::getGrade() const
{
	return this->grade;
}

void Bureaucrat::incrementGrade()
{
	if (this->grade == 1)
		throw GradeTooHighException();
	this->grade--;
}

void Bureaucrat::decrementGrade()
{
	if (this->grade == 150)
		throw GradeTooLowException();
	this->grade++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
	return out;
}
