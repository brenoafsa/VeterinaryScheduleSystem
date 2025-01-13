#ifndef VETERINARIO_H
#define VETERINARIO_H

#include <string>
#include <vector>
#include "consulta.h"

class Veterinario {
private:
    std::string nome;
    std::string crm;
    std::vector<Consulta*> agenda;

public:
    // Constructor
    Veterinario(const std::string& nome, const std::string& crm);

    // Getters and Setters
    std::string getNome() const;
    void setNome(const std::string& nome);
    std::string getCRM() const;
    void setCRM(const std::string& crm);

    // Agenda Management
    std::vector<Consulta*> getAgenda() const;
    void adicionarConsulta(Consulta* consulta);
    bool verificarDisponibilidade(const std::string& data, const std::string& horario) const;
};

#endif // VETERINARIO_H
