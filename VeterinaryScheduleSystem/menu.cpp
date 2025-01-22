#include "menu.h"
#include "ui_menu.h"
#include "agendamento.h"  // Inclua o cabeçalho da nova tela

menu::menu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_8_clicked()
{
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show();

    this->close(); // Fecha a janela atual (menu)
}
