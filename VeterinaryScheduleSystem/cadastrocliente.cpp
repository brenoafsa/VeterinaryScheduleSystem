#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"

cadastrocliente::cadastrocliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrocliente)
{
    ui->setupUi(this);
}

cadastrocliente::~cadastrocliente()
{
    delete ui;
}
