#include "Form.h"

Form::Form(std::string const name, int signGrade, int executeGrade) : name(name), isSigned(false), signGrade(signGrade), executeGrade(executeGrade)
{
	if (signGrade < 1 || executeGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || executeGrade > 150)
		throw GradeTooLowException();
}
Form::~Form()
{
}
Form::Form(Form const &other) : name(other.name), signGrade(other.signGrade), executeGrade(other.executeGrade)
{
	*this = other;
}
Form &Form::operator=(Form const &other)
{
	*this = other;
	return *this;
}

std::string Form::getName() const
{
	return this->name;
}

bool Form::getIsSigned() const
{
	return this->isSigned;
}

int Form::getSignGrade() const
{
	return this->signGrade;
}

int Form::getExecuteGrade() const
{
	return this->executeGrade;
}

void Form::beSigned(Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->signGrade)
		throw GradeTooLowException();
	this->isSigned = true;
}
const char *Form::GradeTooHighException::what() const throw()
{
	return "Grade is too high";
}
const char *Form::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

std::ostream &operator<<(std::ostream &out, Form const &form)
{
	out << "Form: " << form.getName() << ", Sign Grade: " << form.getSignGrade() << ", Execute Grade: \
		" << form.getExecuteGrade() << ", Is Signed: " << (form.getIsSigned() ? "Yes" : "No");
	return out;
}