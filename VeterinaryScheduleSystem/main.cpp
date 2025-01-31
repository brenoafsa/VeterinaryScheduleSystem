#include "mainwindow.h"
#include "database.h"
#include "cadastrocliente.h"
#include "cadastropet.h"
#include <QApplication>
#include <iostream>
#include <QIcon>
#include <QFile>


using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);


    // icon
    a.setWindowIcon(QIcon(":/images/images/icone.png"));



    // Inicializa o banco de dados de usuários
    Database& db = Database::getInstance();
    db.addData("admin", "12345");
    db.addData("user", "password123");



    // Teste: Exibe os clientes cadastrados no terminal
    clientDataBase& clientDB = clientDataBase::getInstance();


    // Exibe os clientes cadastrados no terminal
    for (const auto& cliente : clientDB.getClients()) {
        cout << "Cliente: " << cliente.nome.toStdString()
        << ", CPF: " << cliente.cpf.toStdString()
        << ", Email: " << cliente.email.toStdString()
        << ", Endereço: " << cliente.endereco.toStdString()
        << ", Telefone: " << cliente.telefone.toStdString()
        << endl;
    }

    // Inicializa a janela principal
    MainWindow w;
    w.show();

    return a.exec();
}
