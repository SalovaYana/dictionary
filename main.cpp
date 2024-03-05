#include "TextProcessor.h"
#include "Dictionary.h"

int main() 
{

    std::string dictFile = "dict.txt"; // Файл словаря
    std::string inputFile = "input.txt"; // Файл с входным текстом
    std::string outputFile = "output.txt"; // Файл для записи обработанного текста
    std::string newDictFile = "new_dict.txt"; // Файл для сохранения нового словаря

    // Создаем объект словаря
    Dictionary dictionary(dictFile);

    // Создаем объект для обработки текста и передаем ему словарь
    TextProcessor textProcessor(dictionary);

    // Обрабатываем текст, используя TextProcessor
    textProcessor.processText(inputFile, outputFile);

    // Сохраняем обновленный словарь в файл
    dictionary.saveToFile(newDictFile);

    return 0;
}
