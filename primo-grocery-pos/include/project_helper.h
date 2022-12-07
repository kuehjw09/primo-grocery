#pragma once

#include "Category.h"
#include "Item.h"
#include "SaleItem.h"
#include "Inventory.h"
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <vector>

const std::string getDateString();

const std::string getTimeString();

void clearConsole();

const std::string getCategoryName(int catId);

const int generateSaleId(); // get unique unsigned int for use as sale identifier

void incrementSaleId(unsigned id);

void updateItemQuantities(list<SaleItem> saleItems);

Item* getItemByID(std::string item_id, Inventory* inventory);

std::vector<std::string> parseLine(std::string &s, char delim);

const string ordersFilePath = "../resources/orders.txt";
