#ifndef TICKET_H
#define TICKET_H

#include <string>
using namespace std;

class Ticket
{
private:
    string fullName;
    string purchaseTime;
    double price;
    string route;
    bool isCurrent;
    string ticketComments;
    string ticketStatus;

public:
    Ticket(string name, string time, double p, string r, bool current, string comments, string status);

    string printInfo() const;
    void removeTicket();
};

#endif // TICKET_H
