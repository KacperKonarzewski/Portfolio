#include "AForm.h"

AForm::AForm(std::string const name, int signGrade, int executeGrade) : name(name), isSigned(false), signGrade(signGrade), executeGrade(executeGrade)
{
	if (signGrade < 1 || executeGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || executeGrade > 150)
		throw GradeTooLowException();
}
AForm::~AForm()
{
}
AForm::AForm(AForm const &other) : name(other.name), signGrade(other.signGrade), executeGrade(other.executeGrade)
{
	*this = other;
}
AForm &AForm::operator=(AForm const &other)
{
	*this = other;
	return *this;
}

std::string AForm::getName() const
{
	return this->name;
}

bool AForm::getIsSigned() const
{
	return this->isSigned;
}

int AForm::getSignGrade() const
{
	return this->signGrade;
}

int AForm::getExecuteGrade() const
{
	return this->executeGrade;
}

void AForm::beSigned(Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->signGrade)
		throw GradeTooLowException();
	this->isSigned = true;
}
const char *AForm::GradeTooHighException::what() const throw()
{
	return "Grade is too high";
}
const char *AForm::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed";
}

std::ostream &operator<<(std::ostream &out, AForm const &form)
{
	out << "Form: " << form.getName() << ", Sign Grade: " << form.getSignGrade() << ", Execute Grade: \
		" << form.getExecuteGrade() << ", Is Signed: " << (form.getIsSigned() ? "Yes" : "No");
	return out;
}