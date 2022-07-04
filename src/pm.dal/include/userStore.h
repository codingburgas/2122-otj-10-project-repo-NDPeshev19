#pragma once

#include "pch_dal.h"

// FIXME:
#include "..\src\pm.types\include\user.h"

namespace pm::dal
{
	void ensureAdminUser();
	bool checkForAdminUser();
	
	std::optional<pm::types::User> getUserLogin(std::string_view username,
		std::string_view password);

	void createUser(const pm::types::User& user);
}