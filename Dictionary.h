#pragma once

#include <string>
#include <set>

class Dictionary 
{
private:
    std::set<std::string> words; // ��������� ��� �������� ���� �������

public:
    // �����������, ������� ��������� ������� �� �����
    Dictionary(const std::string& filename);

    // �������� ������� ����� � �������
    bool contains(const std::string& word) const;

    // ���������� ����� � �������
    void insert(const std::string& word);

    // ���������� ������� � ����
    void saveToFile(const std::string& filename) const;

    const std::set<std::string>& getWords() const;
};


