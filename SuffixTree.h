#pragma once

#include "Node.h"
#include <string>

class SuffixTree {
private:
    std::string text;          // Входная строка
    Node* root;                // Корневой узел дерева 
    Node* active_node;         // Активный узел
    int active_edge;           // Активное ребро (индекс в строке)
    int active_length;         // Длина активного ребра
    int remaining_suffixes;    // Количество оставшихся суффиксов для добавления
    int end_point;             // Конечный индекс текущего суффикса

    // Метод для создания нового узла
    Node* createNode(int start, int* end, Node* suffix_link = nullptr);

    // Метод для расширения суффиксного дерева
    void extendSuffixTree(int index);

    // Метод для построения суффиксного дерева
    void buildSuffixTree();

    // Метод для поиска подстроки внутри дерева
    int searchSubString(const std::string& substring);

public:
    // Конструктор, инициализирующий суффиксное дерево с заданной строкой
    SuffixTree(const std::string& str);

    // Метод для поиска подстроки внутри дерева, возвращает индекс начала подстроки
    int search(const std::string& substring);
};
