#include "SuffixTree.h"
#include <iostream>

using namespace std;

// ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
SuffixTree::SuffixTree(const string& str) : text(str), root(nullptr), active_node(nullptr), active_edge(-1), active_length(0), remaining_suffixes(0), end_point(-1) {
    // ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜
    root = createNode(-1, new int(-1)); 
    // ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜ ˜˜˜˜˜˜
    active_node = root;
    // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜ ˜˜˜˜˜˜
    active_node->suffix_link = root;
    // ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
    buildSuffixTree();
}

// ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜
Node* SuffixTree::createNode(int start, int* end, Node* suffix_link) {
    // ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜
    return new Node(start, end, suffix_link);
}

// ˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
void SuffixTree::extendSuffixTree(int index) {
    // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜
    end_point = index; 
    // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    remaining_suffixes++; 

    // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
    Node* last_added_node = nullptr; 

    // ˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
    while (remaining_suffixes > 0) {
        if (active_length == 0) {
            // ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜
            active_edge = index;
        }

        // ˜˜˜˜ ˜˜˜ ˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
        if (active_node->children[text[active_edge]] == nullptr) { 
            // ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜
            active_node->children[text[active_edge]] = createNode(index, &end_point);

            last_added_node = nullptr;
        }
        else {
            // ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
            Node* next_node = active_node->children[text[active_edge]]; 
            // ˜˜˜˜˜ ˜˜˜˜˜
            int length = next_node->length(index); 

            // ˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜
            if (active_length >= length) {
                // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜
                active_edge += length; 
                // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜
                active_length -= length;
                // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜
                active_node = next_node;
                // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
                continue;
            }

            // ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜ ˜˜ ˜˜˜˜˜
            if (text[next_node->start + active_length] == text[index]) {
                // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜
                active_length++; 

                if (active_node != root)
                    last_added_node = nullptr;
                
                // ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜
                break; 
            }

            // ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜, ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
            Node* split_node = createNode(next_node->start, new int(next_node->start + active_length));
            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜ ˜˜˜˜˜ ˜˜˜˜
            active_node->children[text[active_edge]] = split_node;
            // ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜, ˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
            split_node->children[text[index]] = createNode(index, &end_point);
            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
            next_node->start += active_length;
            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
            split_node->children[text[next_node->start]] = next_node;

            if (last_added_node != nullptr) {
                // ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
                last_added_node->suffix_link = split_node;
            }

            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
            last_added_node = split_node; 
        }

        // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
        remaining_suffixes--;

        if (active_node != root) {
            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜
            active_node = (active_node->suffix_link != nullptr) ? active_node->suffix_link : root; 
        }

        else {
            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜, ˜˜˜˜ ˜˜˜ > 0
            if (active_length > 0) {
                active_length--;
            }

            // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜
            active_edge = index - remaining_suffixes + 1; 
        }
    }
}

// ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
void SuffixTree::buildSuffixTree() {
    int n = text.length();

    for (int i = 0; i < n; i++) {
        // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜
        extendSuffixTree(i);
    }
}

// ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
int SuffixTree::searchSubString(const string& substring) {
    // ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    int n = substring.length();
    // ˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜
    Node* current_node = root; 
    int i = 0;
    int j = 0;

    // ˜˜˜˜ ˜˜ ˜˜˜˜˜ ˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    while (i < n) {
        char edge_char = substring[i];

        if (current_node->children[edge_char] == nullptr) {
            // ˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜
            return -1;
        }

        Node* next_node = current_node->children[edge_char];
        int edge_length = next_node->length(text.length());

        // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜
        for (j = 0; j < edge_length && i < n; j++) { 
            if (text[next_node->start + j] != substring[i]) {
                // ˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜˜ -1
                return -1;
            }

            i++;
        }

        if (i == n) {
            // ˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜
            return next_node->start - j + 1;
        }

        // ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
        current_node = next_node;
    }

    // ˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜
    return -1;
}

// ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
int SuffixTree::search(const string& substring) {
    // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    return searchSubString(substring);
}
