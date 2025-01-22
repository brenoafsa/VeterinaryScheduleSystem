#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"  // Inclua o cabeçalho da nova tela
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // A conexão já é feita automaticamente pelo Qt Designer, então a linha abaixo não é necessária
    // connect(ui->BotaoDeEntrada, &QPushButton::clicked, this, &MainWindow::on_BotaoDeEntrada_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BotaoDeEntrada_clicked()
{
    QString nome = ui->txt_nome->text();
    QString senha = ui->txt_senha->text();

    if (verificarCredenciais(nome, senha)) {
        // Login bem-sucedido, cria e exibe a tela de menu
        menu *menuScreen = new menu();
        menuScreen->show();

        // Fecha a janela atual (MainWindow)
        this->close();
    } else {
        // Login falhou, exibe mensagem de erro
        QMessageBox::warning(this, "Login", "Usuário ou senha inválidos!");
    }
}


bool MainWindow::verificarCredenciais(const QString &nome, const QString &senha) {
    // Simulação de credenciais armazenadas (substitua com banco de dados se necessário)
    const QString validnome = "admin";
    const QString validsenha = "12345";

    return (nome == validnome && senha == validsenha);
}
