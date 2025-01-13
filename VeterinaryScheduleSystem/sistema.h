#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "veterinario.h"
#include "tutor.h"
#include "consulta.h"

class Sistema {
private:
    std::vector<Veterinario> veterinarios;
    std::vector<Tutor> tutores;
    std::vector<Consulta> consultas;

public:
    // User and System Management
    void cadastrarVeterinario(const Veterinario& veterinario);
    void cadastrarTutor(const Tutor& tutor);
    void agendarConsulta(const Consulta& consulta);

    // Filtering Methods
    std::vector<Consulta> filtrarConsultasPorData(const std::string& data) const;
    std::vector<Consulta> filtrarConsultasPorVeterinario(const std::string& nomeVeterinario) const;
    std::vector<Consulta> filtrarConsultasPorStatus(const std::string& status) const;

    // Utility Methods
    std::vector<std::string> obterHorariosLivres(const Veterinario& veterinario, const std::string& data) const;
};

#endif // SISTEMA_H
