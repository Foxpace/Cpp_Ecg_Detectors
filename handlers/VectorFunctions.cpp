
#include "vector"
#include <numeric>
#include <algorithm>

template<typename T>
double mean(std::vector<T> values){
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

template<typename T>
T maxValueFromPointToEnd(std::vector<T> values, T from){
    return *std::max_element(std::begin(values) + from, std::end(values));
}

template<typename T>
int findValueFromPointToEnd(std::vector<T> values, T from, T valueToFind){
    auto index = std::find(values.begin()+from, values.end(), valueToFind);
    if (index != values.end()){
        return index - values.begin();
    }
    return -1.0;
}

template<typename T>
std::vector<T> subVector(std::vector<T> values, unsigned int from, unsigned int to){
    typename std::vector<T>::const_iterator first = values.begin() + from;
    typename std::vector<T>::const_iterator last = values.begin() + to;
    std::vector<T> newVec(first, last);
    return newVec;
}

template<typename T>
std::vector<T> valuesOfIndexes(std::vector<T> values, const std::vector<int>& indexes){
    std::vector<T> neededValues;
    for(int i: indexes){
        neededValues.push_back(values[i]);
    }
    return neededValues;
}

template<typename T>
std::vector<T> diff(std::vector<T> values){
    std::vector<T> result;
    for (int i = 1; i < values.size(); i++) {
        result.push_back(values[i] - values[i-1]);
    }
    return result;
}
