// File: database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <string>

// Simple in-memory database for primitive data storage
class Database {
public:
    static Database& getInstance() {
        static Database instance;
        return instance;
    }

    void addData(const std::string& key, const std::string& value);
    std::vector<std::string> getData(const std::string& key);

private:
    Database() = default;
    std::map<std::string, std::vector<std::string>> storage;
};

void Database::addData(const std::string& key, const std::string& value) {
    storage[key].push_back(value);
}

std::vector<std::string> Database::getData(const std::string& key) {
    if (storage.find(key) != storage.end()) {
        return storage[key];
    }
    return {};
}

#endif // DATABASE_H
