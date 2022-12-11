#include "../include/AdminTransaction.h"

#include <iostream>
#include "../include/project_helper.h"
#include "../include/SupplyOrder.h"
#include "../include/Sale.h"

using namespace std;

bool appendTransactionToFile(SupplyOrder supply_order, string path = ordersFilePath);

void AdminTransaction::displayMenu()
{
    char choice;

    do
    {
        clearConsole();
        cout << "\n\t\t\tPRIMO GROCERY\n";
        cout << "\n\tADMIN TRANSACTION\n";
        cout << "\t" << getDateString();
        cout << "\n\n\t************   Select an action   ***********\n";
        cout << "\n\t**             1.View Sales By Date        **" << endl;
        cout << "\t**             2.View Balance Sheet        **" << endl;
        cout << "\t**             3.Order Supplies            **" << endl;
        cout << "\t**             4.EXIT                      **" << endl;
        cout << "\n\t*********************************************\n";
        cout << "\n\tEnter your choice-----> ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            // display sales by date

            // TODO: call method in Inventory class to generate list of sales by date

            // display
            clearConsole();
            displaySalesByDateMenu();

            break;
        case '2':
            // display balance sheet
            clearConsole();
            displayBalanceSheet();

            // TODO: calculate total sales by date and total credit (delivery invoices) by date
            choice = '1';
            break;
        case '3':
            // display list of items needing restock
            clearConsole();
            cout << "Enter 0 to Return to the previous menu" << endl;
            cout << "Enter 1 to View low items to restock (" << inventory->getBelowThresholdQty().size() << " ITEMS)" << endl; // TODO: Add count of items that need to be restocked
            cout << "Enter 2 to Restock an item using an item's id" << endl;
            cout << endl
                 << "Enter your choice ---> ";
            int subchoice;
            cin >> subchoice;
            if (subchoice > 2)
            {
                subchoice = 0;
            }
            if (subchoice != 0)
                this->displayRestockingMenu(subchoice - 1);
            choice = '1';
            break;
        case '4':
            // confirm action
            clearConsole();
            cout << "\n\n\n\tAre you sure you want to cancel?\n\tPress 1 to confirm. Any Key. CANCEL----> ";
            cin >> choice;
            if (choice == '1')
                choice = '0';
            else
                choice = '1';
            break;
        default:
            cout << "\n\tInvalid choice";
            choice = '1';
            break;
        }
    } while (choice != '0' && choice == '1');
    clearConsole();
    return;
}

// TODO: Add variable quantity thresholds to items
// TODO: Show a summary/confirmation when stock is ordered
void AdminTransaction::displayRestockingMenu(int mode)
{
    Item *selected = nullptr;
    cout << " " << endl;
    clearConsole();

    if (mode == 0)
    {
        vector<Item *> belowThreshold = inventory->getBelowThresholdQty();

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

    SupplyOrder order(selected->getId(), desiredQuantity, getDateString(), "0001"); // TODO: Enable dates and different suppliers

    appendTransactionToFile(order);
    order.processDelivery(inventory);

    clearConsole();

    cout << "Order received!" << endl;
    cout << "The stock of \'" << selected->getName() << "\' has been updated to " << selected->getQuantity() << "!" << endl;
    cout << endl
         << "Input anything to continue ---> ";

    int cont;
    cin >> cont;

    clearConsole();
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

void AdminTransaction::displaySalesByDateMenu()
{

    cout << "\n\t\t\tPRIMO GROCERY\n";
    cout << "\n\tADMIN TRANSACTION\n";
    cout << "\t" << getDateString();
    list<string> dateList = GetAllDatesInSales();
    list<string>::iterator li = dateList.begin();

    int selection;
    int listIndex = 0;
    // display categories
    cout << "\n\n\t*****************  Select a Date   **********\n\n";
    while (li != dateList.end())
    {
        cout << "\t**\t" << setw(10) << right << (listIndex + 1) << ". " << setw(23) << left << *li << "**" << endl;

        ++li;
        ++listIndex;
    }

    cout << "\n\t*********************************************\n";
    cout << "\n\tEnter selection (0 to exit) ----> ";
    cin >> selection;

    if (selection == 0)
    {
        return;
    }

    selection--;

    li = dateList.begin();
    advance(li, selection);
    string dateString = *li;

    cout << "\n\nOutgoing items on " << dateString << endl;
    // get a list of sale ids having sale date equal to selected date
    list<string> saleIdsInSelection = GetSaleIdByDate(dateString);

    // for each id in the list returned, display outgoing sale items having that id.
    double dateTotal = 0.0;
    Sale::print_header();
    for (string id : saleIdsInSelection)
    {
        vector<SaleItem *> saleItems = inventory->readSalesById(id);
        for (SaleItem *si : saleItems)
        {
            si->print();
            dateTotal += si->getTotalPrice();
        }
    }

    stringstream ss;
    ss << "TOTAL:           $" << fixed << setprecision(2) << dateTotal;
    cout << endl;
    cout << setw(85) << right << "------------" << endl;
    cout << setw(85) << right << ss.str();

    cin.ignore();
    cout << "\n\n\n\tPress Enter to return";
    cin.ignore();
}

void print_balance_sheet_header()
{

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(12) << "Date"
              << " ";
    std::cout << std::setw(15) << std::left << "Total Sales"
              << " ";
    std::cout << std::setw(15) << std::left << "Total Debt"
              << " ";
    std::cout << std::setw(15) << std::left << "Invoice Due"
              << " " << endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}

void AdminTransaction::displayBalanceSheet()
{
    clearConsole();
    cout << "\n\tBalance Sheet Menu\n";
    print_balance_sheet_header();

    list<string> dateList = GetAllDatesInSales();
    list<string>::iterator li = dateList.begin();

    while (li != dateList.end())
    {
        list<string> saleIds = GetSaleIdByDate(*li);
        double dateTotal = 0.0;
        for (string id : saleIds)
        {
            vector<SaleItem *> saleItems = inventory->readSalesById(id);
            for (SaleItem *si : saleItems)
            {
                dateTotal += si->getTotalPrice();
            }
        }

        stringstream ss;
        ss << "$" << fixed << setprecision(2) << dateTotal;

        cout << setw(12) << *li << " ";
        cout << setw(15) << left << ss.str() << " ";
        cout << setw(15) << left << "-"
             << " ";
        cout << setw(15) << left << "-"
             << " \n";

        ++li;
    }

    cin.ignore();
    cout << "\n\n\n\tPress Enter to return";
    cin.ignore();
}

// void generateBalanceSheet(Inventory *inventory) {
//     list<string> dateList = GetAllDatesInSales();
//     list<string>::iterator li = dateList.begin();

//     while (li!=dateList.end()) {
//         list<string> saleIds = GetSaleIdByDate(*li);
//         double dateTotal = 0.0;
//         for (string id : saleIds)
//         {
//             vector<SaleItem *> saleItems = inventory->readSalesById(id);
//             for (SaleItem *si : saleItems)
//             {
//                 dateTotal += si->getTotalPrice();
//             }
//         }

//         stringstream ss;
//         ss << "$" << fixed << setprecision(2) << dateTotal;

//         cout << setw(12) << *li << " ";
//         cout << setw(15) << left << ss.str() << " ";
//         cout << setw(15) << left << "-" << " ";
//         cout << setw(15) << left << "-" << " \n";

//         ++li;
//     }
// }