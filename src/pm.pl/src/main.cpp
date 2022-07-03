#include <iostream>

#include "nanodbc\nanodbc.h"
#include "db.h"


int main() try
{
    auto conn = pm::dal::DB::get().conn();

    auto result = nanodbc::execute(conn, "SELECT i FROM t;");
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