#include "../include/project_helper.h"
#include "../include/Category.h"

#include <ctime>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <cassert>

using namespace std;

const std::string getDateString()
{
    time_t now = time(0);
    struct tm tstruct;
#ifdef WIN32
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
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif
    return std::string(std::to_string(tstruct.tm_hour) + ":" + std::to_string(tstruct.tm_min) + ":" + std::to_string(tstruct.tm_sec));
}

void clearConsole()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
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

const int generateSaleId()
{
    // read id from file;
    std::ifstream inFS;
    unsigned id;
    inFS.open("../resources/id.txt");

    if (!inFS.is_open())
    {
        errClass error("Failed to Open File", 4);
        throw error;
    }

    inFS >> id;

    inFS.close();
    return ++id;
}

void incrementSaleId(const unsigned id)
{
    std::ofstream outFS;
    outFS.open("../resources/id.txt");

    outFS << id; // updating the id

    outFS.close();
}

void updateItemQuantities(std::list<SaleItem> saleItems)
{
    std::list<SaleItem>::iterator li = saleItems.begin();
    while (li != saleItems.end())
    {
        li->getItem()->decQuantity(li->getQty()); // updating the item quantities
        ++li;
    }
}

Item *getItemByID(std::string item_id, Inventory *inventory)
{
    Item *needle = nullptr;
    for (Category cat : inventory->categories)
        for (Item *item : cat.getItems())
            if (item_id == item->getId())
            {
                needle = item;
                break;
            }
    return needle;
}

/**
 * Return a list of unique dates on which a Sale occured.
 */
std::list<std::string> GetAllDatesInSales()
{
    list<string> dates;
    vector<string> tokens;
    string dateString = "";
    string currentDateString;

    ifstream inFS;

    inFS.open(salesFilePath);

    if (!inFS.is_open())
    {
        cout << "failed to open [" << salesFilePath << "]" << endl;
        assert(false);
    }

    string input;
    getline(inFS, input);

    while (!inFS.fail())
    {
        tokens = parseLine(input, '\t');
        currentDateString = tokens.at(1);

        if (currentDateString != dateString)
        { // adding only unique dates
            dates.push_back(currentDateString);
            dateString = currentDateString;
        }

        getline(inFS, input);
    }

    inFS.close();

    return dates;
}

/**
 * Return a list of SaleItem ids having date equal to dateString
 */
std::list<std::string> GetSaleIdByDate(std::string dateString)
{
    list<string> saleIds;
    vector<string> tokens;

    ifstream inFS;

    inFS.open(salesFilePath);

    if (!inFS.is_open())
    {
        cout << "failed to open [" << salesFilePath << "]" << endl;
        assert(false);
    }

    string input;
    getline(inFS, input);

    while (!inFS.fail())
    {
        tokens = parseLine(input, '\t');
        if (tokens.at(1) == dateString)      // match
            saleIds.push_back(tokens.at(0)); // sale ID

        getline(inFS, input);
    }
    inFS.close();

    return saleIds;
}
