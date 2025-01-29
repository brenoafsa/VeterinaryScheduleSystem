#include "cadastroalterar.h"
#include "ui_cadastroalterar.h"
#include "consultasdodia.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

cadastroalterar::cadastroalterar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastroalterar)
{
    ui->setupUi(this);

    // Conectar os botões com as funções
    connect(ui->listarButton, &QPushButton::clicked, this, &cadastroalterar::on_listarClientesButton_clicked);
    connect(ui->alterarButton, &QPushButton::clicked, this, &cadastroalterar::on_atualizarClienteButton_clicked);
    connect(ui->apagarButton, &QPushButton::clicked, this, &cadastroalterar::on_deletarClienteButton_clicked);
}

cadastroalterar::~cadastroalterar()
{
    delete ui;
}

void cadastroalterar::on_listarClientesButton_clicked()
{
    QVector<QJsonObject> tutores = carregarTutores();
    if (tutores.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Nenhum tutor cadastrado.");
        msgBox.setWindowTitle("Informação");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QString listaTutores;
    for (const auto &tutor : tutores) {
        listaTutores += QString("Nome: %1\nCPF: %2\nEmail: %3\nEndereço: %4\nTelefone: %5\n\n")
                            .arg(tutor["nome"].toString())
                            .arg(tutor["cpf"].toString())
                            .arg(tutor["email"].toString())
                            .arg(tutor["endereco"].toString())
                            .arg(tutor["telefone"].toString());
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(listaTutores);
    msgBox.setWindowTitle("Lista de Tutores");
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
    msgBox.exec();
}

void cadastroalterar::on_atualizarClienteButton_clicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do cliente para atualizar.");
        msgBox.setWindowTitle("Erro");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QVector<QJsonObject> tutores = carregarTutores();
    bool clienteEncontrado = false;

    for (auto &tutor : tutores) {
        if (tutor["cpf"].toString() == cpf) {
            clienteEncontrado = true;

            if (!ui->nomeTutor->text().isEmpty()) {
                tutor["nome"] = ui->nomeTutor->text();
            }
            if (!ui->emailTutor->text().isEmpty()) {
                tutor["email"] = ui->emailTutor->text();
            }
            if (!ui->enderecoTutor->text().isEmpty()) {
                tutor["endereco"] = ui->enderecoTutor->text();
            }
            if (!ui->telefoneTutor->text().isEmpty()) {
                tutor["telefone"] = ui->telefoneTutor->text();
            }

            break;
        }
    }

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");

    if (clienteEncontrado) {
        salvarTutores(tutores);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Cliente atualizado com sucesso!");
        msgBox.setWindowTitle("Sucesso");
    } else {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Cliente com o CPF informado não encontrado.");
        msgBox.setWindowTitle("Erro");
    }

    msgBox.exec();
}

void cadastroalterar::on_deletarClienteButton_clicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do cliente para deletar.");
        msgBox.setWindowTitle("Erro");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QVector<QJsonObject> tutores = carregarTutores();
    bool clienteEncontrado = false;

    for (int i = 0; i < tutores.size(); ++i) {
        if (tutores[i]["cpf"].toString() == cpf) {
            clienteEncontrado = true;
            tutores.remove(i);
            break;
        }
    }

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");

    if (clienteEncontrado) {
        salvarTutores(tutores);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Cliente deletado com sucesso!");
        msgBox.setWindowTitle("Sucesso");

        ui->nomeTutor->clear();
        ui->cpfTutor->clear();
        ui->emailTutor->clear();
        ui->enderecoTutor->clear();
        ui->telefoneTutor->clear();
    } else {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Cliente com o CPF informado não encontrado.");
        msgBox.setWindowTitle("Erro");
    }

    msgBox.exec();
}

// Função para carregar tutores a partir do arquivo JSON
QVector<QJsonObject> cadastroalterar::carregarTutores()
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

// Função para salvar tutores no arquivo JSON
void cadastroalterar::salvarTutores(const QVector<QJsonObject> &tutores)
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

void cadastroalterar::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}

