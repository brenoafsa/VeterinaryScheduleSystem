#include "cadastropet.h"
#include "ui_cadastropet.h"
#include "cadastrocliente.h"
#include "menu.h"
#include <QMessageBox>
#include <QStringList>

namespace petDataBase {

// Definição do método getInstance
PetDataBase& PetDataBase::getInstance() {
    static PetDataBase instance;
    return instance;
}

} // namespace petDataBase

cadastropet::cadastropet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastropet)
{
    ui->setupUi(this);

    // Conectar os botões corretamente
    connect(ui->menuButton, &QPushButton::clicked, this, &cadastropet::on_menuButton_clicked);
    connect(ui->clienteButton_2, &QPushButton::clicked, this, &cadastropet::on_clienteButton_clicked);
    connect(ui->cadastrarButton_2, &QPushButton::clicked, this, &cadastropet::onCadastrarClicked);
    connect(ui->cancelarButton_2, &QPushButton::clicked, this, &cadastropet::onCancelarClicked);

    // Definir os botões de listar, atualizar e deletar pets
    listarPetsButton = new QPushButton(this);
    listarPetsButton->setText("Listar Pets");
    listarPetsButton->setGeometry(340, 520, 200, 40);
    listarPetsButton->setStyleSheet("background-color: #C4B4E0; color: #ffffff; font: bold 10pt;");
    connect(listarPetsButton, &QPushButton::clicked, this, &cadastropet::onListarPetsClicked);

    atualizarPetButton = new QPushButton(this);
    atualizarPetButton->setText("Atualizar Pet");
    atualizarPetButton->setGeometry(340, 570, 200, 40);
    atualizarPetButton->setStyleSheet("background-color: #A0C4FF; color: #ffffff; font: bold 10pt;");
    connect(atualizarPetButton, &QPushButton::clicked, this, &cadastropet::onAtualizarPetClicked);

    deletarPetButton = new QPushButton(this);
    deletarPetButton->setText("Deletar Pet");
    deletarPetButton->setGeometry(340, 620, 200, 40);
    deletarPetButton->setStyleSheet("background-color: #FF6F6F; color: #ffffff; font: bold 10pt;");
    connect(deletarPetButton, &QPushButton::clicked, this, &cadastropet::onDeletarPetClicked);
}

cadastropet::~cadastropet()
{
    delete ui;
    delete listarPetsButton;
    delete atualizarPetButton;
    delete deletarPetButton;
}

void cadastropet::onCadastrarClicked()
{
    QString nome = ui->nomePet->text();
    QString especie = ui->especiePet->text();
    QString raca = ui->racaPet->text();
    QString idade = ui->idadePet->text();
    QString tutor = ui->corPet->text();  // Corrigido para corPet

    if (nome.isEmpty() || especie.isEmpty() || raca.isEmpty() || idade.isEmpty() || tutor.isEmpty()) {

        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Warning);
        msgBox1.setText("<font color='black'>Por favor, preencha todos os campos!</font>");
        msgBox1.setWindowTitle("Erro");
        msgBox1.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox1.exec();
        return;
    }

    petDataBase::PetData pet = {nome, especie, raca, idade, tutor};
    petDataBase::PetDataBase::getInstance().addPet(pet);

    QMessageBox msgBox2;
    msgBox2.setIcon(QMessageBox::Information);
    msgBox2.setText("<font color='black'>Pet cadastrado com sucesso!</font>");
    msgBox2.setWindowTitle("Sucesso");
    msgBox2.setStyleSheet("QMessageBox { background-color: white; color: black; }");
    msgBox2.exec();

    ui->nomePet->clear();
    ui->especiePet->clear();
    ui->racaPet->clear();
    ui->idadePet->clear();
    ui->corPet->clear();  // Corrigido para corPet
}

void cadastropet::onListarPetsClicked()
{
    QList<petDataBase::PetData> pets = petDataBase::PetDataBase::getInstance().getPets();

    if (pets.isEmpty()) {

        QMessageBox msgBox3;
        msgBox3.setIcon(QMessageBox::Information);
        msgBox3.setText("<font color='black'>Nenhum pet cadastrado.</font>");
        msgBox3.setWindowTitle("Lista de Pets");
        msgBox3.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox3.exec();
        return;
    }

    QString petList;
    for (const auto& pet : pets) {
        petList += QString("Nome: %1\nEspécie: %2\nRaça: %3\nIdade: %4\nTutor: %5\n\n")
                       .arg(pet.nome)
                       .arg(pet.especie)
                       .arg(pet.raca)
                       .arg(pet.idade)
                       .arg(pet.cor);
    }

    QMessageBox::information(this, "Lista de Pets", petList);
}

void cadastropet::onAtualizarPetClicked()
{
    QString nome = ui->nomePet->text();

    if (nome.isEmpty()) {
        QMessageBox msgBox4;
        msgBox4.setIcon(QMessageBox::Warning);
        msgBox4.setText("<font color='black'>Por favor, insira o nome do pet para atualizar.</font>");
        msgBox4.setWindowTitle("Erro");
        msgBox4.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox4.exec();
        return;
    }

    petDataBase::PetData updatedPet = {
        nome,
        ui->especiePet->text(),
        ui->racaPet->text(),
        ui->idadePet->text(),
        ui->corPet->text()  // Corrigido para corPet
    };

    if (petDataBase::PetDataBase::getInstance().updatePet(nome, updatedPet)) {

        QMessageBox msgBox5;
        msgBox5.setIcon(QMessageBox::Information);
        msgBox5.setText("<font color='black'>Pet atualizado com sucesso!</font>");
        msgBox5.setWindowTitle("Sucesso");
        msgBox5.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox5.exec();

    } else {

        QMessageBox msgBox6;
        msgBox6.setIcon(QMessageBox::Warning);
        msgBox6.setText("<font color='black'>Pet com o nome informado não encontrado.</font>");
        msgBox6.setWindowTitle("Erro");
        msgBox6.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox6.exec();
    }
}

void cadastropet::onDeletarPetClicked()
{
    QString nome = ui->nomePet->text();

    if (nome.isEmpty()) {
        QMessageBox msgBox7;
        msgBox7.setIcon(QMessageBox::Warning);
        msgBox7.setText("<font color='black'>Por favor, insira o nome do pet para deletar.</font>");
        msgBox7.setWindowTitle("Erro");
        msgBox7.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox7.exec();
        return;
    }

    if (petDataBase::PetDataBase::getInstance().deletePet(nome)) {

        QMessageBox msgBox8;
        msgBox8.setIcon(QMessageBox::Information);
        msgBox8.setText("<font color='black'>Pet deletado com sucesso!</font>");
        msgBox8.setWindowTitle("Sucesso");
        msgBox8.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox8.exec();

        ui->nomePet->clear();
        ui->especiePet->clear();
        ui->racaPet->clear();
        ui->idadePet->clear();
        ui->corPet->clear();  // Corrigido para corPet

    } else {

        QMessageBox msgBox9;
        msgBox9.setIcon(QMessageBox::Warning);
        msgBox9.setText("<font color='black'>Pet com o nome informado não encontrado.</font>");
        msgBox9.setWindowTitle("Erro");
        msgBox9.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox9.exec();
    }
}

void cadastropet::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();     // Exibe a tela de menu
    this->close();          // Fecha a tela de cadastro
}

void cadastropet::on_clienteButton_clicked()
{
    this->close();
    cadastrocliente *cliente = new cadastrocliente(this);
    cliente->show();
}

void cadastropet::onCancelarClicked()
{
    ui->nomePet->clear();
    ui->especiePet->clear();
    ui->racaPet->clear();
    ui->idadePet->clear();
    ui->corPet->clear();  // Corrigido para corPet
}
