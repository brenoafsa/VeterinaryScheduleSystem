#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
#include "menu.h"
#include "database.h"
#include "cadastropet.h"
#include <QMessageBox>
#include <QStringList>

cadastrocliente::cadastrocliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrocliente)
{
    ui->setupUi(this);

    connect(ui->cadastrarButton, &QPushButton::clicked, this, &cadastrocliente::onCadastrarClicked);

    listarClientesButton = new QPushButton(this);
    listarClientesButton->setText("Listar Clientes");
    listarClientesButton->setGeometry(340, 520, 200, 40);
    listarClientesButton->setStyleSheet("background-color: #C4B4E0; color: #ffffff; font: bold 10pt;");
    connect(listarClientesButton, &QPushButton::clicked, this, &cadastrocliente::onListarClientesClicked);

    atualizarClienteButton = new QPushButton(this);
    atualizarClienteButton->setText("Atualizar Cliente");
    atualizarClienteButton->setGeometry(340, 570, 200, 40);
    atualizarClienteButton->setStyleSheet("background-color: #A0C4FF; color: #ffffff; font: bold 10pt;");
    connect(atualizarClienteButton, &QPushButton::clicked, this, &cadastrocliente::onAtualizarClienteClicked);

    deletarClienteButton = new QPushButton(this);
    deletarClienteButton->setText("Deletar Cliente");
    deletarClienteButton->setGeometry(340, 620, 200, 40);
    deletarClienteButton->setStyleSheet("background-color: #FF6F6F; color: #ffffff; font: bold 10pt;");
    connect(deletarClienteButton, &QPushButton::clicked, this, &cadastrocliente::onDeletarClienteClicked);
}

cadastrocliente::~cadastrocliente()
{
    delete ui;
    delete listarClientesButton;
    delete atualizarClienteButton;
    delete deletarClienteButton;
}

void cadastrocliente::onCadastrarClicked()
{
    QString nome = ui->nomeTutor->text();
    QString cpf = ui->cpfTutor->text();
    QString email = ui->emailTutor->text();
    QString endereco = ui->enderecoTutor->text();
    QString telefone = ui->telefoneTutor->text();

    if (nome.isEmpty() || cpf.isEmpty() || email.isEmpty() || endereco.isEmpty() || telefone.isEmpty()) {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Warning);
        msgBox1.setText("<font color='black'>Por favor, preencha todos os campos!</font>");
        msgBox1.setWindowTitle("Erro");
        msgBox1.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox1.exec();
        return;
    }

    // Verifica se o CPF já existe no banco de dados
    std::vector<QString> cpfList = Database::getInstance().getData("cpf");

    if (std::find(cpfList.begin(), cpfList.end(), cpf) != cpfList.end()) {
        QMessageBox msgBox2;
        msgBox2.setIcon(QMessageBox::Warning);
        msgBox2.setText("<font color='black'>CPF já cadastrado!</font>");
        msgBox2.setWindowTitle("Erro");
        msgBox2.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox2.exec();
        return;
    }

    // Adiciona cliente ao banco de dados
    Database::getInstance().addData("nome", nome);
    Database::getInstance().addData("cpf", cpf);
    Database::getInstance().addData("email", email);
    Database::getInstance().addData("endereco", endereco);
    Database::getInstance().addData("telefone", telefone);

    QMessageBox msgBox3;
    msgBox3.setIcon(QMessageBox::Information);
    msgBox3.setText("<font color='black'>Cliente cadastrado com sucesso!</font>");
    msgBox3.setWindowTitle("Sucesso");
    msgBox3.setStyleSheet("QMessageBox { background-color: white; color: black; }");
    msgBox3.exec();

    ui->nomeTutor->clear();
    ui->cpfTutor->clear();
    ui->emailTutor->clear();
    ui->enderecoTutor->clear();
    ui->telefoneTutor->clear();
}

void cadastrocliente::onListarClientesClicked()
{
    std::vector<QString> nomes = Database::getInstance().getData("nome");
    std::vector<QString> cpfs = Database::getInstance().getData("cpf");
    std::vector<QString> emails = Database::getInstance().getData("email");
    std::vector<QString> enderecos = Database::getInstance().getData("endereco");
    std::vector<QString> telefones = Database::getInstance().getData("telefone");

    if (nomes.empty()) {
        QMessageBox msgBox4;
        msgBox4.setIcon(QMessageBox::Information);
        msgBox4.setText("<font color='black'>Nenhum cliente cadastrado.</font>");
        msgBox4.setWindowTitle("Lista de Clientes");
        msgBox4.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox4.exec();
        return;
    }

    QString clientList;
    for (int i = 0; i < nomes.size(); ++i) {
        clientList += QString("Nome: %1\nCPF: %2\nEmail: %3\nEndereço: %4\nTelefone: %5\n\n")
                          .arg(nomes[i])
                          .arg(cpfs[i])
                          .arg(emails[i])
                          .arg(enderecos[i])
                          .arg(telefones[i]);
    }

    //QMessageBox::information(this, "Lista de Clientes", clientList);
    QMessageBox msgBoxlist;
    msgBoxlist.setIcon(QMessageBox::Information);
    msgBoxlist.setText(QString("<font color='black'>%1</font>").arg(clientList));
    msgBoxlist.setWindowTitle("Lista de Clientes");
    msgBoxlist.setStyleSheet("QMessageBox { background-color: white; color: black; }");
    msgBoxlist.exec();
}

void cadastrocliente::onAtualizarClienteClicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        QMessageBox msgBox5;
        msgBox5.setIcon(QMessageBox::Warning);
        msgBox5.setText("<font color='black'>Por favor, insira o CPF do cliente para atualizar.</font>");
        msgBox5.setWindowTitle("Erro");
        msgBox5.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox5.exec();
        return;
    }

    // Atualiza cliente
    std::vector<QString> cpfs = Database::getInstance().getData("cpf");
    auto it = std::find(cpfs.begin(), cpfs.end(), cpf);

    if (it != cpfs.end()) {
        int index = std::distance(cpfs.begin(), it);

        // Atualiza os dados
        Database::getInstance().addData("nome", ui->nomeTutor->text());
        Database::getInstance().addData("email", ui->emailTutor->text());
        Database::getInstance().addData("endereco", ui->enderecoTutor->text());
        Database::getInstance().addData("telefone", ui->telefoneTutor->text());

        QMessageBox msgBox6;
        msgBox6.setIcon(QMessageBox::Information);
        msgBox6.setText("<font color='black'>Cliente atualizado com sucesso!</font>");
        msgBox6.setWindowTitle("Sucesso");
        msgBox6.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox6.exec();
    } else {
        QMessageBox msgBox7;
        msgBox7.setIcon(QMessageBox::Warning);
        msgBox7.setText("<font color='black'>Cliente com o CPF informado não encontrado.</font>");
        msgBox7.setWindowTitle("Erro");
        msgBox7.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox7.exec();
    }
}

void cadastrocliente::onDeletarClienteClicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        QMessageBox msgBox8;
        msgBox8.setIcon(QMessageBox::Warning);
        msgBox8.setText("<font color='black'>Por favor, insira o CPF do cliente para deletar.</font>");
        msgBox8.setWindowTitle("Erro");
        msgBox8.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox8.exec();
        return;
    }

    std::vector<QString> cpfs = Database::getInstance().getData("cpf");
    auto it = std::find(cpfs.begin(), cpfs.end(), cpf);

    if (it != cpfs.end()) {
        int index = std::distance(cpfs.begin(), it);
        // Remove cliente de todas as listas
        Database::getInstance().getData("nome").erase(Database::getInstance().getData("nome").begin() + index);
        Database::getInstance().getData("cpf").erase(Database::getInstance().getData("cpf").begin() + index);
        Database::getInstance().getData("email").erase(Database::getInstance().getData("email").begin() + index);
        Database::getInstance().getData("endereco").erase(Database::getInstance().getData("endereco").begin() + index);
        Database::getInstance().getData("telefone").erase(Database::getInstance().getData("telefone").begin() + index);

        QMessageBox msgBox9;
        msgBox9.setIcon(QMessageBox::Information);
        msgBox9.setText("<font color='black'>Cliente deletado com sucesso!</font>");
        msgBox9.setWindowTitle("Sucesso");
        msgBox9.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox9.exec();

        ui->nomeTutor->clear();
        ui->cpfTutor->clear();
        ui->emailTutor->clear();
        ui->enderecoTutor->clear();
        ui->telefoneTutor->clear();
    } else {
        QMessageBox msgBox10;
        msgBox10.setIcon(QMessageBox::Warning);
        msgBox10.setText("<font color='black'>Cliente com o CPF informado não encontrado.</font>");
        msgBox10.setWindowTitle("Erro");
        msgBox10.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox10.exec();




    }
}

void cadastrocliente::on_clienteButton_2_clicked()
{
    cadastropet *petScreen = new cadastropet();
    petScreen->show();
    this->close();
}

