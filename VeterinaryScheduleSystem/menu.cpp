#include "menu.h"
#include "ui_menu.h"
#include "agendamento.h"
#include "mainwindow.h" // Inclua aqui o cabeçalho

menu::menu(MainWindow *parent) :
    QDialog(parent),  // Chama o construtor de QDialog, não QWidget
    ui(new Ui::menu),
    mainWindow(parent)
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

void menu::on_sairButton_clicked()
{
    // Fecha o menu e exibe a MainWindow novamente
    this->close();
    if (mainWindow) {
        mainWindow->show();
    }
}

