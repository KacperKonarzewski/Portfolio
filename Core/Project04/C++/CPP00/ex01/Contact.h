#pragma once

#include <string>
#include <iostream>

class Contact
{
private:
	std::string	first_name;
	std::string	last_name;
	std::string nickname;
	std::string	number;
	std::string darkest_secret;
public:
	Contact(std::string first_name, std::string last_name,
			std::string nickname, std::string number, std::string darkest_secret);
	Contact();
	~Contact();
	void DisplayContact(void);
	std::string	getFirstName(void);
	std::string	getLastName(void);
	std::string	getNickname(void);
};

