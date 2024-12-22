#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <vector>
#include "ticket.h"

class Database
{
public:
    explicit Database(const QString &dbPath = "tickets.db");
    ~Database();

    bool addTicket(const Ticket &ticket);
    bool removeTicket(int id);
    std::vector<Ticket> getAllTickets() const;

private:
    QSqlDatabase db;
    bool initialize();
};

#endif // DATABASE_H
