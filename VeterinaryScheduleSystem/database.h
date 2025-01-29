#ifndef DATABASE_H
#define DATABASE_H

#include <QList>        // Necessário para QList
#include <QStringList>  // Necessário para QStringList
#include <map>
#include <vector>
#include <QString>

class Database {
public:
    static Database& getInstance();

    //cadastro tutor
    void addData(const QString& key, const QString& value);
    std::vector<QString> getData(const QString& key);
    void deleteData(const QString& key, int index);

    void addPet(const QStringList& petData);  // Adiciona os dados do pet
    QList<QStringList> getPets();            // Retorna todos os pets
    void deletePet(int index);               // Remove um pet pelo índice


private:
    Database() = default;
    std::map<QString, std::vector<QString>> storage;  // Usando QString no map para armazenar dados

    QList<QStringList> pets;  // Lista de pets, onde cada QStringList armazena os dados de um pet

};

#endif // DATABASE_H
