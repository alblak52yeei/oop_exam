#pragma once

#include <vector>
#include <string>
#include "SuffixTree.h"

class TextComparer {
public:
    // Сравнение текстов и нахождение двух наиболее близких по проценту совпадения
    static std::pair<int, int> compareTexts(const std::vector<std::string>& texts);

private:
    // Подсчет совпадений подстрок между двумя текстами
    static double calculateMatchPercentage(const std::string& text1, const std::string& text2);
};
