#ifndef TUTOR_H
#define TUTOR_H

#include <string>
#include <vector>
#include "animal.h"

class Tutor {
private:
    std::string nome;
    std::string cpf;
    std::string telefone;
    std::string endereco;
    std::vector<Animal> animais;

public:
    // Constructors
    Tutor(const std::string& nome, const std::string& cpf, const std::string& telefone, const std::string& endereco);

    // Getters and Setters
    std::string getNome() const;
    void setNome(const std::string& nome);
    std::string getCPF() const;
    void setCPF(const std::string& cpf);
    std::string getTelefone() const;
    void setTelefone(const std::string& telefone);
    std::string getEndereco() const;
    void setEndereco(const std::string& endereco);

    // Animal Management
    void adicionarAnimal(const Animal& animal);
    std::vector<Animal> getAnimais() const;
};

#endif // TUTOR_H
