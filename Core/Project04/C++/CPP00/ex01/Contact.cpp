#include "Contact.h"

Contact::Contact(std::string first_name, std::string last_name,
			std::string nickname, std::string number, std::string darkest_secret)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->nickname = nickname;
	this->number = number;
	this->darkest_secret = darkest_secret;
}
Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::DisplayContact()
{
	std::cout << first_name << std::endl << last_name << std::endl << nickname << std::endl;
	std::cout << number << std::endl << darkest_secret << std::endl;
}

std::string	Contact::getFirstName()
{
	return (first_name);
}

std::string	Contact::getLastName()
{
	return (last_name);
}

std::string	Contact::getNickname()
{
	return (nickname);
}