#include <iostream>

#include "nanodbc\nanodbc.h"
#include "db.h"
#include "userStore.h"

#include "..\src\pm.utils\include\md5.h"

int main() try
{
	pm::dal::ensureAdminUser();
	
	return EXIT_SUCCESS;
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}