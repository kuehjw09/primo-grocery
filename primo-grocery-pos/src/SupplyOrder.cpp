#include "../include/SupplyOrder.h"
#include "../include/Category.h"
#include "../include/project_helper.h"
using namespace std;
//using std::cout;  
//using std::endl;
//using std::setw;
void SupplyOrder::processDelivery(Inventory *inventory)
{
    if (this->wasProcessed())
        return;

    Item *needle = getItemByID(this->getOrderedID(), inventory);
    needle->setQuantity(needle->getQuantity() + this->getQuantity());

    if (!inventory->writeInventoryToFile())
        return;
    this->setProcessed();
}

std::string SupplyOrder::asFileString() const
{
    std::stringstream ss;

    ss << this->getOrderedID() << "\t";
    ss << this->getQuantity() << "\t";
    ss << this->getDatePlaced() << "\t";
    ss << this->getSupplier().getID() << "\t";
    ss << "\n";

    return ss.str();
}

void SupplyOrder::print()
{
    cout << std::left << setw(8) << (std::to_string(this->getQuantity()) + "x") << " ";
    cout << setw(12) << std::left << this->getOrderedID() << " ";
    cout << setw(12) << std::left << this->getDatePlaced() << " ";
    cout << setw(32) << std::left << ("\'" + this->getSupplier().getName() + "\'") << " ";
    cout << setw(48) << std::left << this->supplier.getAddress() << " ";
    cout << setw(16) << std::left << this->supplier.getPhone() << " ";
    cout << setw(16) << std::left << this->supplier.getEmail() << endl;
}