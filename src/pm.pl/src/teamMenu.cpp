#include "teamMenu.h"

std::unique_ptr<cli::Menu> pm::pl::getTeamManagerSubMenu(
	bool isAdmin, size_t loggedUserId)
{
	auto menu = std::make_unique<cli::Menu>("teamManager");

	if (isAdmin)
	{
		menu->Insert("add",
			[loggedUserId](std::ostream& out, std::string teamName)
			{
				pm::bll::addTeam(teamName, loggedUserId);
				out << "Team " << teamName << " added\n";
			}, "Create a new team", { "Name of team" });

		// Get all users of team (list team and it's users)
		menu->Insert("listTeamUsers",
			[](std::ostream& out, std::string teamName)
			{
				auto users = pm::bll::getTeamUsers(teamName);
				auto table = pm::pl::getUsersTable(users);
				out << table << '\n';
			}, "List all users of a team", { "Name of team" });
		
		menu->Insert("listUserTeams",
			[](std::ostream& out, std::string username)
			{
				auto teams = pm::bll::getUserTeams(username);
				auto table = pm::pl::getTeamsTable(teams);
				out << table << '\n';
			}, "List all teams that a certain user is in", {"Username"});
		
		menu->Insert("rename",
			[loggedUserId](
				std::ostream& out, std::string teamName, std::string newName)
			{
				pm::bll::renameTeam(teamName, newName, loggedUserId);
				out << "Team " << teamName << 
					" renamed to " << newName << '\n';
			}, "Rename a team", { "Team name", "New name" });
		
		menu->Insert("assign",
			[loggedUserId](std::ostream& out, 
				std::string username, std::string teamName)
			{
				pm::bll::assignUser(username, teamName);
				out<< "User " << username << 
					" assigned to team " << teamName << '\n';
			}, "Add a user to a team", {"Username", "Team name"});

		menu->Insert("unAssign",
			[](std::ostream& out, std::string username, std::string teamName)
			{
				pm::bll::unAssignUser(username, teamName);
				out << "User " << username << 
					" removed from team " << teamName << '\n';
			}, "Remove a user from a team", {"Username", "Team name"});

		menu->Insert("delete",
			[](std::ostream& out, std::string teamName)
			{
				pm::bll::deleteTeam(teamName);
				out << "Deleted team\n";
			}, "Delete a team", { "Name of team to delete" });
	}

	menu->Insert("list",
		[](std::ostream& out)
		{
			printAllTeams(out);
		}, "List all teams");

	menu->Insert("self",
		[loggedUserId](std::ostream& out)
		{
			auto teams = 
				pm::bll::getUserTeams(
					pm::bll::getUser(loggedUserId)->username);
			
			auto table = pm::pl::getTeamsTable(teams);
			out << table << '\n';
		});


	menu->Insert("assignSelf",
		[loggedUserId](std::ostream& out, std::string teamName)
		{
			auto user = pm::bll::getUser(loggedUserId);

			pm::bll::assignUser(user->username, teamName);
			out << "You have been assigned from team " << teamName << '\n';
		}, "Assign yourself to a team", { "Team name" });

	menu->Insert("unAssignSelf",
		[loggedUserId](std::ostream& out, std::string teamName)
		{
			pm::bll::unAssignUser(
				pm::bll::getUser(loggedUserId)->username, teamName);
			out << "You have been unassigned from team " << teamName << '\n';
		}, "Unassign yourself from a team", { "Team name" });
	
	menu->Insert("shutdown",
		[](std::ostream& out)
		{
			std::cout << "Goodbye!\n";
			exit(0);
		});

	menu->Insert("cls",
		[](std::ostream& out)
		{
			system("cls");
		}, "Clear screen");

	menu->Insert("ping",
		[](std::ostream& out)
		{
			out << "User pong\n";
		});

	return menu;
}
