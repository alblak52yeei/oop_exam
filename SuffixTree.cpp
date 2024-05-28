#include "SuffixTree.h"
#include <iostream>

using namespace std;

// Конструктор суффиксного дерева
SuffixTree::SuffixTree(const string& str) : text(str), root(nullptr), active_node(nullptr), active_edge(-1), active_length(0), remaining_suffixes(0), end_point(-1) {
    // Создаем корень дерева
    root = createNode(-1, new int(-1)); 
    // Устанавливаем активный узел на корень
    active_node = root;
    // Суффиксная ссылка корня указывает на него самого
    active_node->suffix_link = root;
    // Строим суффиксное дерево
    buildSuffixTree();
}

// Приватный метод для создания узла
Node* SuffixTree::createNode(int start, int* end, Node* suffix_link) {
    // Создаем новый узел и возвращаем указатель на него
    return new Node(start, end, suffix_link);
}

// Добавление в суффиксное дерево
void SuffixTree::extendSuffixTree(int index) {
    // Обновляем текущий конец
    end_point = index; 
    // Увеличиваем количество оставшихся суффиксов
    remaining_suffixes++; 

    // Последний добавленный узел
    Node* last_added_node = nullptr; 

    // Пока остаются необработанные суффиксы
    while (remaining_suffixes > 0) {
        if (active_length == 0) {
            // Устанавливаем активное ребро на текущий индекс
            active_edge = index;
        }

        // Если нет пути по текущему символу
        if (active_node->children[text[active_edge]] == nullptr) { 
            // Создаем новый лист
            active_node->children[text[active_edge]] = createNode(index, &end_point);

            last_added_node = nullptr;
        }
        else {
            // Переход к следующему узлу
            Node* next_node = active_node->children[text[active_edge]]; 
            // Длина ребра
            int length = next_node->length(index); 

            // Если активная длина больше или равна длине ребра
            if (active_length >= length) {
                // Перемещаем активное ребро вниз
                active_edge += length; 
                // Уменьшаем активную длину
                active_length -= length;
                // Перемещаем активный узел
                active_node = next_node;
                // Продолжаем цикл
                continue;
            }

            // Если символ уже есть на ребре
            if (text[next_node->start + active_length] == text[index]) {
                // Увеличиваем активную длину
                active_length++; 

                if (active_node != root)
                    last_added_node = nullptr;
                
                // Выходим из цикла
                break; 
            }

            // Создаем новый узел, который будет разделением ребра
            Node* split_node = createNode(next_node->start, new int(next_node->start + active_length));
            // Обновляем ссылку родительского узла на новый узел
            active_node->children[text[active_edge]] = split_node;
            // Создаем новый узел для символа, на котором разбиваем ребро
            split_node->children[text[index]] = createNode(index, &end_point);
            // Обновляем начало ребра для следующего узла
            next_node->start += active_length;
            // Обновляем ссылку родительского узла для следующего узла
            split_node->children[text[next_node->start]] = next_node;

            if (last_added_node != nullptr) {
                // Устанавливаем суффиксную ссылку
                last_added_node->suffix_link = split_node;
            }

            // Обновляем последний добавленный узел
            last_added_node = split_node; 
        }

        // Уменьшаем количество оставшихся суффиксов
        remaining_suffixes--;

        if (active_node != root) {
            // Обновляем активный узел
            active_node = (active_node->suffix_link != nullptr) ? active_node->suffix_link : root; 
        }

        else {
            // Уменьшаем активную длину, если она > 0
            if (active_length > 0) {
                active_length--;
            }

            // Обновляем активное ребро
            active_edge = index - remaining_suffixes + 1; 
        }
    }
}

// Приватный метод для постройки суффиксного дерева
void SuffixTree::buildSuffixTree() {
    int n = text.length();

    for (int i = 0; i < n; i++) {
        // Расширяем дерево для каждого символа строки
        extendSuffixTree(i);
    }
}

// Приватный метод для поиска подстроки
int SuffixTree::searchSubString(const string& substring) {
    // Получаем длину подстроки
    int n = substring.length();
    // Начинаем с корня
    Node* current_node = root; 
    int i = 0;
    int j = 0;

    // Пока не дошли до конца подстроки
    while (i < n) {
        char edge_char = substring[i];

        if (current_node->children[edge_char] == nullptr) {
            // Если текущий символ не найден среди детей текущего узла
            return -1;
        }

        Node* next_node = current_node->children[edge_char];
        int edge_length = next_node->length(text.length());

        // Проверяем совпадение символов на ребре
        for (j = 0; j < edge_length && i < n; j++) { 
            if (text[next_node->start + j] != substring[i]) {
                // Если символы не совпадают, возвращаем -1
                return -1;
            }

            i++;
        }

        if (i == n) {
            // Если достигли конца подстроки, возвращаем индекс начала
            return next_node->start - j + 1;
        }

        // Переходим к следующему узлу
        current_node = next_node;
    }

    // Если подстрока не найдена
    return -1;
}

// Публичный метод для поиска подстроки
int SuffixTree::search(const string& substring) {
    // Возвращаем результат поиска подстроки
    return searchSubString(substring);
}
