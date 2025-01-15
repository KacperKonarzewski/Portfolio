#pragma once

#include "Contact.h"
#include <string>
#include <iostream>

class PhoneBook
{
private:
	Contact contacts[8];
	int		last_id;
	int		current_size;
public:
	PhoneBook();
	~PhoneBook();
	void PushContact(Contact con);
	void PrintRow(int i);
	int	 getCurrentSize(void);
	Contact* getContacts(void);
};
