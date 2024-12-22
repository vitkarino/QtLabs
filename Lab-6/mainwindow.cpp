#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), db("tickets.db")
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QGroupBox *addTicketGroup = new QGroupBox("Додати квиток", this);
    QFormLayout *formLayout = new QFormLayout(addTicketGroup);

    nameInput = new QLineEdit(this);
    formLayout->addRow("Ім'я:", nameInput);

    priceInput = new QDoubleSpinBox(this);
    priceInput->setRange(0, 10000);
    formLayout->addRow("Ціна, грн:", priceInput);

    routeInput = new QLineEdit(this);
    formLayout->addRow("Маршрут:", routeInput);

    statusInput = new QComboBox(this);
    statusInput->addItems({"Заброньовано", "Скасовано", "Дійсний", "Недійсний"});
    formLayout->addRow("Статус:", statusInput);

    currentInput = new QCheckBox(this);
    formLayout->addRow("Актуальний:", currentInput);

    commentsInput = new QTextEdit(this);
    formLayout->addRow("Коментарі:", commentsInput);

    QPushButton *addButton = new QPushButton("Додати квиток", this);
    formLayout->addWidget(addButton);
    mainLayout->addWidget(addTicketGroup);

    QPushButton *showButton = new QPushButton("Показати всі квитки", this);
    mainLayout->addWidget(showButton);

    QPushButton *removeButton = new QPushButton("Видалити квиток", this);
    mainLayout->addWidget(removeButton);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTicket);
    connect(showButton, &QPushButton::clicked, this, &MainWindow::showTickets);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTicket);
}

void MainWindow::addTicket()
{
    QString name = nameInput->text();
    double price = priceInput->value();
    QString route = routeInput->text();
    bool current = currentInput->isChecked();
    QString status = statusInput->currentText();
    QString comments = commentsInput->toPlainText();

    if (name.isEmpty() || route.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Ім'я і маршрут обов'язкові для заповнення.");
        return;
    }

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    Ticket ticket(0, name.toStdString(), time.toStdString(), price, route.toStdString(),
                  current, comments.toStdString(), status.toStdString());

    if (db.addTicket(ticket)) {
        outputText->append("Квиток успішно додано!");
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалося додати квиток.");
    }
}

void MainWindow::showTickets()
{
    outputText->clear();
    auto tickets = db.getAllTickets();

    if (tickets.empty()) {
        outputText->append("Немає квитків.");
        return;
    }

    for (const auto &ticket : tickets) {
        outputText->append(QString::fromStdString(ticket.printInfo()));
    }
}

void MainWindow::removeTicket()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Видалення квитка", "Введіть ID квитка:", 1, 1, 99999, 1, &ok);

    if (ok && db.removeTicket(id)) {
        outputText->append(QString("Квиток #%1 видалено.").arg(id));
    } else {
        QMessageBox::warning(this, "Помилка", "Не вдалося видалити квиток.");
    }
}
