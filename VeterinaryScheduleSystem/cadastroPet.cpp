#include "cadastropet.h"
#include "ui_cadastropet.h"
#include "menu.h"
#include "cadastrocliente.h"

cadastropet::cadastropet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastropet)
{
    ui->setupUi(this);
}

cadastropet::~cadastropet()
{
    delete ui;
}

void cadastropet::on_menuButton_clicked()
{
    // Botão retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();     // Exibe a tela de menu
    this->close();          // Fecha a tela de cadastro
}


void cadastropet::on_clienteButton_2_clicked()
{
    // Botão Cadastro Cliente
    cadastrocliente *clienteScreen = new cadastrocliente(); // Cria a tela de cadastro
    clienteScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

