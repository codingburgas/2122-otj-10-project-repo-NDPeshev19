#include "userMenu.h"


std::unique_ptr<cli::Menu> pm::pl::getUserManagerSubMenu(const bool isAdmin,
	const size_t loggedUserId)
{
	auto menu = std::make_unique<cli::Menu>("userManager");

	if (isAdmin)
	{
		menu->Insert("list",
			[](std::ostream& out, bool includeDeleted)
			{
				pm::pl::printAllUsers(out, includeDeleted);
			}, "List all users", { "Show deleted users (bool)" });

		menu->Insert("add",
			[loggedUserId](std::ostream& out,
				std::string username,
				std::string password,
				std::string firstName,
				std::string lastName,
				bool isAdmin)
			{
				auto now = std::chrono::system_clock::to_time_t(
					std::chrono::system_clock::now());

				pm::types::User user = { username, password,
					firstName, lastName, now, loggedUserId,
					now, loggedUserId, 0, isAdmin };

				pm::bll::addUser(user);

				out << "User: " << user.firstName << ' ' <<
					user.lastName << " added.\n";
			}, "Add a user",
			{ "Username", "Password",
				"First name", "Last name", "Is Admin (bool)", });

		menu->Insert("delete",
			[loggedUserId](std::ostream& out, int userIdToDelete)
			{
				pm::bll::deleteUser(userIdToDelete, loggedUserId);
				out << "User deleted.\n";
			}, "Delete a user", { "User id to delete" });

		if (pm::bll::isUserOriginAdmin(*pm::bll::getUser(loggedUserId)))
		{
			menu->Insert("restore",
				[loggedUserId](std::ostream& out, int userIdToRestore)
				{
					pm::bll::restoreUser(userIdToRestore, loggedUserId);
					out << "User restored.\n";
				}, "Restore a user", { "User id to restore" });

			menu->Insert("otherPassword",
				[loggedUserId](std::ostream& out,
					int userIdToChangePassword, std::string newPassword)
				{
					pm::bll::changePassword(
						userIdToChangePassword, newPassword, loggedUserId);
					out << "Changed password\n";
				});
		}

		menu->Insert("op",
			[loggedUserId](std::ostream& out, int userIdToOp)
			{
				pm::bll::giveAdminPrivileges(userIdToOp, loggedUserId);
				out << "Gave admin privileges\n";
			}, "Give a user admin privileges", { "User id to op" });

		menu->Insert("deop",
			[loggedUserId](std::ostream& out, int userIdToDeop)
			{
				pm::bll::revokeAdminPrivileges(userIdToDeop, loggedUserId);
				out << "Revoked admin privileges\n";
			}, "Revoke admin privileges from a user", { "User id to deop" });
	}

	menu->Insert("password",
		[loggedUserId](std::ostream& out, std::string newPassword)
		{
			pm::bll::changePassword(loggedUserId, newPassword, loggedUserId);
			out << "Password changed.\n";
		}, "Set a new password", { "New password" });

	menu->Insert("self",
		[loggedUserId](std::ostream& out)
		{
			out <<
				pm::bll::getUser(loggedUserId)->toPrettyString() << '\n';
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