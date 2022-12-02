#include "../include/SaleItem.h"
#include "../include/project_helper.h"

void SaleItem::print(int index)
{
    std::string fmtname = (index == -1) ? "" : std::to_string(index + 1) + ": ";
    std::cout << std::setw(27) << (fmtname + this->getItem()->getName()) << " ";
    std::cout << std::setw(27) << getCategoryName((this->getItem()->getCategoryId())) << " ";
    std::cout << std::setw(10) << std::left << this->getQty() << " ";
    std::cout << std::setw(12) << std::fixed << std::setprecision(2) << this->item->getPrice() << " ";
    std::cout << std::setw(12) << std::fixed << std::setprecision(2) << this->getTotalPrice() << std::endl;
}

// SaleItem format to write to items-out.txt
std::string SaleItem::asFileLine()
{
    std::stringstream ss;

    ss << saleId << "\t";
    ss << item->getId() << "\t"; // item id
    ss << qty << "\t";
    ss << "\n";

    return ss.str();
}