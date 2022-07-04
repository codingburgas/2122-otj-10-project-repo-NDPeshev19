#include "pch_dal.h"

#include "teamStore.h"
#include "db.h"

#include "timeConv.h";

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
