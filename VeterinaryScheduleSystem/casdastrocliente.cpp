#include "casdastrocliente.h"
#include "ui_casdastrocliente.h"

casdastrocliente::casdastrocliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::casdastrocliente)
{
    ui->setupUi(this);
}

casdastrocliente::~casdastrocliente()
{
    delete ui;
}
