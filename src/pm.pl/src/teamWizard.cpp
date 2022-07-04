#include "teamWizard.h"

#include "timeConv.h"

void pm::pl::printAllTeams(std::ostream& out)
{
	tabulate::Table table;
	
	table.add_row({ "Id", "Name", "Date of creation", "Id of creator",
		"Date of last change", "Id of last changer" });

	auto teams = pm::bll::getAllTeams();

	for (const auto& team : teams)
	{
		table.add_row({ std::to_string(team.id), team.name,
			pm::utils::toString(team.dateOfCreation),
			std::to_string(team.IdOfCreator),
			pm::utils::toString(team.dateOfLastChange), 
			std::to_string(team.idOfLastChanger) });
	}

	table[0].format()
		.font_color(tabulate::Color::yellow)
		.font_align(tabulate::FontAlign::center);

	out << table << '\n';
}
