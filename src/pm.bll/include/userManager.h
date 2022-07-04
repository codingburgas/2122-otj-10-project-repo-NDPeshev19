#pragma once

#include "pch_bll.h"
#include "..\src\pm.types\include\user.h"

namespace pm::bll
{
	std::optional<pm::types::User> loginAsUser(
		std::string_view username, std::string_view password);

	bool isUserOriginAdmin(const pm::types::User& user);

	std::vector<pm::types::User> getAllUsers(bool includeDeleted);
	std::optional<pm::types::User> getUser(size_t id);
	void deleteUser(size_t userIdToDelete, size_t loggedUserId);
	void restoreUser(size_t userIdToRestore, size_t loggedUserId);
	void giveAdminPrivileges(size_t userIdToOp, size_t loggedUserId);
	void revokeAdminPrivileges(size_t userIdToDeOp, size_t loggedUserId);

	void addUser(const pm::types::User& user);
}