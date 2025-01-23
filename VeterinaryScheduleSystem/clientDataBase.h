#ifndef clientDataBase_H
#define clientDataBase_H

#include <QString>
#include <vector>

struct Cliente {
    QString nome;
    QString cpf;
    QString email;
    QString endereco;
    QString telefone;
};

class clientDataBase {
public:
    static clientDataBase& getInstance() {
        static clientDataBase instance;
        return instance;
    }

    void addCliente(const Cliente& cliente) {
        clientes.push_back(cliente);
    }

    const std::vector<Cliente>& getClientes() const {
        return clientes;
    }

private:
    clientDataBase() = default;
    std::vector<Cliente> clientes;
};

#endif // clientDataBase_H
