#pragma once

#include "pch_types.h"

namespace pm::types
{
	struct Team
	{
		size_t id{};
		std::string name;
		time_t dateOfCreation{};
		size_t IdOfCreator{};
		time_t dateOfLastChange{};
		size_t idOfLastChanger{};
		
		Team() = default;

		Team(size_t id, std::string name, 
			time_t dateOfCreation, size_t IdOfCreator, 
			time_t dateOfLastChange, size_t idOfLastChanger)
			: id(id), name(name), 
			dateOfCreation(dateOfCreation), IdOfCreator(IdOfCreator), 
			dateOfLastChange(dateOfLastChange), idOfLastChanger(idOfLastChanger)
		{}
	};
}