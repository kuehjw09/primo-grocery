#include <iostream>
#include <fstream>

#include "../include/SupplierTransaction.h"
#include "../include/SupplyOrder.h"
#include "../include/Item.h"
#include "../include/project_helper.h"

using std::cout, std::cin, std::endl, std::setw;

vector<SupplyOrder> readTransactions(string path = ordersFilePath);

void SupplierTransaction::displayMenu()
{
    int choice = -1;
    while (choice != 0 && choice != 1)
    {
        clearConsole();
        cout << "Supplier Transaction" << endl;
        cout << "Enter 0 to EXIT" << endl;
        cout << "Enter 1 to View Previous Supply Orders" << endl;
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
    }

    clearConsole();
    displayMenu();
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