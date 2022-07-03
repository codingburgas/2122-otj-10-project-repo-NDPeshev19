#pragma once

#include "pch_dal.h"

// FIXME:
#include "..\src\pm.types\include\user.h"

namespace pm::dal
{
	void ensureAdminUser();
	bool checkForAdminUser();
	
	void createUser(const pm::types::User& user);
}