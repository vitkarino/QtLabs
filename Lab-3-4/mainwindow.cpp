#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QFileDialog>
#include <fstream>

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

    saveButton = new QPushButton("Зберегти квитки у файл", this);
    mainLayout->addWidget(saveButton);

    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathInput = new QLineEdit(this);
    pathInput->setPlaceholderText("Шлях до файлу...");
    pathInput->setReadOnly(true);

    choosePathButton = new QPushButton("Обрати шлях", this);
    pathLayout->addWidget(pathInput);
    pathLayout->addWidget(choosePathButton);
    mainLayout->addLayout(pathLayout);

    removeButton = new QPushButton("Видалити квиток", this);
    mainLayout->addWidget(removeButton);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);
    mainLayout->addWidget(outputText);

    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTicket);
    connect(showButton, &QPushButton::clicked, this, &MainWindow::showTickets);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveTicketsToFile);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTicket);
    connect(choosePathButton, &QPushButton::clicked, this, &MainWindow::chooseFilePath);
}

void MainWindow::chooseFilePath()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Обрати папку для збереження", QDir::homePath());
    if (!dir.isEmpty()) {
        saveDirectory = dir;
        pathInput->setText(saveDirectory + "/tickets.txt");
    }
}

void MainWindow::saveTicketsToFile()
{
    if (saveDirectory.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Оберіть папку для збереження файлу.");
        return;
    }

    QString fullPath = saveDirectory + "/tickets.txt";
    std::ofstream file(fullPath.toStdString(), std::ios::out);
    if (!file.is_open()) {
        QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл для запису.");
        return;
    }

    for (const auto &ticket : tickets) {
        file << ticket.printInfo() << "\n---------------------\n";
    }

    file.close();
    outputText->append("Квитки успішно збережено у файл: " + fullPath);
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
        showTickets();
    } else {
        QMessageBox::warning(this, "Помилка", "Введіть існуючий номер квитка.");
    }
}
