#include "login.h"

#include "userManager.h"
#include "asteriskInput.h"

pm::types::User pm::pl::login()
{
	std::string username;
	std::string password;

	login:

	std::cout << "Username:\n";
	getline(std::cin, username);
	
	pm::utils::PasswordField passwordField("  ", 1, 2);
	std::cout << "Password:\n";
	password = passwordField.getline();

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
