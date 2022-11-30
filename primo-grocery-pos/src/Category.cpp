#include "../include/Category.h"

void Category::displayItems()
{
    print_header();

    int count = 0;
    std::list<Item *>::iterator i;
    for (i = items.begin(); i != items.end(); i++)
    {
        (*i)->print(count);
        count++;
    }
}

std::string Category::asFileString()
{
    std::string result = "";
    for (Item *i : items)
    {
        result += i->asFileLine();
    }
    return result;
}

Item *Category::getItemAtMenuIndex(int index)
{
    Item *found;
    int count = 0;

    if (index < items.size())
        for (Item *i : items)
        {
            if (count == index)
            {
                found = i;
                break;
            }
            count++;
        }

    return found;
}
