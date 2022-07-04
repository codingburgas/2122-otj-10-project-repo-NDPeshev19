#pragma once

#include "pch_dal.h"
#include "team.h"

namespace pm::dal
{
	void createTeam(std::string_view teamName, size_t creatorId);
	std::vector<pm::types::Team> retrieveAllTeams();
	std::optional<pm::types::Team> retrieveTeam(std::string_view teamName);
	void deleteTeam(std::string_view teamName);

	void assignUser(size_t userId, size_t teamId);

	pm::types::Team constructTeam(nanodbc::result& result);
}