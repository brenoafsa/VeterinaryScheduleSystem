#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
#include "menu.h"
#include "database.h"
#include "cadastropet.h"
#include "cadastropesquisar.h"
#include "cadastroalterar.h"
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

// Construtor
cadastrocliente::cadastrocliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrocliente)
{
    ui->setupUi(this);
}

// Destrutor
cadastrocliente::~cadastrocliente()
{
    delete ui;
}

// Botão 'Cadastrar'
void cadastrocliente::on_cadastrarButton_clicked()
{
    // Obtém os dados do usuário na interface
    QString nome = ui->nomeTutor->text();
    QString cpf = ui->cpfTutor->text();
    QString email = ui->emailTutor->text();
    QString endereco = ui->enderecoTutor->text();
    QString telefone = ui->telefoneTutor->text();

    // Checa se algum campo está vazio e exibe uma mensagem de erro
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

    // Analisa se o CPF já foi cadastrado
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

    // Cria um novo objeto JSON com os dados do tutor
    QJsonObject novoTutor;
    novoTutor["nome"] = nome;
    novoTutor["cpf"] = cpf;
    novoTutor["email"] = email;
    novoTutor["endereco"] = endereco;
    novoTutor["telefone"] = telefone;

    // Adiciona o tutor na lista e salva no arquivo
    tutores.append(novoTutor);
    salvarTutores(tutores);

    // Mensagem de cadastro feito com sucessoo
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Tutor cadastrado com sucesso!");
    msgBox.setWindowTitle("Sucesso");
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
    msgBox.exec();

    // Limpa os campos de entrada na interface
    ui->nomeTutor->clear();
    ui->cpfTutor->clear();
    ui->emailTutor->clear();
    ui->enderecoTutor->clear();
    ui->telefoneTutor->clear();
}

// Botão cadastro pet
void cadastrocliente::on_clienteButton_2_clicked()
{
    cadastropet *petScreen = new cadastropet();
    petScreen->show();
    this->close();
}

// Botão para retornar ao menu (consultas gerais)
void cadastrocliente::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();
    this->close();
}

// Botão de pesquisar
void cadastrocliente::on_pesquisarButton_clicked()
{
    cadastropesquisar *pesquisarScreen = new cadastropesquisar();
    pesquisarScreen->show();
    this->close();
}

// Botão para alterar cadastro
void cadastrocliente::on_telaButton_clicked()
{
    cadastroalterar *alterarScreen = new cadastroalterar();
    alterarScreen->show();
    this->close();
}

// Botão para agendamento
void cadastrocliente::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do cadastro
}

// Botão consultas do dia
void cadastrocliente::on_consultaButton_clicked()
{
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}

// Carrega todos os tutores do arquivo JSON
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

// Função para salvar a lista de tutores no arquivo JSON
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

// Botão cancelar, limpa os dados preenchidos
void cadastrocliente::on_cancelarButton_clicked()
{
    ui->nomeTutor->clear();
    ui->cpfTutor->clear();
    ui->emailTutor->clear();
    ui->enderecoTutor->clear();
    ui->telefoneTutor->clear();
}

