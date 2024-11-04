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
    std::string ticketComments;
    std::string ticketStatus;

public:
    Ticket(std::string name, std::string time, double p, std::string r, bool current, std::string comments, std::string status);

    std::string printInfo() const;
    void removeTicket();
};

#endif // TICKET_H
