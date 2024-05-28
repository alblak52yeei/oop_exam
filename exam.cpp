#include <iostream>
#include "SuffixTree.h"

using namespace std;

int main() {
    // Входная строка
    string text = "abceafabcbananabc"; 
    // Создаем суффиксное дерево
    SuffixTree suffixTree(text);

    // Подстрока для поиска
    string pattern = "afa"; 
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
