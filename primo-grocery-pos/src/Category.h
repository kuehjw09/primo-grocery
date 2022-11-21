#ifndef CATEGORY_H
#define CATEGORY_H

#include <list>
#include "Item.h"

class Category {
    public:
        Category(int id, std::string name): id(id), name(name) { }
    private:
        int id;
        std::string name;
        std::list<Item> items;

};

#endif