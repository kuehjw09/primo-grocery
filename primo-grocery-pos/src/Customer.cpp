#include "../include/Customer.h"

std::string Customer::asFileString()
{
    std::stringstream ss;

    ss << lastName << "\t";
    ss << firstName << "\t";
    ss << phoneNumber << "\t";

    return ss.str();
}