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
}
tabulate::Table pm::pl::getUsersTable(std::vector<pm::types::User> users)
{
	tabulate::Table table;

	table.add_row(
		{ "Id", "Username", "Password", "First name", "Last name",
		"Date of creation", "Id of creator",
		"Date of last change", "Id of last changer",
		"Is deleted", "Is admin" });

	for (const auto& user : users)
	{
		table.add_row(
			{ std::to_string(user.id), user.username, user.password,
			user.firstName, user.lastName,
			pm::utils::toString(user.dateOfCreation),
			std::to_string(user.idOfCreator),
			pm::utils::toString(user.dateOfLastChange),
			std::to_string(user.idOfLastChanger),
			std::to_string(user.isDeleted), std::to_string(user.isAdmin) });
	}

	table[0].format()
		.font_color(tabulate::Color::yellow)
		.font_align(tabulate::FontAlign::center);

	return table;
}
