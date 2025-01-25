#include "database.h"

// Definindo o método getInstance
Database& Database::getInstance() {
    static Database instance;
    return instance;
}

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
