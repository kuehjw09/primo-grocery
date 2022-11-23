#ifndef CATEGORY_H
#define CATEGORY_H

#include <list>
#include "Item.h"

class Category {
    public:
        Category(int id, std::string name): id(id), name(name) { }

        void displayItems();
        std::string asFileString();

        Item* getItemAtMenuIndex(int index);

        void addItem(Item* item) {
            items.push_back(item);
        }

        static void print_header() {
            std::cout << "--------------------------------------------------------------" << std::endl;
            std::cout << std::left << std::setw(30) << "Item Name" << " ";
            std::cout << std::setw(10) << std::left << "ID" << " ";
            std::cout << std::setw(10) << std::left << "Price" << " ";
            std::cout << std::setw(10) << std::left << "Quantity" << std::endl;
            std::cout << "--------------------------------------------------------------" << std::endl;
        }

        int getId() const { return id; }
        std::string getName() const { return name; }
        int numItems() const { return items.size(); }
        std::list<Item*> getItems() const { return items; }

    private:
        int id;
        std::string name;
        std::list<Item*> items;
};

#endif