#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <QString>  // Usando QString ao invés de std::string

// Banco de dados simples em memória para armazenamento primitivo
class Database {
public:
    static Database& getInstance();

    void addData(const QString& key, const QString& value);
    std::vector<QString> getData(const QString& key);

private:
    Database() = default;
    std::map<QString, std::vector<QString>> storage;  // Usando QString no map
};

#endif // DATABASE_H
