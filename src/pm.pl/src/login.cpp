#include "login.h"

#include "userManager.h"

pm::types::User pm::pl::login()
{
	std::string username;
	std::string password;

	login:

	std::cout << "Username:\n";
	getline(std::cin, username);
	std::cout << "Password:\n";
	getline(std::cin, password);

	if (auto user = pm::bll::loginAsUser(username, password);
		user)
	{
		return *user;
	}
	else
	{
		std::cout << "Invalid username or password.\n";
		goto login;
	}
}
