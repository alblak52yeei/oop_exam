#include "TextComparer.h"
#include <algorithm>

// Подсчет совпадений подстрок между двумя текстами
double TextComparer::calculateMatchPercentage(const std::string& text1, const std::string& text2) {
     // Создаем суффиксные деревья для двух текстов
    SuffixTree tree1(text1);
    SuffixTree tree2(text2); 
    // Переменная для подсчета совпадений
    int matches = 0;

    // Перебираем все подстроки второго текста
    for (size_t i = 0; i < text2.size(); ++i) {
        for (size_t j = i + 1; j <= text2.size(); ++j) {
            // Извлекаем подстроку
            std::string substring = text2.substr(i, j - i);
            // Проверяем, есть ли подстрока в первом тексте
            if (tree1.search(substring) != -1) {
                // Если есть, увеличиваем счетчик совпадений
                matches += substring.size(); 
            }
        }
    }

    // Возвращаем процент совпадений (в два раза делим на сумму длин обоих текстов)
    return (2.0 * matches) / (text1.size() + text2.size());
}

// Сравнение текстов и нахождение двух наиболее близких по проценту совпадения
std::pair<int, int> TextComparer::compareTexts(const std::vector<std::string>& texts) {
    // Получаем количество текстов
    int n = texts.size();
     // Пара индексов для наиболее близких текстов
    std::pair<int, int> best_pair;
    // Лучший процент совпадений
    double best_percentage = 0.0; 

    // Перебираем все пары текстов
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Вычисляем процент совпадений для текущей пары
            double percentage = calculateMatchPercentage(texts[i], texts[j]); 
            // Если текущий процент больше лучшего
            if (percentage > best_percentage) {
                // Обновляем лучший процент
                best_percentage = percentage; 
                // Обновляем лучшую пару
                best_pair = {i, j}; 
            }
        }
    }

    // Возвращаем пару индексов наиболее близких текстов
    return best_pair;
}