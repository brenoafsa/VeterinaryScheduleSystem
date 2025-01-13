#include "tutor.h"

// Construtor
Tutor::Tutor(const std::string& nome, const std::string& cpf, const std::string& telefone, const std::string& endereco)
    : nome(nome), cpf(cpf), telefone(telefone), endereco(endereco) {}

// Getters e Setters
std::string Tutor::getNome() const {
    return nome;
}

void Tutor::setNome(const std::string& nome) {
    this->nome = nome;
}

std::string Tutor::getCPF() const {
    return cpf;
}

void Tutor::setCPF(const std::string& cpf) {
    this->cpf = cpf;
}

std::string Tutor::getTelefone() const {
    return telefone;
}

void Tutor::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}

std::string Tutor::getEndereco() const {
    return endereco;
}

void Tutor::setEndereco(const std::string& endereco) {
    this->endereco = endereco;
}

// Gerenciamento de Animais
void Tutor::adicionarAnimal(const Animal& animal) {
    animais.push_back(animal);
}

std::vector<Animal> Tutor::getAnimais() const {
    return animais;
}
