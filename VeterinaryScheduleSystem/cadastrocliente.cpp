#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
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

        // Define explicitamente as cores de fundo e texto
        msgBox1.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox1.exec();

        //QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        return;
    }

    if (!clientDataBase::getInstance().isCpfUnique(cpf)) {
        //QMessageBox::warning(this, "Erro", "CPF já cadastrado!");

        QMessageBox msgBox2;

        msgBox2.setIcon(QMessageBox::Warning);
        msgBox2.setText("<font color='black'>CPF já cadastrado!</font>");
        msgBox2.setWindowTitle("Erro");

        // Define explicitamente as cores de fundo e texto
        msgBox2.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox2.exec();

        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        return;
    }

    clientDataBase::ClientData client = {nome, cpf, email, endereco, telefone};
    clientDataBase::getInstance().addClient(client);

    //QMessageBox::information(this, "Sucesso", "Cliente cadastrado com sucesso!");
    //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

    QMessageBox msgBox3;

    msgBox3.setIcon(QMessageBox::Information);
    msgBox3.setText("<font color='black'>Cliente cadastrado com sucesso!</font>");
    msgBox3.setWindowTitle("Sucesso");

    // Define explicitamente as cores de fundo e texto
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
    QList<clientDataBase::ClientData> clients = clientDataBase::getInstance().getClients();

    if (clients.isEmpty()) {
        //QMessageBox::information(this, "Lista de Clientes", "Nenhum cliente cadastrado.");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox4;

        msgBox4.setIcon(QMessageBox::Information);
        msgBox4.setText("<font color='black'>Nenhum cliente cadastrado.</font>");
        msgBox4.setWindowTitle("Lista de Clientes");

        // Define explicitamente as cores de fundo e texto
        msgBox4.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox4.exec();

        return;
    }

    QString clientList;
    for (const auto& client : clients) {
        clientList += QString("Nome: %1\nCPF: %2\nEmail: %3\nEndereço: %4\nTelefone: %5\n\n")
                          .arg(client.nome)
                          .arg(client.cpf)
                          .arg(client.email)
                          .arg(client.endereco)
                          .arg(client.telefone);
    }

    QMessageBox::information(this, "Lista de Clientes", clientList);

}

void cadastrocliente::onAtualizarClienteClicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        //QMessageBox::warning(this, "Erro", "Por favor, insira o CPF do cliente para atualizar.");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox5;

        msgBox5.setIcon(QMessageBox::Warning);
        msgBox5.setText("<font color='black'>Por favor, insira o CPF do cliente para atualizar.</font>");
        msgBox5.setWindowTitle("Erro");

        // Define explicitamente as cores de fundo e texto
        msgBox5.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox5.exec();

        return;
    }

    clientDataBase::ClientData updatedClient = {
        ui->nomeTutor->text(),
        cpf,
        ui->emailTutor->text(),
        ui->enderecoTutor->text(),
        ui->telefoneTutor->text()
    };

    if (clientDataBase::getInstance().updateClient(cpf, updatedClient)) {
       // QMessageBox::information(this, "Sucesso", "Cliente atualizado com sucesso!");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox6;

        msgBox6.setIcon(QMessageBox::Information);
        msgBox6.setText("<font color='black'>Cliente atualizado com sucesso!</font>");
        msgBox6.setWindowTitle("Sucesso");

        // Define explicitamente as cores de fundo e texto
        msgBox6.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox6.exec();

    } else {
       // QMessageBox::warning(this, "Erro", "Cliente com o CPF informado não encontrado.");
        // msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");


        QMessageBox msgBox7;

        msgBox7.setIcon(QMessageBox::Information);
        msgBox7.setText("<font color='black'>Cliente com o CPF informado não encontrado.</font>");
        msgBox7.setWindowTitle("Erro");

        // Define explicitamente as cores de fundo e texto
        msgBox7.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox7.exec();

    }
}

void cadastrocliente::onDeletarClienteClicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        //QMessageBox::warning(this, "Erro", "Por favor, insira o CPF do cliente para deletar.");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox8;

        msgBox8.setIcon(QMessageBox::Warning);
        msgBox8.setText("<font color='black'>Por favor, insira o CPF do cliente para deletar.</font>");
        msgBox8.setWindowTitle("Erro");

        // Define explicitamente as cores de fundo e texto
        msgBox8.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox8.exec();


        return;
    }

    if (clientDataBase::getInstance().deleteClient(cpf)) {
        //QMessageBox::information(this, "Sucesso", "Cliente deletado com sucesso!");
        //msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox9;

        msgBox9.setIcon(QMessageBox::Information);
        msgBox9.setText("<font color='black'>Cliente deletado com sucesso!</font>");
        msgBox9.setWindowTitle("Sucesso");

        // Define explicitamente as cores de fundo e texto
        msgBox9.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox9.exec();

        ui->nomeTutor->clear();
        ui->cpfTutor->clear();
        ui->emailTutor->clear();
        ui->enderecoTutor->clear();
        ui->telefoneTutor->clear();
    } else {
        // QMessageBox::warning(this, "Erro", "Cliente com o CPF informado não encontrado.");
        // msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        QMessageBox msgBox10;

        msgBox10.setIcon(QMessageBox::Warning);
        msgBox10.setText("<font color='black'>Cliente com o CPF informado não encontrado.</font>");
        msgBox10.setWindowTitle("Erro");

        // Define explicitamente as cores de fundo e texto
        msgBox10.setStyleSheet("QMessageBox { background-color: white; color: black; }");
        msgBox10.exec();


    }
}

void cadastrocliente::on_petButton_clicked()
{
    // Botão Cadastro Cliente
    cadastropet *petScreen = new cadastropet(); // Cria a tela de cadastro
    petScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

