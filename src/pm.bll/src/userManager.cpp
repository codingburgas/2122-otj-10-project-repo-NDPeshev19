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

void pm::bll::addUser(const pm::types::User& user)
{
	pm::dal::createUser(user);
}
