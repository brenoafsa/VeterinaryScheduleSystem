#include "menu.h"
#include "ui_menu.h"
#include "agendamento.h"
#include "cadastrocliente.h"
#include "mainwindow.h"
#include "consultasdodia.h"

menu::menu(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::menu),
    mainWindow(parent)
{
    ui->setupUi(this);


    QPixmap logo("C:/Users/camil/Documents/GitHub/VeterinaryScheduleSystem/VeterinaryScheduleSystem/logo1.png");
    //ui->label_2->setPixmap(logo.scaled(500, 500, Qt::KeepAspectRatio));
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_6_clicked()
{
    // Botão Cadastro Cliente
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}


void menu::on_sairButton_clicked()
{

    // Botão Sair
    this->close(); // Fecha o menu
    if (mainWindow) {
        mainWindow->show(); // Exibe a MainWindow novamente
    }
}

void menu::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do menu
}


void menu::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}




