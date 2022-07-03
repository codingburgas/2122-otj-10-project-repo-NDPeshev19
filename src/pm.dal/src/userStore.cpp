#pragma once

#include "pch_dal.h"
#include "db.h"
#include "userStore.h"
#include "asLValue.h"
#include "md5.h"

#include <iostream>

void pm::dal::ensureAdminUser()
{
	if (checkForAdminUser())
		return;

	using std::chrono::system_clock;
	const auto now = system_clock::to_time_t(system_clock::now());

	createUser(
		{ "admin", "adminpass", "admin", "admin",
		now, 1, now, 1, false, true });
}

bool pm::dal::checkForAdminUser()
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT COUNT(*) "
		"FROM Users "
		"WHERE Username = 'admin'");

	nanodbc::result result = nanodbc::execute(statement);

	result.next();

	return result.get<int>(0);
}

void pm::dal::createUser(const pm::types::User& user)
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"INSERT INTO Users"
		"(Username, Password, "
		"FirstName, LastName, "
		"DateOfCreation, IdOfCreator, "
		"DateOfLastChange, idOfLastChanger, "
		"isDeleted, isAdmin) "
		"VALUES (?, ?, ?, ?, GETDATE(), ?, GETDATE(), ?, ?, ?)");

	const auto hashedPassword = md5(user.password);

	statement.bind(0, user.username.c_str());
	statement.bind(1, hashedPassword.c_str());
	statement.bind(2, user.firstName.c_str());
	statement.bind(3, user.lastName.c_str());
	statement.bind(4, &user.idOfCreator);
	statement.bind(5, &user.idOfLastChanger);
	statement.bind(6, &lvalue_cast(static_cast<int>(user.isDeleted)));
	statement.bind(7, &lvalue_cast(static_cast<int>(user.isAdmin)));

	nanodbc::execute(statement);
}