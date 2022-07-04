#pragma once

#include "userWizard.h"

#include "userManager.h"
#include "teamManager.h"

#include "cli\cli.h"
#include "cli\clilocalsession.h"
#include "cli\loopscheduler.h"

#include <memory>

namespace pm::pl
{
	std::unique_ptr<cli::Menu> getUserManagerSubMenu(
		bool isAdmin, size_t loggedUserId);
}