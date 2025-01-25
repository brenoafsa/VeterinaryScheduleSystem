#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <QString>

class Database {
public:
    static Database& getInstance();

    void addData(const QString& key, const QString& value);
    std::vector<QString> getData(const QString& key);
    void deleteData(const QString& key, int index);

private:
    Database() = default;
    std::map<QString, std::vector<QString>> storage;  // Usando QString no map para armazenar dados
};

#endif // DATABASE_H
