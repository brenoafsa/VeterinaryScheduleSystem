#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
#include "menu.h"
#include "database.h"
#include "cadastropet.h"
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
    delete listarClientesButton;
    delete atualizarClienteButton;
    delete deletarClienteButton;
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

void cadastrocliente::on_ListarCliente_clicked()
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

void cadastrocliente::on_AtualizarCliente_clicked()
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

void cadastrocliente::on_DeletarCliente_clicked()
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

void cadastrocliente::on_clienteButton_2_clicked()
{
    cadastropet *petScreen = new cadastropet();
    petScreen->show();
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

void cadastrocliente::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();
    this->close();
}
