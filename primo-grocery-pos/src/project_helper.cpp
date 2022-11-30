#include "../include/project_helper.h"
#include "../include/Category.h"

#include <ctime>
#include <time.h>

using namespace std;

const std::string getDateString()
{
    time_t now = time(0);
    struct tm tstruct;
#ifdef WIN32
#include <windows.h>
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif
    return std::string(std::to_string(tstruct.tm_mon + 1) + "/" + std::to_string(tstruct.tm_mday) + "/" + std::to_string(tstruct.tm_year + 1900));
}

const std::string getTimeString()
{
    time_t now = time(0);
    struct tm tstruct;
#ifdef WIN32
#include <windows.h>
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif
    return std::string(std::to_string(tstruct.tm_hour) + ":" + std::to_string(tstruct.tm_min) + ":" + std::to_string(tstruct.tm_sec));
}

void clearConsole()
{
#ifdef WIN32
#include <windows.h>
    system("cls");
#else
    system("clear");
#endif
}

vector<std::string> parseLine(string &s, char delim)
{
    vector<string> elems;
    stringstream ss;
    ss.str(s);

    string elem;
    while (getline(ss, elem, delim))
    {
        elems.push_back(elem);
    }

    return elems;
}

const std::string getCategoryName(int catId)
{
    std::string categoryNames[12] = {
        "Beverages",
        "Bread & Bakery",
        "Breakfast & Cereal",
        "Cookies, Snacks & Candy",
        "Dairy, Eggs & Cheese",
        "Produce",
        "Grains, Pasta & Sides",
        "Meat & Seafood",
        "Miscellaneous",
        "Paper Products",
        "Pet Care",
        "Pharmacy"};
    return categoryNames[catId - 1];
}
