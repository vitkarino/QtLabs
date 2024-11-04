#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Main widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Add Ticket GroupBox
    QGroupBox *addTicketGroup = new QGroupBox("Додати квиток", this);
    QFormLayout *formLayout = new QFormLayout(addTicketGroup);

    nameInput = new QLineEdit(this);
    formLayout->addRow("Ім'я:", nameInput);

    priceInput = new QDoubleSpinBox(this);
    priceInput->setRange(0, 10000); // Example range, can be adjusted
    formLayout->addRow("Ціна, грн:", priceInput);

    routeInput = new QLineEdit(this);
    formLayout->addRow("Маршрут:", routeInput);

    statusInput = new QComboBox(this);
    statusInput->addItems({"Заброньовано", "Скасовано", "Дійсний", "Недійсний"});
    formLayout->addRow("Статус:", statusInput);

    currentInput = new QCheckBox(this);
    formLayout->addRow("Актуальний:", currentInput);

    // Output TextEdit
    commentsInput = new QTextEdit(this);
    formLayout->addRow("Коментарі (не обов'язково):", commentsInput);

    addButton = new QPushButton("Додати квиток", this);
    formLayout->addWidget(addButton);
    mainLayout->addWidget(addTicketGroup);

    // Show All Tickets Button
    showButton = new QPushButton("Показати всі квитки", this);
    mainLayout->addWidget(showButton);

    // Remove Ticket Button
    removeButton = new QPushButton("Видалити квиток", this);  // Update button name
    mainLayout->addWidget(removeButton);

    // Output TextEdit
    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    // Set main layout
    setCentralWidget(centralWidget);

    // Connect button signals to slots
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTicket);
    connect(showButton, &QPushButton::clicked, this, &MainWindow::showTickets);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTicket);  // Connect to removeTicket
}

void MainWindow::addTicket()
{
    QString fullName = nameInput->text();
    double price = priceInput->value();
    QString route = routeInput->text();
    bool isCurrent = currentInput->isChecked();
    QString status = statusInput->currentText();
    QString ticketComments = commentsInput->toPlainText();

    if (fullName.isEmpty() || route.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Ім'я і маршрут мають бути заповненими.");
        return;
    }

    QString purchaseTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    Ticket ticket(fullName.toStdString(), purchaseTime.toStdString(), price, route.toStdString(),
                  isCurrent, ticketComments.toStdString(), status.toStdString());

    tickets.push_back(ticket);
    outputText->append("Квиток успішно додано!");
}

void MainWindow::showTickets()
{
    outputText->clear();

    if (tickets.empty()) {
        outputText->append("Немає квитків.");
        return;
    }

    for (size_t i = 0; i < tickets.size(); ++i) {
        outputText->append(QString("Квиток #%1:\n%2\n---------------------")
                               .arg(i + 1)
                               .arg(QString::fromStdString(tickets[i].printInfo())));
    }
}

void MainWindow::removeTicket()  // Updated function name
{
    bool ok;
    int index = QInputDialog::getInt(this, "Видалити квиток", "Введіть номер квитка для видалення:", 1, 1, tickets.size(), 1, &ok);

    if (ok && index > 0 && index <= tickets.size()) {
        tickets.erase(tickets.begin() + (index - 1));  // Remove ticket from the list
        outputText->append(QString("Квиток #%1 видалено.").arg(index));
    } else {
        QMessageBox::warning(this, "Помилка", "Введіть існуючий номер квитка.");
    }
}
