#include "veterinario.h"

Veterinario::Veterinario(const std::string& nome, const std::string& crm)
    : nome(nome), crm(crm) {}

std::string Veterinario::getNome() const {
    return nome;
}

void Veterinario::setNome(const std::string& nome) {
    this->nome = nome;
}

std::string Veterinario::getCRM() const {
    return crm;
}

void Veterinario::setCRM(const std::string& crm) {
    this->crm = crm;
}

std::vector<Consulta*> Veterinario::getAgenda() const {
    return agenda;
}

void Veterinario::adicionarConsulta(Consulta* consulta) {
    agenda.push_back(consulta);
}

bool Veterinario::verificarDisponibilidade(const std::string& data, const std::string& horario) const {
    for (const auto& consulta : agenda) {
        if (consulta->getData() == data && consulta->getHorario() == horario) {
            return false; // Time slot is already occupied
        }
    }
    return true;
}
