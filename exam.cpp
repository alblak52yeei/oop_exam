#include <iostream>
#include "SuffixTree.h"

using namespace std;

int main() {
    // ������� ������
    string text = "abceafabcbananabc"; 
    // ������� ���������� ������
    SuffixTree suffixTree(text);

    // ��������� ��� ������
    string pattern = "afa"; 
    // ���� ���������
    int index = suffixTree.search(pattern);

    // ���� ��������� �������, ������� ������
    if (index != -1) {
        cout << "Found at index: " << index << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    return 0;
}
