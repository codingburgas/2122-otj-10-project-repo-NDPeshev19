#pragma once

#include "pch_types.h"

namespace pm::types
{
	using std::string;
	using std::string_view;
	
	struct User
	{
		size_t id{};
		string username;
		string password;
		string firstName;
		string lastName;
		time_t dateOfCreation{};
		size_t idOfCreator{};
		time_t dateOfLastChange{};
		size_t idOfLastChanger{};
		bool isDeleted{};
		bool isAdmin{};

		User(const string_view t_username,
			const string_view t_password, const string_view t_firstName,
			const string_view t_lastName, const time_t t_dateOfCreation,
			const size_t t_idOfCreator, const time_t t_dateOfLastChange,
			const size_t t_idOfLastChanger,
			const bool t_isDeleted, const bool t_isAdmin)
			:
			username(t_username), password(t_password),
			firstName(t_firstName), lastName(t_lastName),
			dateOfCreation(t_dateOfCreation), idOfCreator(t_idOfCreator),
			dateOfLastChange(t_dateOfLastChange),
			idOfLastChanger(t_idOfLastChanger),
			isDeleted(t_isDeleted), isAdmin(t_isAdmin)
		{}

		User(const size_t t_id, const string_view t_username, 
			const string_view t_password, const string_view t_firstName, 
			const string_view t_lastName, const time_t t_dateOfCreation, 
			const size_t t_idOfCreator, const time_t t_dateOfLastChange, 
			const size_t t_idOfLastChanger, 
			const bool t_isDeleted, const bool t_isAdmin)
			:
			id(t_id), username(t_username), password(t_password),
			firstName(t_firstName), lastName(t_lastName),
			dateOfCreation(t_dateOfCreation), idOfCreator(t_idOfCreator),
			dateOfLastChange(t_dateOfLastChange), 
			idOfLastChanger(t_idOfLastChanger), 
			isDeleted(t_isDeleted), isAdmin(t_isAdmin)
		{}
	};
}
