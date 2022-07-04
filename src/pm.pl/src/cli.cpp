#include "cli.h"

#include "userWizard.h"
#include "teamWizard.h"

std::unique_ptr<cli::Menu> pm::pl::getMenu(const bool isAdmin, 
	const size_t loggedUserId)
{
	auto rootMenu =  std::make_unique<cli::Menu>("main");
	
	rootMenu->Insert("shutdown", 
		[](std::ostream& out)
		{
				std::cout << "Goodbye!\n";
				exit(0);
		});
	
	rootMenu->Insert("cls",
		[](std::ostream& out)
		{
			system("cls");
		}, "Clear screen");

	rootMenu->Insert("ping", 
		[](std::ostream& out) 
		{
			std::cout << "pong" << '\n'; 
		});


	rootMenu->Insert("beep", 
		[](std::ostream& out)
		{
			out << '\a';
		});

	rootMenu->Insert(std::move(getUserManagerSubMenu(isAdmin, loggedUserId)));
	rootMenu->Insert(std::move(getTeamManagerSubMenu(isAdmin, loggedUserId)));

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
			out << "An error occured:\n\"" << e.what()
				<< "\"\n with command: " << cmd << ".\n";
		}
	);

	cli::LoopScheduler scheduler;
	cli::CliLocalTerminalSession localSession(cli, scheduler, std::cout);

	scheduler.Post([] {std::cout << "Welcome to the Project Manager!\n"; });
	
	scheduler.Run();
}