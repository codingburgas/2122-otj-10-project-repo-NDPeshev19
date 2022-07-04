#pragma once

#include "pch_bll.h"
#include "..\src\pm.types\include\user.h"

namespace pm::bll
{
	std::optional<pm::types::User> loginAsUser(
		std::string_view username, std::string_view password);

	std::vector<pm::types::User> getAllUsers();

	void addUser(const pm::types::User& user);
}