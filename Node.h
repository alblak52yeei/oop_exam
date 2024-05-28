#pragma once

struct Node {
    int start;          // Начальный индекс ребра в строке
    int* end;           // Указатель на конечный индекс ребра
    Node* suffix_link;  // Ссылка на суффиксный узел
    Node* children[256]; // Массив указателей на дочерние узлы (по символам) 

    // Конструктор узла, инициализирует начальный индекс, конечный индекс и суффиксную ссылку
    Node(int start, int* end, Node* suffix_link = nullptr);
    // Метод для вычисления длины ребра от start до текущего индекса
    int length(int current_index);
};
