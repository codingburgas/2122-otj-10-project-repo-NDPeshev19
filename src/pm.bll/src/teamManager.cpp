#include "pch_bll.h"

#include "teamManager.h"

#include "userStore.h"
#include "teamStore.h"

void pm::bll::addTeam(std::string_view teamName, size_t loggedUserId)
{
	if (teamName.empty())
		throw std::runtime_error("Team name can not be empty");

	pm::dal::createTeam(teamName, loggedUserId);
}

std::vector<pm::types::Team> pm::bll::getAllTeams()
{
	return pm::dal::retrieveAllTeams();
}

std::optional<pm::types::Team> pm::bll::retrieveTeam(std::string_view teamName)
{
	return pm::dal::retrieveTeam(teamName);
}

void pm::bll::assignUser(std::string_view username, std::string_view teamName)
{
	auto user = pm::dal::retrieveUser(username);
	auto team = pm::dal::retrieveTeam(teamName);
	
	if (!user)
		throw std::runtime_error("User not found");
	if (!team)
		throw std::runtime_error("Team not found");

	pm::dal::assignUser(user->id, team->id);
}

void pm::bll::deleteTeam(std::string_view teamName)
{
	pm::dal::deleteTeam(teamName);
}
