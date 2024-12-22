#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QTextEdit>
#include "database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addTicket();
    void showTickets();
    void removeTicket();

private:
    QLineEdit *nameInput;
    QDoubleSpinBox *priceInput;
    QLineEdit *routeInput;
    QComboBox *statusInput;
    QCheckBox *currentInput;
    QTextEdit *commentsInput;
    QTextEdit *outputText;

    Database db;
};

#endif // MAINWINDOW_H
