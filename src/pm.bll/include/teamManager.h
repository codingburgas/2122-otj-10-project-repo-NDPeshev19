#pragma once

#include "pch_bll.h"
#include "team.h"

namespace pm::bll
{
	void addTeam(std::string_view teamName, size_t loggedUserId);
	std::vector<pm::types::Team> getAllTeams();
	std::optional<pm::types::Team> retrieveTeam(std::string_view teamName);
	void assignUser(std::string_view username, std::string_view teamName);
	
	void deleteTeam(std::string_view teamName);
}