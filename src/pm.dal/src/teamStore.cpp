#include "pch_dal.h"

#include "teamStore.h"
#include "db.h"

#include "timeConv.h";

#include <iostream>

void pm::dal::createTeam(std::string_view teamName, size_t creatorId)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"INSERT INTO Teams (Name, "
		"DateOfCreation, IdOfCreator, DateOfLastChange, IdOfLastChanger) "
		"VALUES (?, GETDATE(), ?, GETDATE(), ?)");

	statement.bind(0, teamName.data());
	statement.bind(1, &creatorId);
	statement.bind(2, &creatorId);

	nanodbc::execute(statement);
}

std::vector<pm::types::Team> pm::dal::retrieveAllTeams()
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, Name, DateOfCreation, IdOfCreator," 
		"DateOfLastChange, IdOfLastChanger "
		"FROM Teams");

	nanodbc::result result = nanodbc::execute(statement);
	
	std::vector<types::Team> teams;
	teams.reserve(result.rows() || 1);
	
	while (result.next())
	{
		teams.push_back(std::move(constructTeam(result)));
	}

	return teams;
}

std::optional<pm::types::Team> pm::dal::retrieveTeam(std::string_view teamName)
try
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, Name, DateOfCreation, IdOfCreator," 
		"DateOfLastChange, IdOfLastChanger "
		"FROM Teams WHERE Name = ?");

	statement.bind(0, teamName.data());
	
	nanodbc::result result = nanodbc::execute(statement);
	
	result.next();

	auto team = constructTeam(result);

	return { team };
}
catch (...)
{
	return std::nullopt;
}

std::optional<pm::types::Team> pm::dal::retrieveTeam(size_t teamId)
try
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"SELECT Id, Name, DateOfCreation, IdOfCreator,"
		"DateOfLastChange, IdOfLastChanger "
		"FROM Teams WHERE Id = ?");

	statement.bind(0, &teamId);

	nanodbc::result result = nanodbc::execute(statement);

	result.next();

	auto team = constructTeam(result);

	return { team };
}
catch (...)
{
	return std::nullopt;
}

void pm::dal::deleteTeam(std::string_view teamName)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, "DELETE FROM Teams WHERE Name = ?");

	statement.bind(0, teamName.data());

	nanodbc::execute(statement);
}

void pm::dal::assignUser(size_t userId, size_t teamId)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"INSERT INTO UsersTeams (UserId, TeamId) "
		"VALUES (?, ?)");

	statement.bind(0, &userId);
	statement.bind(1, &teamId);

	nanodbc::execute(statement);
}

void pm::dal::unAssignUser(size_t userId, size_t teamId)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"DELETE FROM UsersTeams WHERE UserId = ? AND TeamId = ?");

	statement.bind(0, &userId);
	statement.bind(1, &teamId);

	nanodbc::execute(statement);
}

std::vector<pm::types::Team> pm::dal::retrieveUserTeams(size_t userId)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, "SELECT TeamId "
		"FROM UsersTeams WHERE UserId = ?");

	statement.bind(0, &userId);
	
	nanodbc::result result = nanodbc::execute(statement);
	
	std::vector<types::Team> teams;
	teams.reserve(result.rows() || 1);
	
	while (result.next())
	{
		auto teamId = result.get<size_t>("TeamId");
		auto team = retrieveTeam(teamId);
		
		if (team)
		{
			teams.push_back(std::move(*team));
		}
		else
		{
			std::cout << "Team id that failed: " << teamId << '\n';
		}
	}

	return teams;
}

void pm::dal::renameTeam(
	size_t teamId, std::string_view newName, size_t loggedUserId)
{
	auto conn = DB::get().conn();

	nanodbc::statement statement(conn);

	nanodbc::prepare(statement,
		"UPDATE Teams SET Name = ?, DateOfLastChange = GETDATE(), "
		"IdOfLastChanger = ? WHERE Id = ?");

	statement.bind(0, newName.data());
	statement.bind(1, &loggedUserId);
	statement.bind(2, &teamId);

	nanodbc::execute(statement);
}

pm::types::Team pm::dal::constructTeam(nanodbc::result& result)
{
	auto id = result.get<size_t>("Id");
	auto name = result.get<std::string>("Name");
	auto dateOfCreation =
		pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfCreation"));
	auto idOfCreator = result.get<size_t>("IdOfCreator");
	auto dateOfLastChange =
		pm::utils::toTimeT(result.get<nanodbc::timestamp>("DateOfLastChange"));
	auto idOfLastChanger = result.get<size_t>("IdOfLastChanger");
	
	return { id, name, dateOfCreation, idOfCreator, 
		dateOfLastChange, idOfLastChanger };
}
