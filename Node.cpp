#include "Node.h"
#include <algorithm> // ��� ������� std::min

using namespace std;

Node::Node(int start, int* end, Node* suffix_link) : start(start), end(end), suffix_link(suffix_link) {
    for (int i = 0; i < 256; ++i) {
        children[i] = nullptr; // ������������� ���� ����� ��� nullptr
    }
}

int Node::length(int current_index) {
    return min(*end, current_index + 1) - start; // ���������� ����� �����
}
