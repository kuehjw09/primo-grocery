#include "../include/SupplyOrder.h"
#include "../include/Category.h"
#include "../include/project_helper.h"

using std::cout, std::endl, std::setw;

void SupplyOrder::processDelivery() {
    if (processed) return;

    Item* needle = getItemByID(this->getOrderedID());
    needle->setQty(needle->getQty() + this->getQuantity());

    if (!Category::writeAllItems()) return;
    this->processed = true;
}

std::string SupplyOrder::asFileString() const {
    std::stringstream ss;

    ss << this->getOrderedID() << "\t";
    ss << this->getQuantity() << "\t";
    ss << this->getDatePlaced() << "\t";
    ss << this->getSupplier() << "\t";
    ss << this->getAddress() << "\t";
    ss << this->getPhone() << "\t";
    ss << this->getEmail();
    ss << "\n";

    return ss.str();
}

void SupplyOrder::print() {
    cout << std::left << setw(8) << (std::to_string(this->getQuantity()) + "x") << " ";
    cout << setw(12) << std::left << this->getOrderedID() << " ";
    cout << setw(12) << std::left << this->getDatePlaced() << " ";
    cout << setw(32) << std::left << ("\'" + this->getSupplier() + "\'") << " ";
    cout << setw(48) << std::left << this->getAddress() << " ";
    cout << setw(16) << std::left << this->getPhone() << " ";
    cout << setw(16) << std::left << this->getEmail() << endl;
}