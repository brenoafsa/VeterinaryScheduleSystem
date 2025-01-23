#include "database.h"  // Incluindo o cabeçalho

// Definindo o método getInstance
Database& Database::getInstance() {
    static Database instance;
    return instance;
}

// Definindo o método addData
void Database::addData(const QString& key, const QString& value) {
    storage[key].push_back(value);  // Adiciona uma nova senha para a chave (nome)
}

// Definindo o método getData
std::vector<QString> Database::getData(const QString& key) {
    if (storage.find(key) != storage.end()) {
        return storage[key];  // Retorna as senhas associadas à chave
    }
    return {};  // Retorna um vetor vazio se não encontrar a chave
}
