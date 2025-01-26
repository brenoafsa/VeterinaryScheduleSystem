#include "cadastroconsulta.h"
#include "ui_cadastroconsulta.h"

cadastroconsulta::cadastroconsulta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroconsulta)
{
    ui->setupUi(this);
}

cadastroconsulta::~cadastroconsulta()
{
    delete ui;
}
