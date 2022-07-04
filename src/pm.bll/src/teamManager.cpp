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
