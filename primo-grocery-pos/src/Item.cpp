#include "../include/Item.h"

std::string Item::asFileLine()
{
    std::stringstream ss;

    ss << id << "\t";
    ss << name << "\t";
    ss << price << "\t";
    ss << qty;
    ss << "\n";

    return ss.str();
}

void Item::print(int index)
{
    std::string fmtname = (index == -1) ? "" : std::to_string(index + 1) + ": ";
    std::cout << std::setw(30) << (fmtname + this->getName()) << " ";
    std::cout << std::setw(10) << std::left << this->getId() << " ";
    std::cout << std::setw(10) << std::fixed << std::setprecision(2) << this->getPrice() << " ";
    std::cout << std::setw(10) << this->getQty() << std::endl;
}

void Item::decQty(int amount)
{
    this->qty -= amount;

    // if qty falls below x --> generate sales receipt
}