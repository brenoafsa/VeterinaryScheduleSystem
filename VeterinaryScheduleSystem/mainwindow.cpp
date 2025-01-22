#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"  // Inclua o cabeçalho da nova tela
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->BotaoDeEntrada, &QPushButton::clicked, this, &MainWindow::on_BotaoDeEntrada_clicked);
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
        // Login bem-sucedido, exibe mensagem ou abre nova janela
       // QMessageBox::information(this, "Login", "Login realizado com sucesso!");
        // Cria a nova tela de menu e mostra
        menu *menuScreen = new menu();
        menuScreen->show();

        // Aqui você pode abrir a próxima janela ou tela principal
    } else {
        // Login falhou, exibe mensagem de erro
        //QMessageBox::warning(this, "Login", "Usuário ou senha inválidos!");
    }



    // Fecha a janela atual (MainWindow)
    //this->close();
}

bool MainWindow::verificarCredenciais(const QString &nome, const QString &senha) {
    // Simulação de credenciais armazenadas (substitua com banco de dados se necessário)
    const QString validnome = "admin";
    const QString validsenha = "12345";

    return (nome == validnome && senha == validsenha);
}
