#pragma once

#include "pch_utils.h"

template <typename T>
T& lvalue_cast(T&& val) {
	return val;
}