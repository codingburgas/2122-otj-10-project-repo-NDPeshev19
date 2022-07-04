#pragma once

#include "pch_dal.h"
#include "user.h"
#include "team.h"

namespace pm::dal
{
	void createTeam(std::string_view teamName, size_t creatorId);
	std::vector<pm::types::Team> retrieveAllTeams();
	std::optional<pm::types::Team> retrieveTeam(std::string_view teamName);
	std::optional<pm::types::Team> retrieveTeam(size_t teamId);
	void deleteTeam(std::string_view teamName);

	void assignUser(size_t userId, size_t teamId);
	void unAssignUser(size_t userId, size_t teamId);

	std::vector<pm::types::Team> retrieveUserTeams(size_t userId);
	std::vector<pm::types::User> retrieveTeamUsers(size_t teamId);
	
	void renameTeam(
		size_t teamId, std::string_view newName, size_t loggedUserId);

	pm::types::Team constructTeam(nanodbc::result& result);
}