#include "TextProcessor.h"
#include "dictionary.h"
#include <fstream>
#include <iostream>

// �����������, ���������������� TextProcessor � �������� ��������
TextProcessor::TextProcessor(Dictionary& dict) : dictionary(dict) {}

// ����� ��� ��������� ������
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
    // ��������� ������� ����� �� �������� �����
    while (inputFile >> word)
    {
        // �������� ������ ���������� �� �����
        std::string cleanedWord = removePunctuation(word);

        if (!cleanedWord.empty()) // ��������, �� �������� �� ����� ������ ����� �������� ������ ����������
        {
            std::string lowercaseWord = toLowerCase(cleanedWord); // ���������� ����� � ������� ��������

            if (dictionary.contains(lowercaseWord))
            {
                outputFile << cleanedWord << " "; // ������ ����� � �������� ����
            }
            else
            {
                // ���� ����� ����������� � �������, ���������� ������������ ��������
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
                    dictionary.insert(lowercaseWord); // ��������� ����� � �������
                    outputFile << cleanedWord << " "; // ���������� ����� � �������� ����
                    break;
                case 2:
                    outputFile << cleanedWord << " "; // ��������� ����� � �������� ����� ��� ���������� � �������
                    break;
                case 3:
                    // �������� ����� �� ������� �� �������, ������������ �� 1 ������
                    replaceWithSimilar(cleanedWord, outputFile);
                    break;
                default:
                    std::cerr << "Invalid choice. Keeping word in output file." << std::endl;
                    outputFile << cleanedWord << " "; // ��������� ����� ��� ���������
                    break;
                }
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

// ���������� ����� � ������� ��������
std::string TextProcessor::toLowerCase(const std::string& word)
{
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
    return lowercaseWord;
}

// ��������, ���������� �� ����� �� 1 ������ �� ������� �����
bool TextProcessor::isOneCharDifference(const std::string& word1, const std::string& word2) const
{
    int diffCount = 0;
    // ���� ����� ���� ���������� ����� ��� �� 1 ������, ��� �� ��������
    if (std::abs((int)(word1.length() - word2.length())) > 1)
        return false;

    // ���� ����� ���� �����, ��������� ���������� ������������� ��������
    if (word1.length() == word2.length()) 
    {
        for (size_t i = 0; i < word1.length(); ++i) 
        {
            if (word1[i] != word2[i]) 
            {
                ++diffCount;
                if (diffCount > 1)
                    return false; // ������ ����� ������� - �� ��������
            }
        }
    }
    else 
    { // ����� ���� ���������� �� 1 ������
        const std::string& longerWord = (word1.length() > word2.length()) ? word1 : word2;
        const std::string& shorterWord = (word1.length() > word2.length()) ? word2 : word1;
        size_t i = 0, j = 0;
        while (i < longerWord.length() && j < shorterWord.length()) 
        {
            if (longerWord[i] != shorterWord[j]) {
                ++diffCount;
                if (diffCount > 1)
                    return false; // ������ ����� ������� - �� ��������
                ++i; // ��������� ������ � ������� �����
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

// ������ ����� �� ������� �� �������, ������������ �� 1 ������
void TextProcessor::replaceWithSimilar(const std::string& word, std::ofstream& outputFile) const
{
    bool similarWordFound = false;
    for (const std::string& dictWord : dictionary.getWords())
    {
        if (isOneCharDifference(word, dictWord))
        {
            outputFile << dictWord << " "; // ���������� ������� ����� � �������� ����
            similarWordFound = true;
            return;
        }
    }

    // ���� ������� ����� �� �������, �������� ������������
    std::cout << "Similar word not found for \"" << word << "\"." << std::endl;
    std::cout << "What do you want to do? " << std::endl;
    std::cout << "1 --- Add to dictionary and keep, " << std::endl;
    std::cout << "2 --- Keep without adding, " << std::endl;
    int choice;
    std::cin >> choice;

    // �������� ������� �������������
    switch (choice) 
    {
    case 1:
        // ��������� ����� � ������� � ��������� ���
        dictionary.insert(word);
        outputFile << word << " ";
        break;
    case 2:
        outputFile << word << " "; // ��������� �������� ����� ��� ���������
        break;
    default:
        std::cerr << "Invalid choice. Keeping word unchanged." << std::endl;
        outputFile << word << " "; // ��������� �������� ����� ��� ���������
        break;
    }
}


// �������� ������ ���������� �� ������
std::string TextProcessor::removePunctuation(const std::string& word) 
{
    std::string result;
    for (char c : word) 
    {
        if (!std::ispunct(c)) 
        { // ���������, �������� �� ������ ������ ����������
            result += c; // ��������� ������ � ����������, ���� ��� �� ���� ����������
        }
    }
    return result;
}

