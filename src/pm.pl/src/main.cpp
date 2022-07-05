#include "userStore.h"

#include "login.h"
#include "cli.h"

#include <iostream>

int main() 
try
{
	pm::dal::ensureAdminUser();
	
	auto loggedUser = pm::pl::login();

	pm::pl::cli(pm::pl::getMenu(loggedUser.isAdmin, loggedUser.id));

	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}