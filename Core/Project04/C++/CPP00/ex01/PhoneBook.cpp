#include "PhoneBook.h"

PhoneBook::PhoneBook()
{
	last_id = 0;
	current_size = 0;
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::PushContact(Contact con)
{
	last_id %= 8;
	contacts[last_id] = con;
	if (current_size < 8)
		current_size++;
	last_id++;
}
void PhoneBook::PrintRow(int i)
{
	std::string first_name = contacts[i].getFirstName();
	std::string last_name = contacts[i].getLastName();
	std::string nickname = contacts[i].getNickname();
	size_t len;

	len = first_name.length();
	if (len > 10)
	{
		first_name.resize(9);
		first_name += ".";
	}
	else
		first_name.insert(0, 10 - len, ' ');
	len = last_name.length();
	if (len > 10)
	{
		last_name.resize(9);
		last_name += ".";
	}
	else
		last_name.insert(0, 10 - len, ' ');
	len = nickname.length();
	if (len > 10)
	{
		nickname.resize(9);
		nickname += ".";
	}
	else
		nickname.insert(0, 10 - len, ' ');
	std::cout << "         " << i + 1 << "|" << first_name << "|" << last_name << "|" << nickname << std::endl;
}

int PhoneBook::getCurrentSize()
{
	return (current_size);
}

Contact* PhoneBook::getContacts(void)
{
	return (contacts);
}