#include "agendamento.h"
#include "ui_agendamento.h"
#include "menu.h"
#include "remarcacao.h"

agendamento::agendamento(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::agendamento)
{
    ui->setupUi(this);
}

agendamento::~agendamento()
{
    delete ui;
}

void agendamento::on_menuButton_clicked()
{
    //Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de agendamento
}

void agendamento::on_remarcacaoButton_clicked()
{
    // Botão Remarcar consulta
    remarcacao *remarcacaoScreen = new remarcacao();
    remarcacaoScreen->show(); // Exibe a tela de remarcação
    this->close();          // Fecha a janela atual
}

