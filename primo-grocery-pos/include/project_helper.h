#pragma once

#include "Category.h"
#include "SaleItem.h"
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

const std::string getDateString();

const std::string getTimeString();

void clearConsole();

std::vector<std::string> parseLine(std::string &s, char delim);

const std::string getCategoryName(int catId);

const int generateSaleId(); // get unique unsigned int for use as sale identifier

void incrementSaleId(unsigned id);

void updateItemQuantities(list<SaleItem> saleItems);