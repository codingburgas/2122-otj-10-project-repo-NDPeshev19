#include <iostream>

#include "nanodbc\nanodbc.h"
#include "db.h"
#include "userStore.h"
#include "userManager.h"

#include "..\src\pm.utils\include\md5.h"

int main() try
{
	pm::dal::ensureAdminUser();

	auto user = pm::bll::loginAsUser("admsin", "adminpass");

	if (user)
		std::cout << user->username << '\n';
	else
		std::cout << "Failed";
	
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}