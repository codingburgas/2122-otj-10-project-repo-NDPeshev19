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

		menu->Insert("list",
			[](std::ostream& out)
			{
				printAllTeams(out);
			}, "List all teams");

		// Get all users of team (list team and it's users)
		// Get all teams of user (list users and all teams the user is in)
		// Change team name
		// Assign user to team
		
		

		// Remove user from team

		menu->Insert("delete",
			[](std::ostream& out, std::string teamName)
			{
				pm::bll::deleteTeam(teamName);
				out << "Deleted team\n";
			}, "Delete a team", { "Name of team to delete" });
	}

	menu->Insert("self",
		[loggedUserId](std::ostream& out)
		{
			// display all teams current user is in
			out << "not implemented\n";
		});

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
