#pragma once

#include "userManager.h"

namespace pm::pl
{
	void printAllUsers(std::ostream& out, bool includeDeleted);

	void addUser(std::ostream& out, size_t creatorId);
}