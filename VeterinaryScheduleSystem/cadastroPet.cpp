#include "cadastroCliente.h"
#include "ui_cadastroCliente.h"

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
