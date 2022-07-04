#pragma once

#include "tabulate/tabulate.hpp"
#include "teamManager.h"

namespace pm::pl
{
	void printAllTeams(std::ostream& out);
	tabulate::Table createTable(std::vector<pm::types::Team> teams);
}