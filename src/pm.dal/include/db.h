#pragma once

#include "pch_dal.h"

namespace pm::dal
{
	class DB
	{
	public:
		static DB& get();
		nanodbc::connection& conn();

		DB(const DB&) = delete;
		void operator=(const DB&) = delete;

	private:
		DB();

		nanodbc::connection m_conn;
	};
}
