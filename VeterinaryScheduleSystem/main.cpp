#include "mainwindow.h"
#include "database.h"
#include "cadastrocliente.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Inicializa o banco de dados de usuários
    Database& db = Database::getInstance();
    db.addData("admin", "12345");
    db.addData("user", "password123");
    db.addData("mily", "1527");
    db.addData("", "");


    // Teste: Exibe os clientes cadastrados no terminal
    clientDataBase& clientDB = clientDataBase::getInstance();

    // Adicionando clientes de exemplo (opcional, para teste)
    clientDataBase::ClientData cliente1 = {"João Silva", "12345678900", "joao@gmail.com", "Rua A, 123", "99999-1111"};
    clientDataBase::ClientData cliente2 = {"Maria Oliveira", "98765432100", "maria@hotmail.com", "Avenida B, 456", "98888-2222"};

    clientDB.addClient(cliente1);
    clientDB.addClient(cliente2);

    // Exibe os clientes cadastrados no terminal
    cout << "Clientes cadastrados:" << endl;
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
