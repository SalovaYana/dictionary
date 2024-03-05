#pragma once

#include <string>
#include <set>

class Dictionary 
{
private:
    std::set<std::string> words; // Множество для хранения слов словаря

public:
    // Конструктор, который загружает словарь из файла
    Dictionary(const std::string& filename);

    // Проверка наличия слова в словаре
    bool contains(const std::string& word) const;

    // Добавление слова в словарь
    void insert(const std::string& word);

    // Сохранение словаря в файл
    void saveToFile(const std::string& filename) const;

    const std::set<std::string>& getWords() const;
};


