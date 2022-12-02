#include "../include/Category.h"
#include <fstream>

std::string Category::itemsFilePath = "../resources/items.txt";

std::vector<Category> Category::categories = {
    Category(1, "Beverages"),
    Category(2, "Bread & Bakery"),
    Category(3, "Breakfast & Cereal"),
    Category(4, "Cookies, Snacks & Candy"),
    Category(5, "Dairy, Eggs & Cheese"),
    Category(6, "Produce"),
    Category(7, "Grains, Pasta & Sides"),
    Category(8, "Meat & Seafood"),
    Category(9, "Miscellaneous"),
    Category(10, "Paper Products"),
    Category(11, "Pet Care"),
    Category(12, "Pharmacy")
 };

bool Category::writeAllItems(std::string path) {
    std::ofstream itemsOut;
    itemsOut.open(path, std::ios::out);
    if (!itemsOut.is_open()) {
        std::cout << "Unable to write to items file! [" << path << "]" << std::endl;
        return false;
    }

    for (Category cat : Category::categories) itemsOut << cat.asFileString();

    return true;
}

void Category::displayItems() {
    print_header();

    int count = 0;
    std::list<Item*>::iterator i;
    for (i = items.begin(); i != items.end(); i++) {
        (*i)->print(count);
        count++;
    }
}

std::string Category::asFileString() {
    std::string result = "";
    for (Item* i : items) {
        result += i->asFileLine();
    }
    return result;
}

Item* Category::getItemAtMenuIndex(int index) {
    Item* found;
    int count = 0;

    if (index < items.size())
        for (Item* i : items) {
            if (count == index) {
                found = i;
                break;
            }
            count++;
        }

    return found;
}
