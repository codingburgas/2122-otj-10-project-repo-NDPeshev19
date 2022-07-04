#include "pch_utils.h"

#include "timeConv.h"

time_t pm::utils::toTimeT(const nanodbc::timestamp& ts)
{
	struct tm time;
	time.tm_year = ts.year - 1900;
	time.tm_mon = ts.month - 1;
	time.tm_mday = ts.day;
	time.tm_hour = ts.hour;
	time.tm_min = ts.min;
	time.tm_sec = ts.sec;

	time_t tsRes = mktime(&time);

	return tsRes;
}

std::string pm::utils::toString(time_t t)
{
	char buff[20];
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	strftime(buff, sizeof(buff), "%b %d %H:%M", timeinfo);

	return std::string(buff);
}
