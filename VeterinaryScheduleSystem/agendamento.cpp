#include "agendamento.h"
#include "ui_agendamento.h"

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
