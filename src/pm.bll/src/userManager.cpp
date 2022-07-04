#include "pch_bll.h"

#include "userManager.h"
#include "userStore.h"

std::optional<pm::types::User> pm::bll::loginAsUser(
	const std::string_view username, const std::string_view password)
{
	return pm::dal::getUserLogin(username, password);
}
