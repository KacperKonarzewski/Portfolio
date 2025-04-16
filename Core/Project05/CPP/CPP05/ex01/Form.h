#pragma once
#ifndef FORM_H
#define FORM_H

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.h"

class Form
{
private:
	std::string const name;
	bool isSigned;
	int const signGrade;
	int const executeGrade;
	class GradeTooHighException : public std::exception
	{
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
		virtual const char *what() const throw();
	};
public:
	Form(std::string const name, int signGrade, int executeGrade);
	~Form();
	Form(Form const &other);
	Form &operator=(Form const &other);
	std::string getName() const;
	bool getIsSigned() const;
	int getSignGrade() const;
	int getExecuteGrade() const;
	void beSigned(Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &out, Form const &form);

#endif