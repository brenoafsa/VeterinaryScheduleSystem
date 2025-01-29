#include "consultasdodia.h"
#include "ui_consultasdodia.h"

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
