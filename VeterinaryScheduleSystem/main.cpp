#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "database.h"  // Incluindo o arquivo de banco de dados

using namespace std;

int main(int argc, char *argv[]) {
    // Inicializa o Qt
    QApplication a(argc, argv);

    // Inicializa o banco de dados e adiciona alguns dados (usuários e senhas)
    Database& db = Database::getInstance();
    db.addData("admin", "12345");
    db.addData("user", "password123");
    db.addData("mily", "1527");


    // Cria a janela principal
    MainWindow w;

    // Exibe a janela principal do Qt
    w.show();

    return a.exec();
}
