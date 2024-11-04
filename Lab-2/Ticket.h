#ifndef TICKET_H
#define TICKET_H

#include <string>

class Ticket
{
private:
    std::string fullName;
    std::string purchaseTime;
    double price;
    std::string route;
    bool isCurrent;
    std::string userHistory;
    std::string ticketStatus;

public:
    Ticket(std::string name, std::string time, double p, std::string r, bool current, std::string history, std::string status);

    void printInfo();
    void removeTicket();
};

#endif // TICKET_H
