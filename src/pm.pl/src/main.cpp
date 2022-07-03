#include <iostream>

#include "nanodbc\nanodbc.h"


int main() try
{
    std::string connstr{ NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=LECOMP\\SQLEXPRESS;Database=test;Trusted_Connection=yes;") };
    nanodbc::connection conn(connstr);

    auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT i FROM t;"));
    while (result.next())
    {
        auto i = result.get<int>(0);
        std::cout << i << '\n';
    }
    return EXIT_SUCCESS;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}