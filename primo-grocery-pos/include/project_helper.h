#pragma once

#include "Category.h"
#include <string>
#include <vector>
#include <ctime>

const std::string getDateString();

const std::string getTimeString();

void clearConsole();

std::vector<std::string> parseLine(std::string &s, char delim);

const std::string getCategoryName(int catId);
