#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
#include "menu.h"
#include "database.h"
#include "cadastropet.h"
#include "cadastropesquisar.h"
#include "cadastroalterar.h"  // Incluindo o cabeçalho da nova tela
#include "agendamento.h"
#include "consultasdodia.h"
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include <QVector>
#include <QString>

cadastrocliente::cadastrocliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrocliente)
{
    ui->setupUi(this);
}

cadastrocliente::~cadastrocliente()
{
    delete ui;
}

void cadastrocliente::on_cadastrarButton_clicked()
{
    QString nome = ui->nomeTutor->text();
    QString cpf = ui->cpfTutor->text();
    QString email = ui->emailTutor->text();
    QString endereco = ui->enderecoTutor->text();
    QString telefone = ui->telefoneTutor->text();

    if (nome.isEmpty() || cpf.isEmpty() || email.isEmpty() || endereco.isEmpty() || telefone.isEmpty()) {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Warning);
        msgBox1.setText("Por favor, preencha todos os campos!");
        msgBox1.setWindowTitle("Erro");
        msgBox1.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox1.exec();
        return;
    }

    QVector<QJsonObject> tutores = carregarTutores();

    for (const auto &tutor : tutores) {
        if (tutor["cpf"].toString() == cpf) {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("CPF já cadastrado!");
            msgBox.setWindowTitle("Erro");
            msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
            msgBox.exec();
            return;
        }
    }

    QJsonObject novoTutor;
    novoTutor["nome"] = nome;
    novoTutor["cpf"] = cpf;
    novoTutor["email"] = email;
    novoTutor["endereco"] = endereco;
    novoTutor["telefone"] = telefone;

    tutores.append(novoTutor);
    salvarTutores(tutores);

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Tutor cadastrado com sucesso!");
    msgBox.setWindowTitle("Sucesso");
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
    msgBox.exec();

    ui->nomeTutor->clear();
    ui->cpfTutor->clear();
    ui->emailTutor->clear();
    ui->enderecoTutor->clear();
    ui->telefoneTutor->clear();
}

void cadastrocliente::on_clienteButton_2_clicked()
{
    cadastropet *petScreen = new cadastropet();
    petScreen->show();
    this->close();
}

void cadastrocliente::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();
    this->close();
}

void cadastrocliente::on_pesquisarButton_clicked()
{
    cadastropesquisar *pesquisarScreen = new cadastropesquisar();
    pesquisarScreen->show();
    this->close();
}

void cadastrocliente::on_telaButton_clicked()
{
    cadastroalterar *alterarScreen = new cadastroalterar();
    alterarScreen->show();
    this->close();
}

QVector<QJsonObject> cadastrocliente::carregarTutores()
{
    QFile arquivo("tutores.json");
    QVector<QJsonObject> tutores;

    if (!arquivo.open(QIODevice::ReadOnly)) {
        return tutores;
    }

    QJsonDocument doc = QJsonDocument::fromJson(arquivo.readAll());
    QJsonArray array = doc.array();
    for (const QJsonValue &valor : array) {
        tutores.append(valor.toObject());
    }

    arquivo.close();
    return tutores;
}

void cadastrocliente::salvarTutores(const QVector<QJsonObject> &tutores)
{
    QFile arquivo("tutores.json");

    if (!arquivo.open(QIODevice::WriteOnly)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Erro ao salvar os tutores.");
        msgBox.setWindowTitle("Erro");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QJsonArray array;
    for (const auto &tutor : tutores) {
        array.append(tutor);
    }

    QJsonDocument doc(array);
    arquivo.write(doc.toJson());
    arquivo.close();
}

void cadastrocliente::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do cadastro
}


void cadastrocliente::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}

