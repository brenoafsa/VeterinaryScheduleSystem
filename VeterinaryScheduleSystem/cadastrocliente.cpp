#include "cadastrocliente.h"
#include "ui_cadastrocliente.h"
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
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos!");
        return;
    }

    if (!clientDataBase::getInstance().isCpfUnique(cpf)) {
        QMessageBox::warning(this, "Erro", "CPF já cadastrado!");
        return;
    }

    clientDataBase::ClientData client = {nome, cpf, email, endereco, telefone};
    clientDataBase::getInstance().addClient(client);

    QMessageBox::information(this, "Sucesso", "Cliente cadastrado com sucesso!");

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
        QMessageBox::information(this, "Lista de Clientes", "Nenhum cliente cadastrado.");
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
        QMessageBox::warning(this, "Erro", "Por favor, insira o CPF do cliente para atualizar.");
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
        QMessageBox::information(this, "Sucesso", "Cliente atualizado com sucesso!");
    } else {
        QMessageBox::warning(this, "Erro", "Cliente com o CPF informado não encontrado.");
    }
}

void cadastrocliente::onDeletarClienteClicked()
{
    QString cpf = ui->cpfTutor->text();

    if (cpf.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, insira o CPF do cliente para deletar.");
        return;
    }

    if (clientDataBase::getInstance().deleteClient(cpf)) {
        QMessageBox::information(this, "Sucesso", "Cliente deletado com sucesso!");
        ui->nomeTutor->clear();
        ui->cpfTutor->clear();
        ui->emailTutor->clear();
        ui->enderecoTutor->clear();
        ui->telefoneTutor->clear();
    } else {
        QMessageBox::warning(this, "Erro", "Cliente com o CPF informado não encontrado.");
    }
}
