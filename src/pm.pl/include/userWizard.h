#pragma once

#include "userManager.h"

namespace pm::pl
{
	void printAllUsers(std::ostream& out, bool includeDeleted);
	tabulate::Table getUsersTable(std::vector<pm::types::User> users);
}