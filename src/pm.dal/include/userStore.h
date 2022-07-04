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

	std::vector<pm::types::User> retrieveAllUsers();
	std::vector<pm::types::User> retrieveAllUsersWithDeleted();

	std::vector<pm::types::User> extractUsersimpl(nanodbc::result result);
	void createUser(const pm::types::User& user);

	pm::types::User constructUser(nanodbc::result& conn);
}