#include "registerwindow.h"
#include "./ui_registerwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    // Setup database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)");
    }

    connect(ui->confirmButton, &QPushButton::clicked, this, &RegisterWindow::on_confirmButton);
}

RegisterWindow::~RegisterWindow()
{
    db.close();
    delete ui;
}

void RegisterWindow::on_confirmButton()
{
    QString newUsername = ui->lineEditUsername->text();
    QString newPassword = ui->lineEditPassword->text();

    if (newUsername.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Username and Password cannot be empty");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", newUsername);
    query.bindValue(":password", newPassword);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "User registered successfully");
        this->close(); // Close the register window
    } else {
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}
