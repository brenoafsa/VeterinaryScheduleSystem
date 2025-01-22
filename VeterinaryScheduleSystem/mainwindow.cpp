#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"  // Inclua o cabeçalho da nova tela
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BotaoDeEntrada_clicked()
{
    QString nome = ui->txt_nome->text();
    QString senha = ui->txt_senha->text();

    QMessageBox::information(this, "Dados inseridos", "Usuário: " + nome + "\nSenha: " + senha);

    // Cria a nova tela de menu e mostra
    menu *menuScreen = new menu();
    menuScreen->show();

    // Fecha a janela atual (MainWindow)
    this->close();
}
