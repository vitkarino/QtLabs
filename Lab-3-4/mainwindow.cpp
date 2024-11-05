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
    formLayout->addRow("Коментарі (не обов'язково):", commentsInput);

    addButton = new QPushButton("Додати квиток", this);
    formLayout->addWidget(addButton);
    mainLayout->addWidget(addTicketGroup);

    showButton = new QPushButton("Показати всі квитки", this);
    mainLayout->addWidget(showButton);

    removeButton = new QPushButton("Видалити квиток", this);
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

    nameInput->clear();
    priceInput->setValue(0.0);
    routeInput->clear();
    currentInput->setChecked(false);
    statusInput->setCurrentIndex(0);
    commentsInput->clear();
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

void MainWindow::removeTicket()
{
    bool ok;
    int index = QInputDialog::getInt(this, "Видалити квиток", "Введіть номер квитка для видалення:", 1, 1, tickets.size(), 1, &ok);

    if (ok && index > 0 && index <= tickets.size()) {
        tickets.erase(tickets.begin() + (index - 1));
        outputText->append(QString("Квиток #%1 видалено.").arg(index));
    } else {
        QMessageBox::warning(this, "Помилка", "Введіть існуючий номер квитка.");
    }
}
