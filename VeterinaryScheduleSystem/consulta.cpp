#include "consulta.h"

Consulta::Consulta(const std::string& data, const std::string& horario, const std::string& motivo,
                   const std::string& veterinario, Animal* animal, const std::string& status)
    : data(data), horario(horario), motivo(motivo), veterinario(veterinario), animal(animal), status(status) {}

std::string Consulta::getData() const {
    return data;
}

void Consulta::setData(const std::string& data) {
    this->data = data;
}

std::string Consulta::getHorario() const {
    return horario;
}

void Consulta::setHorario(const std::string& horario) {
    this->horario = horario;
}

std::string Consulta::getMotivo() const {
    return motivo;
}

void Consulta::setMotivo(const std::string& motivo) {
    this->motivo = motivo;
}

std::string Consulta::getVeterinario() const {
    return veterinario;
}

void Consulta::setVeterinario(const std::string& veterinario) {
    this->veterinario = veterinario;
}

Animal* Consulta::getAnimal() const {
    return animal;
}

void Consulta::setAnimal(Animal* animal) {
    this->animal = animal;
}

std::string Consulta::getStatus() const {
    return status;
}

void Consulta::setStatus(const std::string& status) {
    this->status = status;
}
