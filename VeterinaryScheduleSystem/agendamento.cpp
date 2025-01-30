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
#include <QComboBox>

agendamento::agendamento(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::agendamento)
{
    ui->setupUi(this);

    // Configurar o campo de data
    ui->dateEdit->setDisplayFormat("dd-MM-yyyy");
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());

    // Configurar o campo de horário (ComboBox)
    ui->comboBox->clear();
    QTime horaInicio(7, 30); // Início às 07:30
    QTime horaFim(19, 0);    // Fim às 19:00

    while (horaInicio <= horaFim) {
        ui->comboBox->addItem(horaInicio.toString("HH:mm"));
        horaInicio = horaInicio.addSecs(30 * 60); // Incremento de 30 minutos
    }
}

agendamento::~agendamento()
{
    delete ui;
}

void agendamento::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();
    this->close();
}

void agendamento::on_remarcacaoButton_clicked()
{
    remarcacao *remarcacaoScreen = new remarcacao();
    remarcacaoScreen->show();
    this->close();
}

void agendamento::on_consultaButton_clicked()
{
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}

void agendamento::on_pushButton_10_clicked()
{
    // Obtendo e normalizando dados
    QString nomePet = ui->lineEdit_2->text().trimmed().toLower();
    QString cpfTutor = ui->lineEdit_3->text().remove(".").remove("-").trimmed();
    QString dataConsulta = ui->dateEdit->date().toString("dd-MM-yyyy");
    QString horaConsulta = ui->comboBox->currentText(); // Obtém o horário escolhido no ComboBox
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
        if (!tutor.contains("cpf")) continue;

        if (tutor["cpf"].toString() == cpfTutor) {
            tutorEncontrado = true;
            break;
        }
    }

    if (!tutorEncontrado) {
        showErrorDialog("CPF do tutor não encontrado.");
        return;
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

        if (pet["cpf_tutor"].toString().remove(".").remove("-") == cpfTutor &&
            pet["nome"].toString().toLower() == nomePet) {
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

    return doc.isArray() ? doc.array() : QJsonArray();
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
    cancelarconsulta *cancelarconsultaScreen = new cancelarconsulta();
    cancelarconsultaScreen->show();
    this->close();
}

void agendamento::on_pushButton_11_clicked()
{
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox->setCurrentIndex(0); // Define o primeiro horário como padrão
    ui->lineEdit->clear();
}
