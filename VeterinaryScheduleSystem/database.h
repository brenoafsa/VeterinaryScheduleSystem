#ifndef DATABASE_H
#define DATABASE_H

#include <QList>        // Necessário para QList
#include <QStringList>  // Necessário para QStringList
#include <map>
#include <vector>
#include <QString>

// Classe que gerencia e armazena dados (incluindo informações dos tutores e pets)
class Database {
public:
    static Database& getInstance();

    void addData(const QString& key, const QString& value);     // Adiciona dados dos tutores
    std::vector<QString> getData(const QString& key);           // Recupera dados com base na chave
    void deleteData(const QString& key, int index);             // Exclui dados com base na chave

    void addPet(const QStringList& petData);     // Adiciona os dados do pet
    QList<QStringList> getPets();                // Retorna todos os pets
    void deletePet(int index);                   // Remove um pet pelo índice


private:
    Database() = default;
    std::map<QString, std::vector<QString>> storage;  // Mapa que armazena dados dos tutores

    QList<QStringList> pets;                          // Lista que armazena os pets

};

#endif
