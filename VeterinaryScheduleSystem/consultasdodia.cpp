#include "consultasdodia.h"
#include "ui_consultasdodia.h"
#include "menu.h"
#include "agendamento.h"

consultasdodia::consultasdodia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::consultasdodia)
{
    ui->setupUi(this);
}

consultasdodia::~consultasdodia()
{
    delete ui;
}

void consultasdodia::on_menuButton_2_clicked()
{
    // Botão voltar ao menu
    menu *menuScreen = new menu(); // Cria a tela menu
    menuScreen->show(); // Exibe a tela de menu
    this->close();             // Fecha a janela atual
}


void consultasdodia::on_agendamentoButton_2_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela das consultas
}

