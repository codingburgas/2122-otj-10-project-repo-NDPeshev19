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

std::optional<pm::types::User> pm::dal::getUserLogin(
	std::string_view username, std::string_view password) 
try 
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users "
		"WHERE Username = ? AND Password = ? AND IsDeleted = 0");


	auto hashed = md5(std::string(password));
	statement.bind(0, username.data());
	statement.bind(1, hashed.c_str());

	nanodbc::result result = nanodbc::execute(statement);

	result.next();

	auto user = constructUser(result);

	return { user };
}
catch (...)
{
	return std::nullopt;
}

std::vector<pm::types::User> pm::dal::retrieveAllUsers()
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users "
		"WHERE IsDeleted = 0");

	return extractUsersimpl(nanodbc::execute(statement));
}

std::vector<pm::types::User> pm::dal::retrieveAllUsersWithDeleted()
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users ");

	return extractUsersimpl(nanodbc::execute(statement));
}

std::vector<pm::types::User> pm::dal::extractUsersimpl(nanodbc::result result)
{
	std::vector<pm::types::User> users;
	users.reserve(result.rows() || 1);

	while (result.next())
	{
		auto user = constructUser(result);

		users.push_back(std::move(user));
	}

	return users;
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

std::optional<pm::types::User> pm::dal::retrieveUser(size_t userId)
try 
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users "
		"WHERE Id = ? AND IsDeleted = 0");

	statement.bind(0, &userId);

	nanodbc::result result = nanodbc::execute(statement);
	result.next();

	auto user = constructUser(result);

	return { user };
}
catch (...)
{
	return std::nullopt;
}

std::optional<pm::types::User> pm::dal::retrieveUserWithDeleted(size_t userId)
try
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, UserName, Password, FirstName, LastName, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger, "
		"IsDeleted, IsAdmin "
		"FROM Users "
		"WHERE Id = ?");

	statement.bind(0, &userId);

	nanodbc::result result = nanodbc::execute(statement);
	result.next();

	auto user = constructUser(result);

	return { user };
}
catch (...)
{
	return std::nullopt;
}

void pm::dal::deleteUser(const size_t userIdToDelete, 
	const size_t loggedUserId)
try
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"UPDATE Users "
		"SET IsDeleted = 1, idOfLastChanger = ?, DateOfLastChange = GETDATE()"
		"WHERE Id = ?");
	
	statement.bind(0, &loggedUserId);
	statement.bind(1, &userIdToDelete);
	
	nanodbc::execute(statement);
}
catch (...)
{
	throw std::runtime_error("Failed to delete user.");
}

void pm::dal::restoreUser(size_t userIdToRestore, size_t loggedUserId)
try
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"UPDATE Users "
		"SET IsDeleted = 0, idOfLastChanger = ?, DateOfLastChange = GETDATE()"
		"WHERE Id = ?");

	statement.bind(0, &loggedUserId);
	statement.bind(1, &userIdToRestore);

	nanodbc::execute(statement);
}
catch (...)
{
	throw std::runtime_error("Failed to restore user.");
}

void pm::dal::giveAdminPrivileges(size_t userIdToOp, size_t loggedUserId)
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"UPDATE Users "
		"SET IsAdmin = 1, idOfLastChanger = ?, DateOfLastChange = GETDATE()"
		"WHERE Id = ?");

	statement.bind(0, &loggedUserId);
	statement.bind(1, &userIdToOp);

	nanodbc::execute(statement);
}

void pm::dal::revokeAdminPrivileges(size_t userIdToDeOp, size_t loggedUserId)
{
	auto& conn = pm::dal::DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"UPDATE Users "
		"SET IsAdmin = 0, idOfLastChanger = ?, DateOfLastChange = GETDATE()"
		"WHERE Id = ?");

	statement.bind(0, &loggedUserId);
	statement.bind(1, &userIdToDeOp);

	nanodbc::execute(statement);
}

// Note: Call nanodbc::result::next before invoking.
pm::types::User pm::dal::constructUser(nanodbc::result& result)
{
	auto id = result.get<size_t>("Id");
	auto userName = result.get<std::string>("UserName");
	auto passwordHash = result.get<std::string>("Password");
	auto firstName = result.get<std::string>("FirstName");
	auto lastName = result.get<std::string>("LastName");
	auto dateOfCreation = 
		pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfCreation"));
	auto idOfCreator = result.get<size_t>("IdOfCreator");
	auto dateOfLastChanger = 
		pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfLastChange"));
	auto idOfLastChanger = result.get<size_t>("IdOfLastChanger");
	auto isDeleted = static_cast<bool>(result.get<int>("IsDeleted"));
	auto isAdmin = static_cast<bool>(result.get<int>("IsAdmin"));

	return { id, userName, passwordHash, firstName, lastName,
			dateOfCreation, idOfCreator, dateOfLastChanger, idOfLastChanger,
			isDeleted, isAdmin };
}
