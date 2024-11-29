#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QTextEdit>
#include <vector>
#include "ticket.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addTicket();
    void showTickets();
    void saveTicketsToFile();
    void removeTicket();
    void chooseFilePath();

private:
    QLineEdit *nameInput;
    QDoubleSpinBox *priceInput;
    QLineEdit *routeInput;
    QComboBox *statusInput;
    QCheckBox *currentInput;
    QPushButton *addButton;
    QPushButton *showButton;
    QPushButton *saveButton;
    QPushButton *removeButton;
    QPushButton *choosePathButton;
    QTextEdit *outputText;
    QTextEdit *commentsInput;
    QLineEdit *pathInput;
    QString saveDirectory;
    std::vector<Ticket> tickets;
};

#endif // MAINWINDOW_H
