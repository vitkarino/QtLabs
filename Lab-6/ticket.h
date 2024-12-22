#ifndef TICKET_H
#define TICKET_H

#include <string>

class Ticket
{
public:
    Ticket(int id, const std::string &name, const std::string &time, double price,
           const std::string &route, bool current, const std::string &comments, const std::string &status);

    int getId() const;
    std::string getName() const;
    std::string getPurchaseTime() const;
    double getPrice() const;
    std::string getRoute() const;
    bool isCurrent() const;
    std::string getComments() const;
    std::string getStatus() const;

    std::string printInfo() const;

private:
    int id;
    std::string name;
    std::string purchaseTime;
    double price;
    std::string route;
    bool current;
    std::string comments;
    std::string status;
};

#endif // TICKET_H
