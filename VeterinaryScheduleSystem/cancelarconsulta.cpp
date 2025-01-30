#include "cancelarconsulta.h"
#include "ui_cancelarconsulta.h"
#include "agendamento.h"
#include "menu.h"
#include "consultasdodia.h"
#include "remarcacao.h"
#include <QDateEdit>
#include <QTimeEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

cancelarconsulta::cancelarconsulta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cancelarconsulta)
{
    ui->setupUi(this);

    ui->dateEdit_2->setCalendarPopup(true); //pop-up de data
    // Definir a data do dia atual ao abrir a tela
    ui->dateEdit_2->setDate(QDate::currentDate());


    // Populando o comboBox com horários padronizados (7:30 até 19:00, de 30 em 30 minutos)
    QTime horaInicio(7, 30); // 07:30
    QTime horaFim(19, 0);    // 19:00

    while (horaInicio <= horaFim) {
        ui->comboBox->addItem(horaInicio.toString("HH:mm"));
        horaInicio = horaInicio.addSecs(30 * 60); // Adiciona 30 minutos
    }

}

cancelarconsulta::~cancelarconsulta()
{
    delete ui;
}

void cancelarconsulta::on_novaconsultaButton_clicked()
{
    // Botão Nova consulta
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();          // Fecha a janela atual
}

void cancelarconsulta::on_menuButton_clicked()
{
    // Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de remarcação
}

void cancelarconsulta::on_apagarButton_clicked()
{
    // Obter os dados preenchidos nos campos
    QString nomePet = ui->nomePet_2->text().trimmed().toLower();
    QString cpfTutor = ui->cpfTutor_2->text().remove(".").remove("-").trimmed();
    QString dataConsulta = ui->dateEdit_2->date().toString("dd/MM/yyyy").replace("/", "-");
    QString horaConsulta = ui->comboBox->currentText();
    QString veterinario = ui->veterinarioEdit_2->text().trimmed();

    // Verificar se algum campo está vazio
    if (nomePet.isEmpty() || cpfTutor.isEmpty() || dataConsulta.isEmpty() || horaConsulta.isEmpty() || veterinario.isEmpty()) {
        showErrorDialog("Por favor, preencha todos os campos.");
        return;
    }

    // Carregar as consultas existentes
    QFile file("consultas.json");
    if (!file.open(QIODevice::ReadOnly)) {
        showErrorDialog("Erro ao carregar consultas.");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray consultasArray = doc.array();
    file.close();

    bool consultaEncontrada = false;

    // Buscar a consulta com todos os critérios
    for (int i = 0; i < consultasArray.size(); ++i) {
        QJsonObject consulta = consultasArray[i].toObject();

        if (consulta["cpf_tutor"].toString() == cpfTutor &&
            consulta["nome_pet"].toString().toLower() == nomePet &&
            consulta["data"].toString() == dataConsulta &&
            consulta["hora"].toString() == horaConsulta &&
            consulta["veterinario"].toString() == veterinario) {

            consultasArray.removeAt(i);  // Remove a consulta encontrada
            consultaEncontrada = true;
            break;  // Encerra o loop após encontrar a consulta
        }
    }

    // Salvar alterações no arquivo
    if (consultaEncontrada) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            showErrorDialog("Erro ao salvar as alterações.");
            return;
        }

        file.write(QJsonDocument(consultasArray).toJson());
        file.close();

        QMessageBox successBox;
        successBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #C4B4E0; color: black; font-size: 14px;"
            "}"
            "QMessageBox QLabel {"
            "    color: #FFFFFF;" // Define a cor do texto principal como branco
            "}"
            "QPushButton {"
            "    background-color: #9B88BF; color: #FFFFFF; border-radius: 5px; padding: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #C7C0D5;"
            "}"
            );
        successBox.setIcon(QMessageBox::Information);
        successBox.setText("Consulta apagada com sucesso!");
        successBox.setWindowTitle("Sucesso");
        successBox.exec();

    } else {
        showErrorDialog("Nenhuma consulta encontrada com os dados fornecidos.");
    }
}

void cancelarconsulta::on_consultaButton_clicked()
{
    // Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}

void cancelarconsulta::showErrorDialog(const QString &message)
{
    QMessageBox errorBox;
    errorBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                           "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                           "QPushButton:hover { background-color: #A6036D; }");
    errorBox.setText(message);
    errorBox.exec();
}

void cancelarconsulta::on_cancelarButton_2_clicked()
{

    ui->nomePet_2->clear();
    ui->cpfTutor_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate()); // Define a data para o dia atual
    ui->comboBox->setCurrentIndex(0); // Define o primeiro horário (7:30)
    ui->veterinarioEdit_2->clear();

}



void cancelarconsulta::on_remarcacaoButton_clicked()
{
    remarcacao *remarcacaoScreen = new remarcacao();
    remarcacaoScreen -> show();
    this -> close();
}


void cancelarconsulta::on_consultaButton_2_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}


void cancelarconsulta::on_agendamentoButton_2_clicked()
{
    //Botão agendamento
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen -> show();
    this -> close();
}

