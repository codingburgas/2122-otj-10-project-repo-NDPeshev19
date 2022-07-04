#include "userWizard.h"

#include <iostream>
#include <string>
#include <chrono>


void pm::pl::printAllUsers(std::ostream& out, const bool includeDeleted)
{
	auto users = pm::bll::getAllUsers(includeDeleted);
	
	for (const auto& user : users)
	{
		out << user.toPrettyString() << '\n' << std::string(47, '-') << '\n';
	}
}

void pm::pl::addUser(std::ostream& out, const size_t creatorId)
{
	pm::types::User user;

	out << "User creation:\n";
	out << "Username:\n";
	std::getline(std::cin, user.username);
	out << "Password:\n";
	std::getline(std::cin, user.password);
	out << "FirstName:\n";
	std::getline(std::cin, user.firstName);
	out << "LastName:\n";
	std::getline(std::cin, user.lastName);
	out << "IsAdmin (0 - no, 1 - yes):\n";
	std::cin >> user.isAdmin;

	auto now = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());

	user.dateOfCreation = now;
	user.dateOfLastChange = now;
		
	user.idOfCreator = creatorId;
	user.idOfLastChanger = creatorId;

	user.isDeleted = false;

	// pm::bll::addUser(user);

	out << user.toPrettyString() << '\n';

	out << "\nUser added successfully!\n";
}
