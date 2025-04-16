#include "Bureaucrat.h"

int main()
{
	try
	{
		Bureaucrat bureaucrat("John Doe", 1);
		std::cout << bureaucrat << std::endl;
		bureaucrat.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat bureaucrat("Jane Doe", 150);
		bureaucrat.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat bureaucrat("John Doe", 151);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat bureaucrat("Jane Doe", 0);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}