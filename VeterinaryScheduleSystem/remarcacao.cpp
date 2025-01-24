#include "remarcacao.h"
#include "ui_remarcacao.h"
#include "agendamento.h"
#include "menu.h"

remarcacao::remarcacao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::remarcacao)
{
    ui->setupUi(this);
}

remarcacao::~remarcacao()
{
    delete ui;
}

void remarcacao::on_novaconsultaButton_clicked()
{
    // Botão Nova consulta
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show(); // Exibe a tela de remarcação
    this->close();          // Fecha a janela atual
}


void remarcacao::on_menuButton_clicked()
{
    //Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de agendamento
}

