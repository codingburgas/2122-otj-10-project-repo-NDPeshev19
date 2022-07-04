#include <iostream>
#include <memory>

#include "nanodbc\nanodbc.h"
#include "db.h"
#include "userStore.h"
#include "userManager.h"
#include "login.h"
#include "cli.h"

#include "tabulate/tabulate.hpp"

int main() try
{
	system("chcp 437");
	system("cls");

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