#include "cadastropesquisar.h"
#include "ui_cadastropesquisar.h"
#include "cadastrocliente.h"
#include "cadastropet.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QTreeWidgetItem>

cadastropesquisar::cadastropesquisar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastropesquisar)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels({"Nome", "Informação"});
    ui->lineEdit->setStyleSheet("color: black; "
                                "background-color:#ffffff;"
                                "border-radius: 10px;");


    // Carrega todos os tutores e pets ao inicializar a tela
    carregarTutoresEPets();



}

cadastropesquisar::~cadastropesquisar()
{
    delete ui;
}




QJsonArray cadastropesquisar::loadJsonArray(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Erro", "Não foi possível abrir o arquivo: " + fileName);
        return {};
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::critical(this, "Erro", "O arquivo " + fileName + " está em um formato inválido.");
        return {};
    }

    return doc.array();
}



void cadastropesquisar::carregarTutoresEPets()
{
    // Carrega os tutores
    QJsonArray tutoresArray = loadJsonArray("tutores.json");

    // Limpa o TreeWidget antes de adicionar os itens
    ui->treeWidget->clear();

    // Percorre os tutores
    for (const QJsonValue& value : tutoresArray) {
        if (value.isObject()) {
            QJsonObject tutor = value.toObject();

            // Cria um item principal para o tutor
            QTreeWidgetItem* tutorItem = new QTreeWidgetItem(ui->treeWidget);
            tutorItem->setText(0, "Tutor: " + tutor["nome"].toString());
            tutorItem->setText(1, "CPF: " + tutor["cpf"].toString());

            // Adiciona mais informações do tutor
            QTreeWidgetItem* telefoneItem = new QTreeWidgetItem(tutorItem);
            telefoneItem->setText(0, "Telefone");
            telefoneItem->setText(1, tutor["telefone"].toString());

            QTreeWidgetItem* emailItem = new QTreeWidgetItem(tutorItem);
            emailItem->setText(0, "Email");
            emailItem->setText(1, tutor["email"].toString());

            // Carrega os dados dos pets
            QJsonArray petsArray = loadJsonArray("dados_pet.json");

            // Adiciona os pets ao TreeWidget
            for (const QJsonValue& petValue : petsArray) {
                if (petValue.isObject()) {
                    QJsonObject pet = petValue.toObject();
                    if (pet["cpf_tutor"].toString() == tutor["cpf"].toString()) {
                        QTreeWidgetItem* petItem = new QTreeWidgetItem(tutorItem);
                        petItem->setText(0, "Pet: " + pet["nome"].toString());
                        petItem->setText(1, "Raça: " + pet["raca"].toString());

                        // Adiciona mais informações do pet
                        QTreeWidgetItem* idadeItem = new QTreeWidgetItem(petItem);
                        idadeItem->setText(0, "Idade");
                        idadeItem->setText(1, pet["idade"].toString());

                        QTreeWidgetItem* corItem = new QTreeWidgetItem(petItem);
                        corItem->setText(0, "Cor");
                        corItem->setText(1, pet["cor"].toString());
                    }
                }
            }
        }
    }

    // Expande o TreeWidget para exibir todos os dados
    ui->treeWidget->expandAll();
}



//BOTÃO DE PESQUISAR
void cadastropesquisar::on_pesquisarrButton_3_clicked()
{
    QString cpfPesquisa = ui->lineEdit->text().trimmed(); // Obtém o texto do QLineEdit
    if (cpfPesquisa.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Por favor, insira um CPF para pesquisar.");
        return;
    }

    // Carrega os tutores
    QJsonArray tutoresArray = loadJsonArray("tutores.json");

    // Variável para armazenar o tutor encontrado
    QJsonObject tutorEncontrado;

    // Percorre os tutores para verificar se o CPF existe
    for (const QJsonValue& value : tutoresArray) {
        if (value.isObject()) {
            QJsonObject tutor = value.toObject();
            if (tutor["cpf"].toString() == cpfPesquisa) {
                tutorEncontrado = tutor;
                break;
            }
        }
    }

    // Se o tutor não foi encontrado, exibe uma mensagem
    if (tutorEncontrado.isEmpty()) {
        QMessageBox::information(this, "Pesquisa", "Tutor com o CPF informado não foi encontrado.");
        return;
    }

    // Exibe os dados do tutor no TreeWidget
    ui->treeWidget->clear();
    QTreeWidgetItem* tutorItem = new QTreeWidgetItem(ui->treeWidget);
    tutorItem->setText(0, "Tutor: " + tutorEncontrado["nome"].toString());
    tutorItem->setText(1, "CPF: " + tutorEncontrado["cpf"].toString());

    // Adiciona mais informações do tutor
    QTreeWidgetItem* telefoneItem = new QTreeWidgetItem(tutorItem);
    telefoneItem->setText(0, "Telefone");
    telefoneItem->setText(1, tutorEncontrado["telefone"].toString());

    QTreeWidgetItem* emailItem = new QTreeWidgetItem(tutorItem);
    emailItem->setText(0, "Email");
    emailItem->setText(1, tutorEncontrado["email"].toString());

    // Agora carrega os dados dos pets
    QJsonArray petsArray = loadJsonArray("dados_pet.json");

    // Adiciona os pets ao TreeWidget
    for (const QJsonValue& value : petsArray) {
        if (value.isObject()) {
            QJsonObject pet = value.toObject();
            if (pet["cpf_tutor"].toString() == cpfPesquisa) {
                QTreeWidgetItem* petItem = new QTreeWidgetItem(tutorItem);
                petItem->setText(0, "Pet: " + pet["nome"].toString());
                petItem->setText(1, "Raça: " + pet["raca"].toString());

                // Adiciona mais informações do pet
                QTreeWidgetItem* idadeItem = new QTreeWidgetItem(petItem);
                idadeItem->setText(0, "Idade");
                idadeItem->setText(1, pet["idade"].toString());

                QTreeWidgetItem* corItem = new QTreeWidgetItem(petItem);
                corItem->setText(0, "Cor");
                corItem->setText(1, pet["cor"].toString());
            }
        }
    }

    // Expande o TreeWidget
    ui->treeWidget->expandAll();
}




//BOTÃO DE ATUALIZAR
void cadastropesquisar::on_atualizarButton_3_clicked()
{

}



//BOTÃO DE DELETAR
void cadastropesquisar::on_deletarButton_4_clicked()
{

}



//BOTÃO DE CANCELAR
void cadastropesquisar::on_cancelarButton_2_clicked()
{

}



//BOTÃO PAGINA CADASTROCLIENTE
void cadastropesquisar::on_clienteButton_clicked()
{
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

//BOTÃO PAGINA CADASTROPET
void cadastropesquisar::on_clienteButton_2_clicked()
{
    cadastropet *petScreen = new cadastropet();
    petScreen->show();
    this->close();
}

