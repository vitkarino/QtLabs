#include "ticket.h"
#include <sstream>

Ticket::Ticket(int id, const std::string &name, const std::string &time, double price,
               const std::string &route, bool current, const std::string &comments, const std::string &status)
    : id(id), name(name), purchaseTime(time), price(price), route(route), current(current),
    comments(comments), status(status) {}

int Ticket::getId() const { return id; }
std::string Ticket::getName() const { return name; }
std::string Ticket::getPurchaseTime() const { return purchaseTime; }
double Ticket::getPrice() const { return price; }
std::string Ticket::getRoute() const { return route; }
bool Ticket::isCurrent() const { return current; }
std::string Ticket::getComments() const { return comments; }
std::string Ticket::getStatus() const { return status; }

std::string Ticket::printInfo() const
{
    std::ostringstream oss;
    oss << "Ім'я: " << name << "\n"
        << "Дата купівлі: " << purchaseTime << "\n"
        << "Ціна: " << price << " UAH\n"
        << "Маршрут: " << route << "\n"
        << "Актуальний: " << (current ? "Так" : "Ні") << "\n"
        << "Коментарі: " << comments << "\n"
        << "Статус: " << status;
    return oss.str();
}
