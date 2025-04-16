#pragma once
#ifndef FORM_H
#define FORM_H

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.h"

class AForm
{
private:
	std::string const name;
	bool isSigned;
	int const signGrade;
	int const executeGrade;
protected:
	class GradeTooHighException : public std::exception
	{
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
		virtual const char *what() const throw();
	};
	class FormNotSignedException : public std::exception
	{
		virtual const char *what() const throw();
	};
public:
	AForm(std::string const name, int signGrade, int executeGrade);
	virtual ~AForm();
	AForm(AForm const &other);
	AForm &operator=(AForm const &other);
	virtual std::string getName() const;
	virtual bool getIsSigned() const;
	virtual int getSignGrade() const;
	virtual int getExecuteGrade() const;
	virtual void beSigned(Bureaucrat &bureaucrat);
	virtual void execute(Bureaucrat const &executor) const = 0;
};

std::ostream &operator<<(std::ostream &out, AForm const &form);

#endif