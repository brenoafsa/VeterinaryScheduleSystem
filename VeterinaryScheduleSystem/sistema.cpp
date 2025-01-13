#include "sistema.h"
#include <algorithm>  // Para std::remove
#include <vector>     // Para std::vector
#include <string>     // Para std::string

void Sistema::cadastrarVeterinario(const Veterinario& veterinario) {
    veterinarios.push_back(veterinario);
}

void Sistema::cadastrarTutor(const Tutor& tutor) {
    tutores.push_back(tutor);
}

void Sistema::agendarConsulta(const Consulta& consulta) {
    consultas.push_back(consulta);
}

std::vector<Consulta> Sistema::filtrarConsultasPorData(const std::string& data) const {
    std::vector<Consulta> resultados;
    for (const auto& consulta : consultas) {
        if (consulta.getData() == data) {
            resultados.push_back(consulta);
        }
    }
    return resultados;
}

std::vector<Consulta> Sistema::filtrarConsultasPorVeterinario(const std::string& nomeVeterinario) const {
    std::vector<Consulta> resultados;
    for (const auto& consulta : consultas) {
        if (consulta.getVeterinario() == nomeVeterinario) {
            resultados.push_back(consulta);
        }
    }
    return resultados;
}

std::vector<Consulta> Sistema::filtrarConsultasPorStatus(const std::string& status) const {
    std::vector<Consulta> resultados;
    for (const auto& consulta : consultas) {
        if (consulta.getStatus() == status) {
            resultados.push_back(consulta);
        }
    }
    return resultados;
}

std::vector<std::string> Sistema::obterHorariosLivres(const Veterinario& veterinario, const std::string& data) const {
    std::vector<std::string> horariosLivres = { "08:00", "09:00", "10:00", "11:00", "14:00", "15:00", "16:00" };
    for (const auto& consulta : veterinario.getAgenda()) {
        if (consulta->getData() == data) {
            // Remove o horário da lista de horários livres
            horariosLivres.erase(std::remove(horariosLivres.begin(), horariosLivres.end(), consulta->getHorario()), horariosLivres.end());
        }
    }
    return horariosLivres;
}

