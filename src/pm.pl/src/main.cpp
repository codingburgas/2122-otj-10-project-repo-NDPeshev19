#include <iostream>

#include "nanodbc\nanodbc.h"
#include "db.h"
#include "userStore.h"
#include "userManager.h"
#include "login.h"

#include "..\src\pm.utils\include\md5.h"

int main() try
{
	pm::dal::ensureAdminUser();

	auto user = pm::pl::login();

	std::cout << "Mnogo si gotin :)\n";
	
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}