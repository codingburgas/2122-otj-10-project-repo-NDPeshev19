#pragma once

#include "pch_types.h"
// #include "timeConv.h"
#include "..\..\pm.utils\include\timeConv.h"

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

		User() = default;

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

		std::string toString() const
		{
			return std::to_string(id) + " " +
				username + password + firstName + lastName + " " +
				pm::utils::toString(dateOfCreation) + " " +
				std::to_string(idOfCreator) + " " +
				pm::utils::toString(dateOfLastChange) + " " +
				std::to_string(idOfLastChanger) + " " +
				std::to_string(isDeleted) + " " +
				std::to_string(isAdmin);
		}

		std::string toPrettyString() const
		{
			return "Id: " + std::to_string(id) + '\n' +
				"Username: " + username + '\n' +
				"Password hash: " + password + '\n' +
				"First name: " + firstName +
				"\nLast name: " + lastName + '\n' +
				"Date of creation: " + pm::utils::toString(dateOfCreation) + 
				"\nId of creator: " + std::to_string(idOfCreator) + '\n' +
				"Date of last change: " + pm::utils::toString(dateOfLastChange) +
				"\nId of last changer: " + std::to_string(idOfLastChanger) +
				"\nIs admin: " + std::to_string(isAdmin);
		}
	};
}
