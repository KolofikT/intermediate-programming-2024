#include <iostream>
#include <vector>

void print(std::vector<int> data) {
    if (data.size() == 0) {
        std::cout << "[]";
        return;
    }

    std::cout << "[ ";
    for (std::size_t i = 0; i < data.size() - 1; i++) {
        std::cout << data[i] << ", ";
    }

    std::cout << data.back() << " ]";
}

int sum(std::vector<int> data) {
    int suma = 0;
    for(int e : data){
        suma = suma + e;
    }
    return suma;
}

float average(std::vector<int> data) {
    int total = data.size();
    float sum = 0;
    float avg = 0;
    for(int i : data){
        sum = sum + i;
        avg = sum / total;
    }
    return avg;
}

float median(std::vector<int> data) {
    int size = data.size();
    int mid = size / 2;
    float avg_mid = data[mid];
    if(size % 2 == 0){
        avg_mid = (data[mid] + data[mid - 1]) / 2.0;
    }
    return avg_mid;
}

std::vector<int> range(int start, int end) {
    std::vector<int> data;
    if(start < end){
        for(int i = start; i < end; i++){
            data.push_back(i);
        }
    } else if(start > end){
        for(int i = start; i > end; i--){
            data.push_back(i);
        }
    } else {
        std::cout << "[]";
    }
    return data;
}

std::vector<int> runningSum(std::vector<int> data) {
    std::vector<int> sum;
    int suma = 0;
    for(int e : data){
        suma = suma + e;
        sum.push_back(suma);
    }
    return sum;
}

std::vector<int> rotateRight(std::vector<int> data, int count) {
    std::vector<int> vector;
    vector.resize(data.size());
    for(std::size_t i = 0; i < data.size(); i++){
        vector[(i + count) % vector.size()] = data[i];   
    }
    return vector;
}

int main() {
    std::vector<int> vec1 = { 1, 9, 4, 8, 4, 0, 9, 2, 3, 5, 6 };
    std::vector<int> asc1 = { 0, 2, 4, 7, 8, 5 };
    std::vector<int> asc2 = { 1, 3, 5, 6, 7, 9 };

    std::cout << "sum(vec1): " << sum(vec1) << std::endl;
    std::cout << "average(vec1): " << average(vec1) << std::endl;
    std::cout << "median(asc1): " << median(asc1) << std::endl;

    std::cout << "range(5, 10): ";
    print(range(5, 10));
    std::cout << std::endl;

    std::cout << "range(11, 4): ";
    print(range(11, 4));
    std::cout << std::endl;

    std::cout << "runningSum(vec1): ";
    print(runningSum(vec1));
    std::cout << std::endl;

    std::cout << "rotateRight(vec1): ";
    print(rotateRight(vec1, 2));
    std::cout << std::endl;
}
