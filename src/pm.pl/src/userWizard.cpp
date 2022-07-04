#include "userWizard.h"

#include <iostream>

namespace pm::pl
{
	void pm::pl::printAllUsers(std::ostream& out)
	{
		auto users = pm::bll::getAllUsers();

		for (const auto& user : users)
		{
			out << user.toPrettyString() << '\n' << std::string(47, '-') << '\n';
		}
	}
}