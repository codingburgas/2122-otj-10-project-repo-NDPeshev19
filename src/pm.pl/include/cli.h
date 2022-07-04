#pragma once

#include "cli\cli.h"
#include "cli\clilocalsession.h"
#include "cli\loopscheduler.h"

#include <memory>

namespace pm::pl
{
	std::unique_ptr<cli::Menu> getMenu(bool isAdmin);
	void cli(std::unique_ptr<cli::Menu> menu);
	
	std::unique_ptr<cli::Menu> getUserManagerSubMenu(bool isAdmin);
}