#include "Ticket.h"
#include <iostream>

Ticket::Ticket(std::string name, std::string time, double p, std::string r, bool current, std::string history, std::string status)
    : fullName(name), purchaseTime(time), price(p), route(r), isCurrent(current), userHistory(history), ticketStatus(status) {}

void Ticket::printInfo()
{
    std::cout << "Full Name: " << fullName << std::endl;
    std::cout << "Purchase Time: " << purchaseTime << std::endl;
    std::cout << "Price: " << price << " UAH" << std::endl;
    std::cout << "Route: " << route << std::endl;
    std::cout << "Current Status: " << (isCurrent ? "Valid" : "Invalid") << std::endl;
    std::cout << "User History: " << userHistory << std::endl;
    std::cout << "Ticket Status: " << ticketStatus << std::endl;
}

void Ticket::removeTicket()
{
    ticketStatus = "Cancelled";
    isCurrent = false;
}
