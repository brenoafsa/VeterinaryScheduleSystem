#include "animal.h"

Animal::Animal(const std::string& nome, int idade, const std::string& raca, const std::string& historicoMedico)
    : nome(nome), idade(idade), raca(raca), historicoMedico(historicoMedico) {}

std::string Animal::getNome() const {
    return nome;
}

void Animal::setNome(const std::string& nome) {
    this->nome = nome;
}

int Animal::getIdade() const {
    return idade;
}

void Animal::setIdade(int idade) {
    this->idade = idade;
}

std::string Animal::getRaca() const {
    return raca;
}

void Animal::setRaca(const std::string& raca) {
    this->raca = raca;
}

std::string Animal::getHistoricoMedico() const {
    return historicoMedico;
}

void Animal::setHistoricoMedico(const std::string& historicoMedico) {
    this->historicoMedico = historicoMedico;
}

void Animal::adicionarConsultaHistorico(const std::string& consulta) {
    historicoConsultas.push_back(consulta);
}

std::vector<std::string> Animal::getHistoricoConsultas() const {
    return historicoConsultas;
}
