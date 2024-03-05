#include "Dictionary.h"
#include "TextProcessor.h"
#include <fstream>
#include <iostream>

// Конструктор класса Dictionary, загружает словарь из файла
Dictionary::Dictionary(const std::string& filename)
{
    std::ifstream file(filename); // Открываем файл для чтения
    if (!file.is_open()) // Проверяем, удалось ли открыть файл
    {
        // Если не удалось открыть файл, выводим сообщение об ошибке
        std::cerr << "Error opening dictionary file: " << filename << std::endl;
        return;
    }

    std::string word;
    // Загрузка слов из файла в множество
    while (file >> word) // Читаем слова из файла по одному
    {
        words.insert(word); // Добавляем слово в множество
    }
    file.close(); // Закрываем файл
}


const std::set<std::string>& Dictionary::getWords() const
{
    return words;
}

// Проверяем, содержится ли слово в словаре
bool Dictionary::contains(const std::string& word) const
{
    std::string lowerCaseWord = TextProcessor::toLowerCase(word); // Преобразуем слово к нижнему регистру
    return words.find(lowerCaseWord) != words.end(); // Проверяем наличие слова в словаре
}


// Добавляем слово в словарь
void Dictionary::insert(const std::string& word)
{
    words.insert(word); // Добавляем слово в множество
}

// Сохраняем словарь в файл
void Dictionary::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename); // Открываем файл для записи
    if (!file.is_open()) // Проверяем, удалось ли открыть файл
    {
        // Если не удалось открыть файл, выводим сообщение об ошибке
        std::cerr << "Error opening file for saving dictionary: " << filename << std::endl;
        return;
    }

    // Сохранение слов из множества в файл
    for (const auto& word : words) // Перебираем все слова в множестве
    {
        file << word << std::endl; // Записываем каждое слово в файл
    }
    file.close(); // Закрываем файл
}



