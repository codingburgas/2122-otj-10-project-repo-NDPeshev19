#include "pch_bll.h"

#include "userManager.h"
#include "userStore.h"

std::optional<pm::types::User> pm::bll::loginAsUser(
	const std::string_view username, const std::string_view password)
{
	return pm::dal::getUserLogin(username, password);
}

bool pm::bll::isUserOriginAdmin(const pm::types::User& user)
{
	return user.username == "admin";
}

std::vector<pm::types::User> pm::bll::getAllUsers(const bool includeDeleted)
{
	return includeDeleted ? 
		pm::dal::retrieveAllUsersWithDeleted() : 
		pm::dal::retrieveAllUsers();
}

std::optional<pm::types::User> pm::bll::getUser(size_t id)
{
	return pm::dal::retrieveUser(id);
}

void pm::bll::deleteUser(size_t userIdToDelete, size_t loggedUserId)
{
	auto user = pm::dal::retrieveUser(userIdToDelete);
	
	if (!user)
		throw std::runtime_error("User not found.");

	if (user->username == "admin")
		throw std::runtime_error("Cannot delete origin admin user.");

	if (user->id == loggedUserId)
		throw std::runtime_error("Cannot delete yourself.");

	pm::dal::deleteUser(userIdToDelete, loggedUserId);
}

void pm::bll::restoreUser(size_t userIdToRestore, size_t loggedUserId)
{
	auto user = pm::dal::retrieveUserWithDeleted(userIdToRestore);
	
	if (!user)
		throw std::runtime_error("User not found.");

	pm::dal::restoreUser(userIdToRestore, loggedUserId);
}

void pm::bll::giveAdminPrivileges(size_t userIdToOp, size_t loggedUserId)
{
	auto user = pm::dal::retrieveUser(userIdToOp);
	
	if (!user)
		throw std::runtime_error("User not found.");

	if (user->isAdmin == true)
		throw std::runtime_error("User is already admin");

	if (userIdToOp == loggedUserId)
		throw std::runtime_error("Cannot give admin privileges to yourself.");
	
	pm::dal::giveAdminPrivileges(userIdToOp, loggedUserId);
}

void pm::bll::revokeAdminPrivileges(size_t userIdToDeOp, size_t loggedUserId)
{
	auto user = pm::dal::retrieveUser(userIdToDeOp);
	
	if (!user)
		throw std::runtime_error("User not found.");

	if (user->isAdmin == false)
		throw std::runtime_error("User is already not admin");

	if (userIdToDeOp == loggedUserId)
		throw std::runtime_error("Cannot revoke admin " 
			"privileges from yourself.");

	pm::dal::revokeAdminPrivileges(userIdToDeOp, loggedUserId);
}

void pm::bll::changePassword(
	size_t userId, std::string_view newPassword, size_t loggedUserId)
{
	auto user = pm::dal::retrieveUser(userId);
	
	if (!user)
		throw std::runtime_error("User not found.");

	pm::dal::changePassword(userId, newPassword, loggedUserId);
}

void pm::bll::addUser(const pm::types::User& user)
{
	pm::dal::createUser(user);
}
