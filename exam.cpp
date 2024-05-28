#include <iostream>
#include "SuffixTree.h"

using namespace std;

int main() {
    // Локализация
    setlocale(0, "");

    // Входная строка
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
    }

    return 0;
}
