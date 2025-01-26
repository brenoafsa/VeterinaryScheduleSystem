#include "cadastropet.h"
#include "ui_cadastropet.h"

cadastropet::cadastropet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastropet)
{
    ui->setupUi(this);
}

cadastropet::~cadastropet()
{
    delete ui;
}
