#include "cadastropet.h"
#include "ui_cadastropet.h"
#include "cadastrocliente.h"
#include "database.h"
#include "cadastropesquisar.h"
#include "petalterar.h"
#include "menu.h"
#include "agendamento.h"
#include "consultasdodia.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>




cadastropet::cadastropet(QWidget *parent)
    : QDialog(parent), ui(new Ui::cadastropet) {
    ui->setupUi(this);

    // Conectando o botão "Cadastrar" ao método de cadastro
    connect(ui->cadastrarButton_2, &QPushButton::clicked, this, &cadastropet::cadastrarPet);

}

cadastropet::~cadastropet() {
    delete ui;
}




// Implementação do método cadastrarPet
void cadastropet::cadastrarPet() {
    // Reutiliza o método on_cadastrarButton_2_clicked
    //on_cadastrarButton_2_clicked();

    //não precisa mais usar isso
}




void cadastropet::on_cadastrarButton_2_clicked() {
    // Obtém os valores dos campos de texto
    QString nome = ui->nomePet->text();
    QString especie = ui->especiePet->text();
    QString cpfTutor = ui->cpfTutor->text();
    QString raca = ui->racaPet->text();
    QString idade = ui->idadePet->text();
    QString cor = ui->corPet->text();

    // Verifica se os campos obrigatórios estão preenchidos
    if (nome.isEmpty() || especie.isEmpty() || cpfTutor.isEmpty()) {
        QMessageBox msgBox0;
        msgBox0.setIcon(QMessageBox::Warning);
        msgBox0.setText("<font color='black'>Por favor, preencha os campos obrigatórios.</font>");
        msgBox0.setWindowTitle("Erro");
        msgBox0.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox0.exec();
        return;
    }

    // Verifica se o CPF do tutor existe no arquivo tutores.json
    QFile tutorFile("tutores.json");
    if (!tutorFile.open(QIODevice::ReadOnly)) {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Critical);
        msgBox1.setText("<font color='black'>Erro ao acessar o arquivo de tutores.</font>");
        msgBox1.setWindowTitle("Erro");
        msgBox1.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox1.exec();
        return;
    }

    QByteArray tutorData = tutorFile.readAll();
    tutorFile.close();

    QJsonDocument tutorDoc = QJsonDocument::fromJson(tutorData);
    QJsonArray tutorArray = tutorDoc.array();

    bool cpfEncontrado = false;
    for (const auto &tutor : tutorArray) {
        QJsonObject tutorObj = tutor.toObject();
        if (tutorObj["cpf"].toString() == cpfTutor) {
            cpfEncontrado = true;
            break;
        }
    }

    if (!cpfEncontrado) {
        QMessageBox msgBox2;
        msgBox2.setIcon(QMessageBox::Warning);
        msgBox2.setText("<font color='black'>CPF do tutor não encontrado. Cadastre o tutor antes de adicionar o pet.</font>");
        msgBox2.setWindowTitle("Erro");
        msgBox2.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox2.exec();
        return;
    }

    // Cria o objeto JSON para o novo pet
    QJsonObject novoPet;
    novoPet["nome"] = nome;
    novoPet["especie"] = especie;
    novoPet["cpf_tutor"] = cpfTutor;
    novoPet["raca"] = raca;
    novoPet["idade"] = idade;
    novoPet["cor"] = cor;

    // Carrega os dados existentes do arquivo
    QVector<QJsonObject> dados = carregarDados();

    // Adiciona o novo pet aos dados
    dados.append(novoPet);

    // Salva os dados no arquivo JSON
    salvarDados(dados);

    // Exibe uma mensagem de sucesso
    QMessageBox msgBox3;
    msgBox3.setIcon(QMessageBox::Information);
    msgBox3.setText("<font color='black'>Pet cadastrado com sucesso!</font>");
    msgBox3.setWindowTitle("Sucesso");
    msgBox3.setStyleSheet("QMessageBox { background-color: white; color: black; }");
    msgBox3.exec();

    // Limpa os campos após o cadastro
    ui->nomePet->clear();
    ui->especiePet->clear();
    ui->cpfTutor->clear();
    ui->racaPet->clear();
    ui->idadePet->clear();
    ui->corPet->clear();
}








void cadastropet::on_ListarPets_clicked() {
    QVector<QJsonObject> dados = carregarDados(); // Carrega os dados do JSON
    QString petList;

    for (const auto &pet : dados) {
        petList += QString("Nome: %1\nEspécie: %2\nCPF Tutor: %3\nRaça: %4\nIdade: %5\nCor: %6\n\n")
                       .arg(pet["nome"].toString())
                       .arg(pet["especie"].toString())
                       .arg(pet["cpf_tutor"].toString())
                       .arg(pet["raca"].toString())
                       .arg(pet["idade"].toString())
                       .arg(pet["cor"].toString());
    }

    if (petList.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Nenhum pet cadastrado.");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(petList);
        msgBox.setWindowTitle("Lista de Pets");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
    }
}









void cadastropet::on_AtualizarPet_clicked() {
    QString cpfTutor = ui->cpfTutor->text();

    if (cpfTutor.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do tutor para atualizar os dados do pet.");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
        return;
    }

    // Carrega os dados do JSON
    QVector<QJsonObject> dados = carregarDados();
    bool encontrado = false;

    // Atualiza o pet com o CPF informado
    for (auto &pet : dados) {
        if (pet["cpf_tutor"].toString() == cpfTutor) {
            pet["nome"] = ui->nomePet->text();
            pet["especie"] = ui->especiePet->text();
            pet["raca"] = ui->racaPet->text();
            pet["idade"] = ui->idadePet->text();
            pet["cor"] = ui->corPet->text();
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        salvarDados(dados); // Salva os dados atualizados no JSON
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Dados do pet atualizados com sucesso!");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Pet com o CPF do tutor informado não encontrado.");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
    }
}







void cadastropet::on_DeletarPet_clicked() {
    QString cpfTutor = ui->cpfTutor->text();

    if (cpfTutor.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Por favor, insira o CPF do tutor para deletar o pet.");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
        return;
    }

    // Carrega os dados do JSON
    QVector<QJsonObject> dados = carregarDados();
    bool encontrado = false;

    // Remove o pet com o CPF informado
    for (int i = 0; i < dados.size(); ++i) {
        if (dados[i]["cpf_tutor"].toString() == cpfTutor) {
            dados.remove(i);
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        salvarDados(dados); // Salva os dados restantes no JSON
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pet deletado com sucesso!");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();

        // Limpa os campos de entrada
        ui->nomePet->clear();
        ui->especiePet->clear();
        ui->cpfTutor->clear();
        ui->racaPet->clear();
        ui->idadePet->clear();
        ui->corPet->clear();
    } else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Pet com o CPF do tutor informado não encontrado.");
        msgBox.setStyleSheet("QMessageBox { background-color: #333; color: white; }");
        msgBox.exec();
    }
}









void cadastropet::on_clienteButton_2_clicked() {
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}









void cadastropet::salvarDados(const QVector<QJsonObject> &dados) {
    QFile file("dados_pet.json"); // Nome do arquivo JSON
    if (!file.open(QIODevice::WriteOnly)) { // Tenta abrir o arquivo para escrita
        qDebug() << "Erro ao abrir o arquivo para escrita.";
        return;
    }

    QJsonArray jsonArray;
    for (const auto &dado : dados) {
        jsonArray.append(dado); // Adiciona cada objeto ao array JSON
    }

    QJsonDocument doc(jsonArray);
    file.write(doc.toJson()); // Salva o array no arquivo
    file.close(); // Fecha o arquivo
}








QVector<QJsonObject> cadastropet::carregarDados() {
    QFile file("dados_pet.json"); // Nome do arquivo JSON
    if (!file.open(QIODevice::ReadOnly)) { // Tenta abrir o arquivo para leitura
        qDebug() << "Arquivo JSON não encontrado. Será criado ao salvar novos dados.";
        return {}; // Retorna uma lista vazia se o arquivo não existir
    }

    QByteArray jsonData = file.readAll(); // Lê os dados do arquivo
    QJsonDocument doc = QJsonDocument::fromJson(jsonData); // Converte para JSON
    QJsonArray jsonArray = doc.array(); // Obtém o array de objetos JSON

    QVector<QJsonObject> dados;
    for (const auto &item : jsonArray) {
        dados.append(item.toObject()); // Converte cada item para QJsonObject
    }

    return dados; // Retorna os dados carregados
}


//BOTÃO PAGINA PESQUISAR
void cadastropet::on_pesquisarButton_2_clicked()
{
    cadastropesquisar *pesquisarScreen = new cadastropesquisar();
    pesquisarScreen->show();
    this->close();
}


void cadastropet::on_telaButton_clicked()
{
    petalterar *atualizarpetScreen = new petalterar();
    atualizarpetScreen->show();
    this->close();
}


void cadastropet::on_menuButton_clicked()
{
    // Botão voltar Menu
    menu *menuScreen = new menu(); // Cria a tela menu
    menuScreen->show(); // Exibe a tela de menu
    this->close();             // Fecha a janela atual
}


void cadastropet::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do cadastro pet
}


void cadastropet::on_consultaButton_clicked()
{
    //Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}

