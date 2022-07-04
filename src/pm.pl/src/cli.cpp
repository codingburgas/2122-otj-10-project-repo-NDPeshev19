#include "cli.h"

#include "userWizard.h"

#include <functional>

std::unique_ptr<cli::Menu> pm::pl::getMenu(const bool isAdmin)
{
	auto rootMenu =  std::make_unique<cli::Menu>("main");
	
	rootMenu->Insert("ping", [](std::ostream& out) 
	{
		std::cout << "pong" << '\n'; 
	});

	rootMenu->Insert(std::move(pm::pl::getUserManagerSubMenu(isAdmin)));

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

std::unique_ptr<cli::Menu> pm::pl::getUserManagerSubMenu(const bool isAdmin)
{
	auto menu = std::make_unique<cli::Menu>("userManager");

	menu->Insert("list", [](std::ostream& out) { printAllUsers(out); });

	menu->Insert("ping", [](std::ostream& out)
		{
			std::cout << "User pong\n";
		});

	return menu;
}
