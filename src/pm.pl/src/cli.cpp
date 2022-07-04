#include "cli.h"

#include "userWizard.h"

#include <functional>

std::unique_ptr<cli::Menu> pm::pl::getMenu(const bool isAdmin, const size_t loggedUserId)
{
	auto rootMenu =  std::make_unique<cli::Menu>("main");
	
	rootMenu->Insert("ping", [](std::ostream& out) 
	{
		std::cout << "pong" << '\n'; 
	});

	rootMenu->Insert(std::move(pm::pl::getUserManagerSubMenu(isAdmin, loggedUserId)));

	return rootMenu;
}

void pm::pl::cli(std::unique_ptr<cli::Menu> menu)
{
	cli::Cli cli(std::move(menu));

	/*cli.ExitAction([](std::ostream& out)
		{
			std::cout << "Bye!" << '\n';
		});*/

	cli.StdExceptionHandler(
		[](std::ostream& out, const std::string& cmd, const std::exception& e)
		{
			out << "Exception caught in cli handler: "
				<< e.what()
				<< " handling command: "
				<< cmd
				<< ".\n";
		}
	);

	cli::LoopScheduler scheduler;
	cli::CliLocalTerminalSession localSession(cli, scheduler, std::cout);

	scheduler.Post([] {std::cout << "Welcome to the Project Manager!"; });
	
	scheduler.Run();
}

std::unique_ptr<cli::Menu> pm::pl::getUserManagerSubMenu(const bool isAdmin, 
	const size_t loggedUserId)
{
	auto menu = std::make_unique<cli::Menu>("userManager");

	menu->Insert("list", [](std::ostream& out) 
	{ 
		printAllUsers(out); 
	}, "List all users.");
	
	menu->Insert("add", [loggedUserId](std::ostream& out, 
		std::string username,
		std::string password,
		std::string firstName,
		std::string lastName,
		bool isAdmin)
	{
		auto now = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now());

		pm::bll::addUser({ username, password, firstName, lastName,
			now, loggedUserId, now, loggedUserId, 0, isAdmin });
		
	}, "Add a user.", { "Username", "Password", "First name", "Last name", "Is Admin (bool)", });

	menu->Insert("ping", [](std::ostream& out)
		{
			out << "User pong\n";
		});

	return menu;
}