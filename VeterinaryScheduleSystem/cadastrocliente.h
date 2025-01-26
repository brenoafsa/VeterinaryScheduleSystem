#ifndef CADASTROCLIENTE_H
#define CADASTROCLIENTE_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QPushButton>

namespace Ui {
class cadastrocliente;
}

class clientDataBase {
public:
    struct ClientData {
        QString nome;
        QString cpf;
        QString email;
        QString endereco;
        QString telefone;
    };

    static clientDataBase& getInstance() {
        static clientDataBase instance;
        return instance;
    }

    void addClient(const ClientData& client) {
        clients.append(client);
    }

    QList<ClientData> getClients() const {
        return clients;
    }

    bool isCpfUnique(const QString& cpf) const {
        for (const auto& client : clients) {
            if (client.cpf == cpf) {
                return false;
            }
        }
        return true;
    }

    // Atualiza informações do cliente com base no CPF
    bool updateClient(const QString& cpf, const ClientData& updatedClient) {
        for (auto& client : clients) {
            if (client.cpf == cpf) {
                client = updatedClient;
                return true;
            }
        }
        return false;
    }

    // Exclui cliente com base no CPF
    bool deleteClient(const QString& cpf) {
        for (int i = 0; i < clients.size(); ++i) {
            if (clients[i].cpf == cpf) {
                clients.removeAt(i);
                return true;
            }
        }
        return false;
    }

private:
    QList<ClientData> clients;

    clientDataBase() = default;
    ~clientDataBase() = default;

    clientDataBase(const clientDataBase&) = delete;
    clientDataBase& operator=(const clientDataBase&) = delete;
};

class cadastrocliente : public QDialog
{
    Q_OBJECT

public:
    explicit cadastrocliente(QWidget *parent = nullptr);
    ~cadastrocliente();

private slots:

    void on_menuButton_clicked();

    void on_clienteButton_2_clicked();

    void on_ListarCliente_clicked();

    void on_AtualizarCliente_clicked();

    void on_DeletarCliente_clicked();

    void on_cadastrarButton_clicked();

    void on_pesquisarButton_clicked();

private:
    Ui::cadastrocliente *ui;
    QPushButton *listarClientesButton;
    QPushButton *atualizarClienteButton;
    QPushButton *deletarClienteButton;

    QVector<QJsonObject> carregarTutores(); // Carrega tutores do arquivo JSON
    void salvarTutores(const QVector<QJsonObject> &tutores); // Salva tutores no arquivo JSON
};

#endif // CADASTROCLIENTE_H
