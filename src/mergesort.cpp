#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <random>


template <typename It>
std::string PrintRangeToString(It range_begin, It range_end) {
    // удобный тип ostringstream -> https://ru.cppreference.com/w/cpp/io/basic_ostringstream
    std::ostringstream out;
    bool is_first = true;
    for (auto it = range_begin; it != range_end; ++it) {
        if (!is_first) {
            out << ' ';
        }
        is_first = false;
        out << *it;
    }
    out << std::endl;
    // получаем доступ к строке с помощью метода str для ostringstream
    return out.str();
}

template <typename It>
void PrintRange(It range_begin, It range_end) {
    std::cout << PrintRangeToString(range_begin, range_end);
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
    std::size_t range_length = std::distance(range_begin, range_end);
    if (range_length < 2) {
        return;
    }

    // 2. Создаем вектор, содержащий все элементы текущего диапазона
    //    ну а вообще можно переделать на динамический массив чтоб было быстрее
    
    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

    // 3. Разбиваем вектор на две равные части
    auto mid = std::next(elements.begin(), range_length / 2);

    // 4. Вызываем функцию MergeSort от каждой половины вектора
    MergeSort(elements.begin(), mid);
    MergeSort(mid, elements.end());

    // 5. С помощью алгоритма merge сливаем отсортированные половины
    // в исходный диапазон
    // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}

int main() {
    std::cout << "****************" << std::endl;
    std::vector<int> vec(10);
    std::iota(vec.begin(), vec.end(), 1);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::shuffle(vec.begin(), vec.end(), rng);
    PrintRange(vec.begin(), vec.end());
    std::cout << "****************" << std::endl;
    MergeSort(vec.begin(), vec.end());
    PrintRange(vec.begin(), vec.end());
}