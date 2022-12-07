#include "../include/Item.h"

Item::Item(std::vector<std::string> props) : name(props.at(1)), id(props.at(0)), restockQuantity(stoi(props.at(4))), price(stod(props.at(2))), quantity(stoi(props.at(3)))
{
    std::string str = (props.size() > 5) ? props.at(5) : ""; // check whether units are defined
    units = str;
}

std::string Item::asFileLine()
{
    std::stringstream ss;

    ss << id << "\t";
    ss << name << "\t";
    ss << price << "\t";
    ss << quantity << "\t";
    ss << restockQuantity << "\t";
    ss << units;
    ss << "\n";

    return ss.str();
}

void Item::print(int index)
{
    std::string fmtname = (index == -1) ? "" : std::to_string(index + 1) + ": ";
    std::cout << std::setw(30) << (fmtname + this->getName()) << " ";
    std::cout << std::setw(10) << std::left << this->getId() << " ";
    std::cout << std::setw(10) << std::fixed << std::setprecision(2) << this->getPrice() << " ";
    std::cout << std::setw(10) << this->getQuantity() << std::endl;
}

void Item::decQuantity(int amount)
{
    this->quantity -= amount;
}