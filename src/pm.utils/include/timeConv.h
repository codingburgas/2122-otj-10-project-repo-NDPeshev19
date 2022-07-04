#pragma once

#include "pch_utils.h"

namespace pm::utils
{
	time_t toTimeT(const nanodbc::timestamp& ts);
}