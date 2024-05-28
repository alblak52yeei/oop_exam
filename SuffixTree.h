#pragma once

#include "Node.h"
#include <string>

class SuffixTree {
private:
    std::string text;
    Node* root;
    Node* active_node;
    int active_edge;
    int active_length;
    int remaining_suffixes;
    int end_point;

    Node* createNode(int start, int* end, Node* suffix_link = nullptr);
    void extendSuffixTree(int index);
    void buildSuffixTree();
    int searchSubString(const std::string& substring);
public:
    SuffixTree(const std::string& str);
    int search(const std::string& substring);
};
