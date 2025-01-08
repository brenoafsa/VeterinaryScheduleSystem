#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , registerWindow(new RegisterWindow(this)) // Initialize RegisterWindow
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton); // Connect Register button
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton()
{
    QString name[] = {"abc", "def", "ghi"};
    QString code[] = {"abc123", "def34", "ghi56"};

    QString uName = ui->lineEdit->text();
    QString uCode = ui->lineEdit_2->text();

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (uName == name[i] && uCode == code[i]) {
            QMessageBox::information(this, "Welcome Message",
                                     "User: " + name[i] +
                                         " Welcome to Login Management System");
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "Error Box", "Invalid Username or Password");
    }
}

void MainWindow::on_registerButton()
{
    registerWindow->show(); // Show the Register window
}
