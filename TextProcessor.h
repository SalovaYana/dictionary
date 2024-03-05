#pragma once
#include <string>
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class TextProcessor 
{
public:
    TextProcessor(Dictionary& dict);

    // Приведение слова к нижнему регистру
    static std::string toLowerCase(const std::string& word);

    // Метод для обработки текста
    void processText(const std::string& inputFilename, const std::string& outputFilename);

private:

    Dictionary& dictionary; // Ссылка на объект словаря

    // Проверка, отличается ли слово на 1 символ от другого слова
    bool isOneCharDifference(const std::string& word1, const std::string& word2) const;

    // Замена слова на похожее из словаря, отличающееся на 1 символ
    void replaceWithSimilar(const std::string& word, std::ofstream& outputFile) const;

    // Удаление знаков препинания из строки
    std::string removePunctuation(const std::string& word);
};




