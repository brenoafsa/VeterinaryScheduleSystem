#ifndef CONSULTA_H
#define CONSULTA_H

#include <string>
#include "animal.h"

class Consulta {
private:
    std::string data;
    std::string horario;
    std::string motivo;
    std::string veterinario;
    Animal* animal;
    std::string status;

public:
    // Constructors
    Consulta(const std::string& data, const std::string& horario, const std::string& motivo,
             const std::string& veterinario, Animal* animal, const std::string& status);

    // Getters and Setters
    std::string getData() const;
    void setData(const std::string& data);
    std::string getHorario() const;
    void setHorario(const std::string& horario);
    std::string getMotivo() const;
    void setMotivo(const std::string& motivo);
    std::string getVeterinario() const;
    void setVeterinario(const std::string& veterinario);
    Animal* getAnimal() const;
    void setAnimal(Animal* animal);
    std::string getStatus() const;
    void setStatus(const std::string& status);
};

#endif // CONSULTA_H
