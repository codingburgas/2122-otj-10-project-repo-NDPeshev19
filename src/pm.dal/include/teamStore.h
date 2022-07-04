#pragma once

#include "pch_dal.h"
#include "team.h"

namespace pm::dal
{
	void createTeam(std::string_view teamName, size_t creatorId);
	std::vector<pm::types::Team> retrieveAllTeams();

	pm::types::Team constructTeam(nanodbc::result& result);
}