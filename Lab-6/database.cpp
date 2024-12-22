#include "database.h"
#include <QSqlError>
#include <QDebug>

Database::Database(const QString &dbPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qCritical() << "Cannot open database:" << db.lastError().text();
        return;
    }

    if (!initialize()) {
        qCritical() << "Failed to initialize database.";
    }
}

Database::~Database()
{
    db.close();
}

bool Database::initialize()
{
    QSqlQuery query(db);
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS tickets ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "time TEXT NOT NULL, "
        "price REAL NOT NULL, "
        "route TEXT NOT NULL, "
        "current INTEGER NOT NULL, "
        "comments TEXT, "
        "status TEXT NOT NULL)";
    return query.exec(createTableQuery);
}

bool Database::addTicket(const Ticket &ticket)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO tickets (name, time, price, route, current, comments, status) "
                  "VALUES (:name, :time, :price, :route, :current, :comments, :status)");
    query.bindValue(":name", QString::fromStdString(ticket.getName()));
    query.bindValue(":time", QString::fromStdString(ticket.getPurchaseTime()));
    query.bindValue(":price", ticket.getPrice());
    query.bindValue(":route", QString::fromStdString(ticket.getRoute()));
    query.bindValue(":current", ticket.isCurrent());
    query.bindValue(":comments", QString::fromStdString(ticket.getComments()));
    query.bindValue(":status", QString::fromStdString(ticket.getStatus()));
    return query.exec();
}

bool Database::removeTicket(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM tickets WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

std::vector<Ticket> Database::getAllTickets() const
{
    std::vector<Ticket> tickets;
    QSqlQuery query("SELECT * FROM tickets", db);

    while (query.next()) {
        Ticket ticket(query.value("id").toInt(),
                      query.value("name").toString().toStdString(),
                      query.value("time").toString().toStdString(),
                      query.value("price").toDouble(),
                      query.value("route").toString().toStdString(),
                      query.value("current").toBool(),
                      query.value("comments").toString().toStdString(),
                      query.value("status").toString().toStdString());
        tickets.push_back(ticket);
    }

    return tickets;
}
