#include "petalterar.h"
#include "ui_petalterar.h"
#include "menu.h"
#include "consultasdodia.h"
#include "agendamento.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

petalterar::petalterar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::petalterar)
{
    ui->setupUi(this);

}

petalterar::~petalterar()
{
    delete ui;
}

void petalterar::on_listarButton_clicked()
{
    QVector<QJsonObject> pets = carregarPets();
    if (pets.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Nenhum pet cadastrado.");
        msgBox.setWindowTitle("Informação");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QString listaPets;
    for (const auto &pet : pets) {
        listaPets += QString("Nome: %1\nEspécie: %2\nRaça: %3\nIdade: %4\nCor: %5\nCPF do Tutor: %6\n\n")
                         .arg(pet["nome"].toString())
                         .arg(pet["especie"].toString())
                         .arg(pet["raca"].toString())
                         .arg(pet["idade"].toString())
                         .arg(pet["cor"].toString())
                         .arg(pet["cpf_tutor"].toString());
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(listaPets);
    msgBox.setWindowTitle("Lista de Pets");
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
    msgBox.exec();
}

void petalterar::on_alterarButton_clicked()
{
    QString cpfTutor = ui->cpfTutor->text();
    QString nomePet = ui->nomePet->text();

    if (cpfTutor.isEmpty() || nomePet.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do tutor e o nome do pet para atualizar.");
        msgBox.setWindowTitle("Erro");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QVector<QJsonObject> pets = carregarPets();
    bool petEncontrado = false;

    for (auto &pet : pets) {
        if (pet["cpf_tutor"].toString() == cpfTutor && pet["nome"].toString() == nomePet) {
            petEncontrado = true;

            if (!ui->especiePet->text().isEmpty()) {
                pet["especie"] = ui->especiePet->text();
            }
            if (!ui->racaPet->text().isEmpty()) {
                pet["raca"] = ui->racaPet->text();
            }
            if (!ui->idadePet->text().isEmpty()) {
                pet["idade"] = ui->idadePet->text();
            }
            if (!ui->corPet->text().isEmpty()) {
                pet["cor"] = ui->corPet->text();
            }

            break;
        }
    }

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");

    if (petEncontrado) {
        salvarPets(pets);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pet atualizado com sucesso!");
        msgBox.setWindowTitle("Sucesso");
    } else {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Pet com o CPF do tutor e nome informados não encontrado.");
        msgBox.setWindowTitle("Erro");
    }

    msgBox.exec();
}

void petalterar::on_apagarButton_clicked()
{
    QString cpfTutor = ui->cpfTutor->text();
    QString nomePet = ui->nomePet->text();

    if (cpfTutor.isEmpty() || nomePet.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do tutor e o nome do pet para deletar.");
        msgBox.setWindowTitle("Erro");
        msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");
        msgBox.exec();
        return;
    }

    QVector<QJsonObject> pets = carregarPets();
    bool petEncontrado = false;

    for (int i = 0; i < pets.size(); ++i) {
        if (pets[i]["cpf_tutor"].toString() == cpfTutor && pets[i]["nome"].toString() == nomePet) {
            petEncontrado = true;
            pets.remove(i);
            break;
        }
    }

    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox { background-color: #323232; color: #FFFFFF; }");

    if (petEncontrado) {
        salvarPets(pets);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pet deletado com sucesso!");
        msgBox.setWindowTitle("Sucesso");

        ui->nomePet->clear();
        ui->cpfTutor->clear();
        ui->especiePet->clear();
        ui->racaPet->clear();
        ui->idadePet->clear();
        ui->corPet->clear();
    } else {
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Pet com o CPF do tutor e nome informados não encontrado.");
        msgBox.setWindowTitle("Erro");
    }

    msgBox.exec();
}

QVector<QJsonObject> petalterar::carregarPets()
{
    QFile arquivo("dados_pet.json"); // Alterado para usar o novo arquivo
    QVector<QJsonObject> pets;

    if (!arquivo.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erro", "Não foi possível abrir o arquivo dados_pet.json.");
        return pets;
    }

    QJsonDocument doc = QJsonDocument::fromJson(arquivo.readAll());
    QJsonArray array = doc.array();
    for (const QJsonValue &valor : array) {
        pets.append(valor.toObject());
    }

    arquivo.close();
    return pets;
}


void petalterar::salvarPets(const QVector<QJsonObject> &pets)
{
    QFile arquivo("dados_pet.json"); // Alterado para usar o novo arquivo

    if (!arquivo.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Erro", "Erro ao salvar os pets no arquivo dados_pet.json.");
        return;
    }

    QJsonArray array;
    for (const auto &pet : pets) {
        array.append(pet);
    }

    QJsonDocument doc(array);
    arquivo.write(doc.toJson());
    arquivo.close();
}


void petalterar::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen -> show();
    this-> close();
}


void petalterar::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}


void petalterar::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do menu
}


void petalterar::on_cancelarButton_2_clicked()
{
    ui->corPet->clear();
    ui->cpfTutor->clear();
    ui->especiePet->clear();
    ui->idadePet->clear();
    ui->nomePet->clear();
    ui->racaPet->clear();


}

