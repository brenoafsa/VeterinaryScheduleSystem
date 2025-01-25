#ifndef PETDATABASE_H
#define PETDATABASE_H

#include <QString>
#include <vector>

struct Pet {
    QString nome;
    QString especie;
    QString raca;
    QString idade;
    QString cor;
};

class petDataBase {
public:
    static petDataBase& getInstance() {
        static petDataBase instance;
        return instance;
    }

    void addPet(const Pet& pet) {
        pets.push_back(pet);
    }

    const std::vector<Pet>& getPets() const {
        return pets;
    }

private:
    petDataBase() = default;
    std::vector<Pet> pets;
};

#endif // PETDATABASE_H
