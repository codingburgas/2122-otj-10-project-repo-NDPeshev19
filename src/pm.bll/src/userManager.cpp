#include "pch_bll.h"

#include "userManager.h"
#include "userStore.h"

std::optional<pm::types::User> pm::bll::loginAsUser(
	const std::string_view username, const std::string_view password)
{
	return pm::dal::getUserLogin(username, password);
}

std::vector<pm::types::User> pm::bll::getAllUsers(const bool includeDeleted)
{
	return includeDeleted ? 
		pm::dal::retrieveAllUsersWithDeleted() : 
		pm::dal::retrieveAllUsers();
}

void pm::bll::addUser(const pm::types::User& user)
{
	pm::dal::createUser(user);
}
