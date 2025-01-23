#include "menu.h"
#include "ui_menu.h"
#include "agendamento.h"
#include "cadastrocliente.h"
#include "mainwindow.h"

menu::menu(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::menu),
    mainWindow(parent)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_6_clicked()
{
    // Botão Cadastro Cliente
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

void menu::on_pushButton_8_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do menu
}

void menu::on_sairButton_clicked()
{
    // Botão Sair
    this->close(); // Fecha o menu
    if (mainWindow) {
        mainWindow->show(); // Exibe a MainWindow novamente
    }
}
