#include "pch_dal.h"

#include "db.h"

DB& DB::get()
{
	static DB db;

	return db;
}

nanodbc::connection& DB::conn()
{
	return m_conn;
}

DB::DB()
	: m_conn(
		"Driver={ODBC Driver 17 for SQL Server};"
		"Server=LECOMP\\SQLEXPRESS;"
		"Database=test;"
		"Trusted_Connection=yes;")
{  }
