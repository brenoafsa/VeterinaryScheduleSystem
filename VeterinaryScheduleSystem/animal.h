#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <vector>

class Animal {
private:
    std::string nome;
    int idade;
    std::string raca;
    std::string historicoMedico;
    std::vector<std::string> historicoConsultas; // Add a vector to store consultation history

public:
    // Constructor
    Animal(const std::string& nome, int idade, const std::string& raca, const std::string& historicoMedico);

    // Getters and Setters
    std::string getNome() const;
    void setNome(const std::string& nome);

    int getIdade() const;
    void setIdade(int idade);

    std::string getRaca() const;
    void setRaca(const std::string& raca);

    std::string getHistoricoMedico() const;
    void setHistoricoMedico(const std::string& historicoMedico);

    // Methods for consultation history
    void adicionarConsultaHistorico(const std::string& consulta);
    std::vector<std::string> getHistoricoConsultas() const;
};

#endif
