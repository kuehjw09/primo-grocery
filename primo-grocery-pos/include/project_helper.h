#pragma once 

#include "Category.h"
#include "Item.h"

#include <string>
#include <ctime>
#include <vector>

const std::string getDateString();

const std::string getTimeString();

void clearConsole();

const std::string getCategoryName(int catId);

Item* getItemByID(std::string item_id);

std::vector<std::string> parseLine(std::string &s, char delim);