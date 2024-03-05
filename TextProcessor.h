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

    // ���������� ����� � ������� ��������
    static std::string toLowerCase(const std::string& word);

    // ����� ��� ��������� ������
    void processText(const std::string& inputFilename, const std::string& outputFilename);

private:

    Dictionary& dictionary; // ������ �� ������ �������

    // ��������, ���������� �� ����� �� 1 ������ �� ������� �����
    bool isOneCharDifference(const std::string& word1, const std::string& word2) const;

    // ������ ����� �� ������� �� �������, ������������ �� 1 ������
    void replaceWithSimilar(const std::string& word, std::ofstream& outputFile) const;

    // �������� ������ ���������� �� ������
    std::string removePunctuation(const std::string& word);
};




