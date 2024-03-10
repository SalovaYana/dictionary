#include "Dictionary.h"
#include "TextProcessor.h"
#include <fstream>
#include <iostream>


Dictionary::Dictionary(const std::string& filename)
{
    std::ifstream file(filename); 
    if (!file.is_open()) 
    {
        
        std::cerr << "Error opening dictionary file: " << filename << std::endl;
        return;
    }

    std::string word;
   
    while (file >> word) 
    {
        words.insert(word); 
    }
    file.close(); 
}


const std::set<std::string>& Dictionary::getWords() const
{
    return words;
}


bool Dictionary::contains(const std::string& word) const
{
    std::string lowerCaseWord = TextProcessor::toLowerCase(word); 
    return words.find(lowerCaseWord) != words.end(); 
}


void Dictionary::insert(const std::string& word)
{
    words.insert(word); 
}


void Dictionary::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename); 
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file for saving dictionary: " << filename << std::endl;
        return;
    }

    for (const auto& word : words) 
    {
        file << word << std::endl; 
    }
    file.close(); 
}



