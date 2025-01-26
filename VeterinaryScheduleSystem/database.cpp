#include "database.h"

// Definindo o método getInstance(isso é uma instancia singleton)
Database& Database::getInstance() {
    static Database instance;
    return instance;
}

//CadastroTutor

// Adiciona um dado para uma chave específica
void Database::addData(const QString& key, const QString& value) {
    storage[key].push_back(value);  // Adiciona um novo valor à chave
}

// Retorna os dados armazenados para uma chave específica
std::vector<QString> Database::getData(const QString& key) {
    if (storage.find(key) != storage.end()) {
        return storage[key];  // Retorna os dados
    }
    return {};  // Retorna um vetor vazio se não encontrar a chave
}

// Remove um dado com base no índice da chave
void Database::deleteData(const QString& key, int index) {
    if (storage.find(key) != storage.end() && index < storage[key].size()) {
        storage[key].erase(storage[key].begin() + index);  // Remove o dado do índice específico
    }
}


//CadastroPet

// Adiciona os dados de um pet
void Database::addPet(const QStringList& petData) {
    pets.append(petData);  // Usamos append para adicionar à QList
}

// Retorna todos os pets
QList<QStringList> Database::getPets() {
    return pets;
}

// Remove um pet pelo índice
void Database::deletePet(int index) {
    if (index >= 0 && index < pets.size()) {
        pets.removeAt(index);  // Remove o item pelo índice
    }
}
