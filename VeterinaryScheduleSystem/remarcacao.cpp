#include "remarcacao.h"
#include "ui_remarcacao.h"

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
