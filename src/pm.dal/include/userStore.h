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
	std::optional<pm::types::User> retrieveUser(size_t userId);
	std::optional<pm::types::User> retrieveUser(std::string_view username);
	std::optional<pm::types::User> retrieveUserWithDeleted(size_t userId);
	void deleteUser(size_t userIdToDelete, size_t loggedUserId);
	void restoreUser(size_t userIdToRestore, size_t loggedUserId);
	void giveAdminPrivileges(size_t userIdToOp, size_t loggedUserId);
	void revokeAdminPrivileges(size_t userIdToDeOp, size_t loggedUserId);
	void changePassword(
		size_t userId, std::string_view newPassword, size_t loggedUserId);

	pm::types::User constructUser(nanodbc::result& conn);
}