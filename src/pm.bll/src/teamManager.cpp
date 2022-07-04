#include "pch_bll.h"

#include "teamManager.h"
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

void pm::bll::deleteTeam(std::string_view teamName)
{
	pm::dal::deleteTeam(teamName);
}
