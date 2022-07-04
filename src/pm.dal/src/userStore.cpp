#pragma once

#include "pch_dal.h"

#include "db.h"
#include "userStore.h"
#include "asLValue.h"
#include "md5.h"
#include "timeConv.h"

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

std::optional<pm::types::User> pm::dal::getUserLogin(std::string_view username, std::string_view password)
try {
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users "
		"WHERE Username = ? AND Password = ?");


	auto hashed = md5(std::string(password));
	statement.bind(0, username.data());
	statement.bind(1, hashed.c_str());

	nanodbc::result result = nanodbc::execute(statement);

	result.next();

	auto id = result.get<size_t>("Id");
	auto userName = result.get<std::string>("UserName");
	auto passwordHash = result.get<std::string>("Password");
	auto firstName = result.get<std::string>("FirstName");
	auto lastName = result.get<std::string>("LastName");
	auto dateOfCreation = pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfCreation"));
	auto idOfCreator = result.get<size_t>("IdOfCreator");
	auto dateOfLastChanger = pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfLastChange"));
	auto idOfLastChanger = result.get<size_t>("IdOfLastChanger");
	auto isDeleted = static_cast<bool>(result.get<int>("IsDeleted"));
	auto isAdmin = static_cast<bool>(result.get<int>("IsAdmin"));

	//	id, userName, passwordHash, firstName, lastName,
	//	dateOfCreation, idOfCreator, dateOfLastChanger, idOfLastChanger,
	//	isDeleted, isAdmin

	return {{ id, userName, passwordHash, firstName, lastName,
						dateOfCreation, idOfCreator, dateOfLastChanger, idOfLastChanger,
						isDeleted, isAdmin }};
}
catch (...)
{
	return std::nullopt;
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