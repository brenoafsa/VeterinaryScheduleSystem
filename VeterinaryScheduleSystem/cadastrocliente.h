#ifndef CADASTROCLIENTE_H
#define CADASTROCLIENTE_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QPushButton>
#include "cadastroalterar.h"

// Gerando a interface
namespace Ui {
class cadastrocliente;
}

// Classe para gerenciar os dados dos clientes.
class clientDataBase {
public:
    // Armazenando as informações de um cliente
    struct ClientData {
        QString nome;
        QString cpf;
        QString email;
        QString endereco;
        QString telefone;
    };

    // Retorna a instância única da base de dados de clientes
    static clientDataBase& getInstance() {
        static clientDataBase instance;
        return instance;
    }

    // Adiciona um cliente na base de dados
    void addClient(const ClientData& client) {
        clients.append(client);
    }

    // Lista de todos os clientes cadastrados
    QList<ClientData> getClients() const {
        return clients;
    }

    // Checa se o CPF já existe na base de dados
    bool isCpfUnique(const QString& cpf) const {
        for (const auto& client : clients) {
            if (client.cpf == cpf) {
                return false;   // CPF já existe
            }
        }
        return true;            // CPF não encontrado
    }

    // Atualiza informações do cliente com base no CPF
    bool updateClient(const QString& cpf, const ClientData& updatedClient) {
        for (auto& client : clients) {
            if (client.cpf == cpf) {
                client = updatedClient;
                return true;    // Informações atualizadas
            }
        }
        return false;           // Cliente não encontrado
    }

    // Exclui cliente com base no CPF
    bool deleteClient(const QString& cpf) {
        for (int i = 0; i < clients.size(); ++i) {
            if (clients[i].cpf == cpf) {
                clients.removeAt(i);
                return true;    // Cliente removido
            }
        }
        return false;           // Cliente não encontrado
    }

private:
    QList<ClientData> clients;      // Lista interna dos clientes

    clientDataBase() = default;
    ~clientDataBase() = default;

    clientDataBase(const clientDataBase&) = delete;
    clientDataBase& operator=(const clientDataBase&) = delete;
};


// Classe que gerencia a tela de cadastro dos cliente
class cadastrocliente : public QDialog
{
    Q_OBJECT

public:
    explicit cadastrocliente(QWidget *parent = nullptr);        // Construtor
    ~cadastrocliente();                                         // Destrutor

private slots:
    // Funções associadas aos botões da interface.
    void on_menuButton_clicked();
    void on_clienteButton_2_clicked();
    void on_cadastrarButton_clicked();
    void on_pesquisarButton_clicked();
    void on_telaButton_clicked();
    void on_agendamentoButton_clicked();
    void on_consultaButton_clicked();
    void on_cancelarButton_clicked();

private:
    Ui::cadastrocliente *ui;        // Ponteiro para interface

    // Botões movidos para esta classe para ter um controle mais direto
    QPushButton *listarClientesButton;
    QPushButton *atualizarClienteButton;
    QPushButton *deletarClienteButton;

    cadastroalterar *cadastroalterarWindow;                        // Instância de tela para alteração do cadastro

    QVector<QJsonObject> carregarTutores();                        // Carrega tutores do arquivo JSON
    void salvarTutores(const QVector<QJsonObject> &tutores);       // Salva tutores no arquivo JSON
};

#endif
