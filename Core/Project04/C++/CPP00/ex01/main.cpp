#include "PhoneBook.h"
#include "Contact.h"

#include <string>
#include <limits>
#include <iostream>

void	checkEmpty(std::string& var)
{
	while (var == "")
	{
		std::cout << "Input cannot be empty! Try again:" << std::endl;
		std::getline(std::cin, var);
	}
}

Contact AddContactForm()
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone;
	std::string darkest_secret;

	std::cout << "Enter first name:" << std::endl;
	std::getline(std::cin, first_name);
	checkEmpty(first_name);

	std::cout << "Enter last name:" << std::endl;
	std::getline(std::cin, last_name);
	checkEmpty(last_name);

	std::cout << "Enter nickname:" << std::endl;
	std::getline(std::cin, nickname);
	checkEmpty(nickname);

	std::cout << "Enter phone number:" << std::endl;
	std::getline(std::cin, phone);
	checkEmpty(phone);

	std::cout << "Enter darkest secret:" << std::endl;
	std::getline(std::cin, darkest_secret);
	checkEmpty(darkest_secret);

	Contact con = Contact(first_name, last_name, nickname, phone, darkest_secret);
	return (con);
}

int	main()
{
	PhoneBook	book = PhoneBook();
	std::string	input;
	int			size;
	int			input2;

	while (1)
	{
		std::cout << "Select command!:" << std::endl << "ADD" << std::endl << "SEARCH" << std::endl << "EXIT" << std::endl;
		if (!(std::cin >> input))
		{
			std::cout << "Input error or EOF detected. Exiting." << std::endl;
			break;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input == "ADD")
			book.PushContact(AddContactForm());
		else if (input == "SEARCH")
		{
			size = book.getCurrentSize();
			for (int i = 0; i < size; i++)
				book.PrintRow(i);
			std::cout << "Enter a wanted index:" << std::endl;
			a:
			while (!(std::cin >> input2)) 
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter a number:" << std::endl;
			} 
			if (input2 < 1 || input2 > size) 
			{
				std::cout << "Invalid index. Please enter a number between 1 and " << size << ":" << std::endl;
				goto a;
			}
			book.getContacts()[input2 - 1].DisplayContact();
		}
		else if (input == "EXIT")
			break;
	}
	return (0);
}
