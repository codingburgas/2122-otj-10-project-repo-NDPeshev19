#pragma once

#include "pch_bll.h"
#include "team.h"

namespace pm::bll
{
	void addTeam(std::string_view teamName, size_t loggedUserId);
	std::vector<pm::types::Team> getAllTeams();
}