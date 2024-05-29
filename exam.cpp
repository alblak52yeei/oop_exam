#include <iostream>
#include "SuffixTree.h"
#include "TextComparer.h"

using namespace std;

int main() {
    // Локализация
    setlocale(0, "");

    /*// Входная строка
    string text; 

    cout << "Введите строку: ";
    cin >> text;

    // Подстрока для поиска
    string pattern; 

    cout << "Введите подстроку: ";
    cin >> pattern;

    // Создаем суффиксное дерево
    SuffixTree suffixTree(text);
    // Ищем подстроку
    int index = suffixTree.search(pattern); 

    // Если подстрока найдена, выводим индекс
    if (index != -1) {
        cout << "Found at index: " << index << endl;
    }
    else {
        cout << "Not found" << endl;
    }*/
    
    // Входные тексты для сравнения
    std::vector<std::string> texts = {
        "abanabanana",
        "bananas",
        "ananas",
        "apple",
        "orange",
        "banana",
        "anana",
        "ababab",
        "banabana",
        "nanananana"
    };

    // Нахождение двух наиболее близких текстов
    pair<int, int> closest_texts = TextComparer::compareTexts(texts);

    // Вывод результатов
    cout << "Самые похожие текста: " << closest_texts.first << " и " << closest_texts.second << endl;
    cout << "Текст 1: " << texts[closest_texts.first] << endl;
    cout << "Текст 2: " << texts[closest_texts.second] << endl;

    return 0;
}