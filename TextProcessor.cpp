#include "TextProcessor.h"
#include "dictionary.h"
#include <fstream>
#include <iostream>

// Конструктор, инициализирующий TextProcessor с заданным словарем
TextProcessor::TextProcessor(Dictionary& dict) : dictionary(dict) {}

// Метод для обработки текста
void TextProcessor::processText(const std::string& inputFilename, 
                                const std::string& outputFilename)
{
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cerr << "Error opening input or output file." << std::endl;
        return;
    }

    std::string word;
    // Обработка каждого слова из входного файла
    while (inputFile >> word)
    {
        // Удаление знаков препинания из слова
        std::string cleanedWord = removePunctuation(word);

        if (!cleanedWord.empty()) // Проверка, не является ли слово пустым после удаления знаков препинания
        {
            std::string lowercaseWord = toLowerCase(cleanedWord); // Приведение слова к нижнему регистру

            if (dictionary.contains(lowercaseWord))
            {
                outputFile << cleanedWord << " "; // Запись слова в выходной файл
            }
            else
            {
                // Если слово отсутствует в словаре, предлагаем пользователю действия
                std::cout << "Word \"" << cleanedWord << "\" not found in dictionary."<< std::endl;
                std::cout << "What do you want to do? "<< std::endl;
                std::cout << "1 --- Add to dictionary and keep, " << std::endl;
                std::cout << "2 --- Keep without adding, "<< std::endl;
                std::cout << "3 --- Replace:"<< std::endl;
                int choice; 
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    dictionary.insert(lowercaseWord); // Добавляем слово в словарь
                    outputFile << cleanedWord << " "; // Записываем слово в выходной файл
                    break;
                case 2:
                    outputFile << cleanedWord << " "; // Оставляем слово в выходном файле без добавления в словарь
                    break;
                case 3:
                    // Заменяем слово на похожее из словаря, отличающееся на 1 символ
                    replaceWithSimilar(cleanedWord, outputFile);
                    break;
                default:
                    std::cerr << "Invalid choice. Keeping word in output file." << std::endl;
                    outputFile << cleanedWord << " "; // Оставляем слово без изменений
                    break;
                }
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

// Приведение слова к нижнему регистру
std::string TextProcessor::toLowerCase(const std::string& word)
{
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    return lowercaseWord;
}

// Проверка, отличается ли слово на 1 символ от другого слова
bool TextProcessor::isOneCharDifference(const std::string& word1, const std::string& word2) const
{
    int diffCount = 0;
    // Если длины слов отличаются более чем на 1 символ, они не подходят
    if (std::abs((int)(word1.length() - word2.length())) > 1)
        return false;

    // Если длины слов равны, проверяем количество различающихся символов
    if (word1.length() == word2.length()) 
    {
        for (size_t i = 0; i < word1.length(); ++i) 
        {
            if (word1[i] != word2[i]) 
            {
                ++diffCount;
                if (diffCount > 1)
                    return false; // Больше одной разницы - не подходит
            }
        }
    }
    else 
    { // Длины слов отличаются на 1 символ
        const std::string& longerWord = (word1.length() > word2.length()) ? word1 : word2;
        const std::string& shorterWord = (word1.length() > word2.length()) ? word2 : word1;
        size_t i = 0, j = 0;
        while (i < longerWord.length() && j < shorterWord.length()) 
        {
            if (longerWord[i] != shorterWord[j]) {
                ++diffCount;
                if (diffCount > 1)
                    return false; // Больше одной разницы - не подходит
                ++i; // Двигаемся дальше в длинном слове
            }
            else 
            {
                ++i;
                ++j;
            }
        }
    }
    return diffCount == 1;
}

// Замена слова на похожее из словаря, отличающееся на 1 символ
void TextProcessor::replaceWithSimilar(const std::string& word, std::ofstream& outputFile) const
{
    bool similarWordFound = false;
    for (const std::string& dictWord : dictionary.getWords())
    {
        if (isOneCharDifference(word, dictWord))
        {
            outputFile << dictWord << " "; // Записываем похожее слово в выходной файл
            similarWordFound = true;
            return;
        }
    }

    // Если похожее слово не найдено, сообщаем пользователю
    std::cout << "Similar word not found for \"" << word << "\"." << std::endl;
    std::cout << "What do you want to do? " << std::endl;
    std::cout << "1 --- Add to dictionary and keep, " << std::endl;
    std::cout << "2 --- Keep without adding, " << std::endl;
    int choice;
    std::cin >> choice;

    // Принятие решения пользователем
    switch (choice) 
    {
    case 1:
        // Добавляем слово в словарь и оставляем его
        dictionary.insert(word);
        outputFile << word << " ";
        break;
    case 2:
        outputFile << word << " "; // Оставляем исходное слово без изменений
        break;
    default:
        std::cerr << "Invalid choice. Keeping word unchanged." << std::endl;
        outputFile << word << " "; // Оставляем исходное слово без изменений
        break;
    }
}


// Удаление знаков препинания из строки
std::string TextProcessor::removePunctuation(const std::string& word) 
{
    std::string result;
    for (char c : word) 
    {
        if (!std::ispunct(c)) 
        { // Проверяем, является ли символ знаком препинания
            result += c; // Добавляем символ к результату, если это не знак препинания
        }
    }
    return result;
}

