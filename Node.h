#pragma once

struct Node {
    int start, *end;
    Node* suffix_link;
    Node* children[256];

    Node(int start, int* end, Node* suffix_link = nullptr);
    int length(int current_index);
};
