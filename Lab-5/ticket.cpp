#include "ticket.h"
#include <sstream>
using namespace std;

Ticket::Ticket(string name, string time, double p, string r, bool current, string comments, string status)
    : fullName(name), purchaseTime(time), price(p), route(r), isCurrent(current), ticketComments(comments), ticketStatus(status) {}

std::string Ticket::printInfo() const
{
    std::ostringstream oss;
    oss << "Ім'я: " << fullName << "\n"
        << "Дата купівлі: " << purchaseTime << "\n"
        << "Ціна: " << price << " UAH\n"
        << "Маршрут: " << route << "\n"
        << "Статус: " << (isCurrent ? "Дійсний" : "Недійсний") << "\n"
        << "Коментарі: " << ticketComments << "\n"
        << "Статус: " << ticketStatus;
    return oss.str();
}

void Ticket::removeTicket()
{
    ticketStatus = "Скасовано";
    isCurrent = false;
}
