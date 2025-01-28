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

//BOTÃO DE PESQUISAR
void cadastroconsulta::on_pesquisarrButton_3_clicked()
{

}

