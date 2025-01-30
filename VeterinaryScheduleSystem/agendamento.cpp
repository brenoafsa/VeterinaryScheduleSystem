#include "agendamento.h"
#include "ui_agendamento.h"
#include "menu.h"
#include "remarcacao.h"
#include "consultasdodia.h"
#include "cancelarconsulta.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QDateEdit>
#include <QTimeEdit>





agendamento::agendamento(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::agendamento)
{
    ui->setupUi(this);

    // Configurar o campo de data
    ui->dateEdit->setDisplayFormat("dd-MM-yyyy"); // Define o formato de exibição
    ui->dateEdit->setCalendarPopup(true); // Habilita o popup do calendário
    ui->dateEdit->setDate(QDate::currentDate()); // Define a data atual como padrão

    // Configurar o campo de hora
    ui->timeEdit->setDisplayFormat("HH:mm"); // Garante que horas e minutos aparecem
    ui->timeEdit->setTime(QTime::currentTime()); // Define a hora atual
    ui->timeEdit->setMinimumTime(QTime(0, 0));  // Permite valores desde 00:00
    ui->timeEdit->setMaximumTime(QTime(23, 59)); // Permite até 23:59
    ui->timeEdit->setWrapping(true); // Permite rolagem de valores
    ui->timeEdit->setButtonSymbols(QAbstractSpinBox::UpDownArrows);


}

agendamento::~agendamento()
{
    delete ui;
}

void agendamento::on_menuButton_clicked()
{
    //Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de agendamento
}

void agendamento::on_remarcacaoButton_clicked()
{
    // Botão Remarcar consulta
    remarcacao *remarcacaoScreen = new remarcacao();
    remarcacaoScreen->show(); // Exibe a tela de remarcação
    this->close();          // Fecha a janela atual
}

void agendamento::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}


void agendamento::on_pushButton_10_clicked()
{
    // Obtendo e normalizando dados
    QString nomePet = ui->lineEdit_2->text().trimmed().toLower();
    QString cpfTutor = ui->lineEdit_3->text().remove(".").remove("-").trimmed();
    QString dataConsulta = ui->dateEdit->date().toString("dd-MM-yyyy");
    QString horaConsulta = ui->timeEdit->time().toString("HH:mm");
    QString veterinario = ui->lineEdit->text().trimmed();

    // Verificação de campos vazios
    if (nomePet.isEmpty() || cpfTutor.isEmpty() || dataConsulta.isEmpty() || horaConsulta.isEmpty() || veterinario.isEmpty()) {
        showErrorDialog("Por favor, preencha todos os campos.");
        return;
    }

    // Validação do tutor
    QJsonArray tutoresArray = loadJsonArray("tutores.json");
    qDebug() << "Tutores carregados:" << QJsonDocument(tutoresArray).toJson();

    if (tutoresArray.isEmpty()) {
        showErrorDialog("Erro ao carregar dados dos tutores.");
        return;
    }

    bool tutorEncontrado = false;

    for (const QJsonValue &value : tutoresArray) {
        QJsonObject tutor = value.toObject();

        if (!tutor.contains("cpf")) {
            qDebug() << "Erro: Objeto tutor sem chave 'cpf':" << tutor;
            continue;
        }

        QString cpfJson = tutor["cpf"].toString();
        QString cpfTutorLimpo = cpfTutor;

        qDebug() << "Comparando CPF do JSON:" << cpfJson << "com CPF informado:" << cpfTutorLimpo;

        if (cpfJson == cpfTutorLimpo) {
            tutorEncontrado = true;
            break;
        }
    }

    if (!tutorEncontrado) {
        qDebug() << "Nenhum tutor encontrado com o CPF:" << cpfTutor;
    }

    // Validação do pet
    QJsonArray petsArray = loadJsonArray("dados_pet.json");
    if (petsArray.isEmpty()) {
        showErrorDialog("Erro ao carregar dados dos pets.");
        return;
    }

    bool petEncontrado = false;
    for (const QJsonValue &value : petsArray) {
        QJsonObject pet = value.toObject();

        QString cpfTutorPet = pet["cpf_tutor"].toString().remove(".").remove("-");
        QString nomePetJson = pet["nome"].toString().toLower();

        qDebug() << "Comparando nome do pet JSON: [" << nomePetJson << "] com nome informado: [" << nomePet << "]";


        if (cpfTutorPet == cpfTutor && nomePetJson == nomePet) {
            petEncontrado = true;
            break;
        }
    }

    if (!petEncontrado) {
        showErrorDialog("Pet não encontrado para este tutor.");
        return;
    }

    // Salvar consulta
    QJsonObject novaConsulta;
    novaConsulta["nome_pet"] = nomePet;
    novaConsulta["cpf_tutor"] = cpfTutor;
    novaConsulta["data"] = dataConsulta;
    novaConsulta["hora"] = horaConsulta;
    novaConsulta["veterinario"] = veterinario;

    if (!saveConsulta(novaConsulta)) {
        showErrorDialog("Erro ao salvar a consulta.");
        return;
    }

    QMessageBox successBox;
    successBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                             "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                             "QPushButton:hover { background-color: #A6036D; }");
    successBox.setText("Consulta cadastrada com sucesso!");
    successBox.exec();
}

// Funções auxiliares
QJsonArray agendamento::loadJsonArray(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return QJsonArray();
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        return QJsonArray();
    }

    return doc.array();
}

bool agendamento::saveConsulta(const QJsonObject &consulta) {
    QFile file("consultas.json");
    QJsonArray consultasArray;

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        consultasArray = doc.array();
        file.close();
    }

    consultasArray.append(consulta);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    file.write(QJsonDocument(consultasArray).toJson());
    file.close();
    return true;
}

void agendamento::showErrorDialog(const QString &message) {
    QMessageBox errorBox;
    errorBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                           "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                           "QPushButton:hover { background-color: #A6036D; }");
    errorBox.setText(message);
    errorBox.exec();

}


void agendamento::on_cancelarconsultaButton_clicked()
{
    //Botão cancelar consulta
    cancelarconsulta *cancelarconsultaScreen = new cancelarconsulta();
    cancelarconsultaScreen -> show();
    this -> close();
}

