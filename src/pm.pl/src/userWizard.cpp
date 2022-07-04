#include "userWizard.h"

#include "tabulate/tabulate.hpp"

#include <iostream>
#include <string>
#include <chrono>

void pm::pl::printAllUsers(std::ostream& out, const bool includeDeleted)
{
	auto users = pm::bll::getAllUsers(includeDeleted);
	
	tabulate::Table table;

	table.add_row(
		{ "Id", "Username", "Password", "First name", "Last name",
		"Date of creation", "Id of creator", 
		"Date of last change", "Id of last changer",
		"Is deleted", "Is admin"});

	for (const auto& user : users)
	{
		table.add_row(
			{ std::to_string(user.id), user.username, user.password,
			user.firstName, user.lastName,
			pm::utils::toString(user.dateOfCreation),
			std::to_string(user.idOfCreator),
			pm::utils::toString(user.dateOfLastChange),
			std::to_string(user.idOfLastChanger),
			std::to_string(user.isDeleted), std::to_string(user.isAdmin)});
	}

	table[0].format()
		.font_color(tabulate::Color::yellow)
		.font_align(tabulate::FontAlign::center);

	out << table << '\n';
	
	/*for (const auto& user : users)
	{
		out << user.toPrettyString() << '\n' << std::string(47, '-') << '\n';
	}*/
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
