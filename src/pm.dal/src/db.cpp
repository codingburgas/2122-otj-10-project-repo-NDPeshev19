#include "pch_dal.h"

#include "db.h"
#include "userStore.h"

pm::dal::DB& pm::dal::DB::get()
{
	static pm::dal::DB db;

	return db;
}

nanodbc::connection& pm::dal::DB::conn()
{
	return m_conn;
}

pm::dal::DB::DB()
	: m_conn(
		"Driver={ODBC Driver 17 for SQL Server};"
		"Server=LECOMP\\SQLEXPRESS;"
		"Database=pmdb;"
		"Trusted_Connection=yes;")
{}
