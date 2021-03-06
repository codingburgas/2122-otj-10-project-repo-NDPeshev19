#pragma once

#include "userManager.h"
#include "teamManager.h"

#include "userMenu.h"
#include "teamMenu.h"

#include "cli\cli.h"
#include "cli\clilocalsession.h"
#include "cli\loopscheduler.h"

#include <memory>

namespace pm::pl
{
	std::unique_ptr<cli::Menu> getMenu(bool isAdmin, size_t loggedUserId);
	void cli(std::unique_ptr<cli::Menu> menu);
}