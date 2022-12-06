#include <iostream>
#include <fstream>

#include "../include/SupplierTransaction.h"
#include "../include/SupplyOrder.h"
#include "../include/Item.h"
#include "../include/project_helper.h"

using std::cout, std::cin, std::endl, std::setw;

const string ordersFilePath = "../resources/orders.txt";

vector<SupplyOrder> readTransactions(string path = ordersFilePath);
bool appendTransactionToFile(SupplyOrder supply_order, string path);

void SupplierTransaction::displayMenu()
{
    int choice = -1;
    while (choice < 0 || choice > 3)
    {
        clearConsole();
        cout << "Supplier Transaction" << endl;
        cout << "Enter 0 to EXIT" << endl;
        cout << "Enter 1 to View Previous Transactions" << endl;
        cout << "Enter 2 to View Items to Restock (# ITEMS)" << endl; // TODO: Add count of items that need to be restocked
        cout << "Enter 3 to Restock an Item by Item Code" << endl;
        cout << endl
             << "Enter your choice ---> ";

        cin >> choice;
    }

    switch (choice)
    {
    case 0:
        clearConsole();
        return;
    case 1:
        displayHistoryMenu();
        break;
    case 2:
        displayRestockingMenu();
        break;
    case 3:
        displayRestockingMenu(1);
        break;
    }

    clearConsole();
    displayMenu();
}

// TODO: Add variable quantity thresholds to items
// TODO: Show a summary/confirmation when stock is ordered
void SupplierTransaction::displayRestockingMenu(int mode)
{
    Item *selected = nullptr;
    cout << " " << endl;
    clearConsole();

    if (mode == 0)
    {
        vector<Item *> belowThreshold;
        for (Category cat : inventory->categories)
        {
            for (Item *i : cat.getItems())
                if (i->isBelowThreshold())
                    belowThreshold.push_back(i);
        }

        std::cout << "---------------------------------------------------------------" << std::endl;
        std::cout << std::left << std::setw(30) << "Item Name"
                  << " ";
        std::cout << std::setw(10) << std::left << "ID"
                  << " ";
        std::cout << std::setw(10) << std::left << "Cost"
                  << " ";
        std::cout << std::setw(10) << std::left << "Quantity"
                  << " " << endl;
        std::cout << "---------------------------------------------------------------" << std::endl;

        int index = 0;
        for (Item *i : belowThreshold)
        {
            i->print(index);
            index++;
        }

        cout << endl
             << "Input the index of the item to restock, or 0 to EXIT ---> ";
        int selectedIndex;
        cin >> selectedIndex;

        if (selectedIndex == 0)
            return;

        selected = belowThreshold[selectedIndex - 1];
    }
    else if (mode == 1)
    {
        while (selected == nullptr)
        {
            string itemCode;
            cout << "Input the Item ID of the item to restock, or 0 to EXIT ---> ";
            cin >> itemCode;

            if (itemCode == "0")
                return;

            selected = getItemByID(itemCode, inventory);
        }
    }

    clearConsole();

    cout << "Current stock of \'" << selected->getName() << "\' is " << selected->getQuantity() << endl;
    cout << "Input the quantity of \'" << selected->getName() << "\' that you would like to re-order ---> ";
    int desiredQuantity;
    cin >> desiredQuantity;

    SupplyOrder order(selected->getId(), desiredQuantity, "DATE", "SUPPLIER_NAME", "1234 ADDRESS ROAD", "+1(123)1234567", "SUPPLIER@SUPPLIERWEBSITE.COM");

    appendTransactionToFile(order, ordersFilePath);
    order.processDelivery(inventory);
}

bool appendTransactionToFile(SupplyOrder supply_order, string path)
{
    std::ofstream supplyOrdersOut;
    supplyOrdersOut.open(path, std::ios::out | std::ios::app);
    if (!supplyOrdersOut.is_open())
    {
        cout << "Unable to write to orders file! [" << path << "]" << endl;
        return false;
    }

    supplyOrdersOut << supply_order.asFileString();

    return true;
}

void SupplierTransaction::displayHistoryMenu()
{
    clearConsole();
    vector<SupplyOrder> orders = readTransactions(ordersFilePath);

    if (orders.size() != 0)
    {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        cout << std::left << setw(8) << "Amount"
             << " ";
        cout << setw(12) << std::left << "Item ID"
             << " ";
        cout << setw(12) << std::left << "Date"
             << " ";
        cout << setw(32) << std::left << "Supplier"
             << " ";
        cout << setw(48) << std::left << "Address"
             << " ";
        cout << setw(16) << std::left << "Phone"
             << " ";
        cout << setw(16) << std::left << "Email" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (SupplyOrder order : orders)
            order.print();
    }
    else
        cout << std::left << "There are currently no orders recorded!" << endl
             << "Create an order from the previous menu." << endl;

    cout << endl
         << "Enter anything to return to the previous menu ---> ";

    string returnstr;
    cin >> returnstr;
}

vector<SupplyOrder> readTransactions(string path)
{
    vector<SupplyOrder> orders;
    ifstream itemsFS;
    itemsFS.open(ordersFilePath);
    if (!itemsFS.is_open())
        return orders;

    string input;
    getline(itemsFS, input);
    while (!itemsFS.fail())
    {
        vector<string> tokens = parseLine(input, '\t');
        SupplyOrder order(tokens);
        orders.push_back(order);
        getline(itemsFS, input);
    }
    return orders;
}